#include <iostream>
#include <fstream>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>

bool signCSR(const std::string& csrFilePath, const std::string& privateKeyFilePath, const std::string& outputFilePath) {
    // Abrir el archivo CSR
    FILE* csrFile = fopen(csrFilePath.c_str(), "r");
    if (!csrFile) {
        std::cerr << "Error al abrir el archivo CSR: " << csrFilePath << std::endl;
        return false;
    }

    X509_REQ* csr = PEM_read_X509_REQ(csrFile, nullptr, nullptr, nullptr);
    fclose(csrFile);
    if (!csr) {
        std::cerr << "Error al leer el archivo CSR" << std::endl;
        return false;
    }

    // Abrir el archivo de clave privada
    FILE* privateKeyFile = fopen(privateKeyFilePath.c_str(), "r");
    if (!privateKeyFile) {
        std::cerr << "Error al abrir el archivo de clave privada: " << privateKeyFilePath << std::endl;
        X509_REQ_free(csr);
        return false;
    }

    RSA* privateKey = PEM_read_RSAPrivateKey(privateKeyFile, nullptr, nullptr, nullptr);
    fclose(privateKeyFile);
    if (!privateKey) {
        std::cerr << "Error al leer la clave privada" << std::endl;
        X509_REQ_free(csr);
        return false;
    }

    // Crear el objeto EVP_PKEY a partir de la clave privada RSA
    EVP_PKEY* privateKeyEVP = EVP_PKEY_new();
    if (!privateKeyEVP) {
        std::cerr << "Error al crear el objeto EVP_PKEY para la clave privada" << std::endl;
        X509_REQ_free(csr);
        RSA_free(privateKey);
        return false;
    }

    if (EVP_PKEY_assign_RSA(privateKeyEVP, privateKey) == 0) {
        std::cerr << "Error al asignar la clave privada RSA al objeto EVP_PKEY" << std::endl;
        X509_REQ_free(csr);
        EVP_PKEY_free(privateKeyEVP);
        return false;
    }

    // Crear el certificado
    X509* certificate = X509_new();
    if (!certificate) {
        std::cerr << "Error al crear el certificado" << std::endl;
        X509_REQ_free(csr);
        EVP_PKEY_free(privateKeyEVP);
        return false;
    }

    // Configurar los campos del certificado
    X509_set_version(certificate, 2);
    X509_set_pubkey(certificate, privateKeyEVP);
    X509_set_subject_name(certificate, X509_REQ_get_subject_name(csr));
    X509_set_issuer_name(certificate, X509_REQ_get_subject_name(csr));
    X509_set_pubkey(certificate, X509_REQ_get_pubkey(csr));

    // Firmar el certificado
    if (X509_sign(certificate, privateKeyEVP, EVP_sha256()) == 0) {
        std::cerr << "Error al firmar el certificado" << std::endl;
        X509_REQ_free(csr);
        EVP_PKEY_free(privateKeyEVP);
        X509_free(certificate);
        return false;
    }

    // Guardar el certificado en un archivo CRT
    FILE* outputFile = fopen(outputFilePath.c_str(), "w");
    if (!outputFile) {
        std::cerr << "Error al abrir el archivo de salida: " << outputFilePath << std::endl;
        X509_REQ_free(csr);
        EVP_PKEY_free(privateKeyEVP);
        X509_free(certificate);
        return false;
    }

    PEM_write_X509(outputFile, certificate);
    fclose(outputFile);

    X509_REQ_free(csr);
    EVP_PKEY_free(privateKeyEVP);
    X509_free(certificate);

    return true;
}

bool verifyCertificate(const std::string& certificateFilePath, const std::string& publicKeyFilePath) {
    // Abrir el archivo de certificado
    FILE* certificateFile = fopen(certificateFilePath.c_str(), "r");
    if (!certificateFile) {
        std::cerr << "Error al abrir el archivo de certificado: " << certificateFilePath << std::endl;
        return false;
    }

    X509* certificate = PEM_read_X509(certificateFile, nullptr, nullptr, nullptr);
    fclose(certificateFile);
    if (!certificate) {
        std::cerr << "Error al leer el archivo de certificado" << std::endl;
        return false;
    }

    // Abrir el archivo de clave pública
    FILE* publicKeyFile = fopen(publicKeyFilePath.c_str(), "r");
    if (!publicKeyFile) {
        std::cerr << "Error al abrir el archivo de clave pública: " << publicKeyFilePath << std::endl;
        X509_free(certificate);
        return false;
    }

    EVP_PKEY* publicKey = PEM_read_PUBKEY(publicKeyFile, nullptr, nullptr, nullptr);
    fclose(publicKeyFile);
    if (!publicKey) {
        std::cerr << "Error al leer la clave pública" << std::endl;
        X509_free(certificate);
        return false;
    }

    // Verificar la firma del certificado utilizando la clave pública
    if (X509_verify(certificate, publicKey) != 1) {
        std::cerr << "Error al verificar el certificado" << std::endl;
        X509_free(certificate);
        EVP_PKEY_free(publicKey);
        return false;
    }

    // La verificación fue exitosa
    std::cout << "El certificado es auténtico" << std::endl;

    X509_free(certificate);
    EVP_PKEY_free(publicKey);

    return true;
}


int main() {
    std::string csrFilePath = "/home/valery.murcia/In-secure/Certificados/sofia.csr";
    std::string privateKeyFilePath = "/home/valery.murcia/In-secure/Certificados/CAGrupo5p.csr.txt";
    std::string certificateFilePath = "ruta.crt";
    std::string publicKeyFilePath = "/home/valery.murcia/In-secure/Certificados/CAGrupo5.csr.txt";

    // Firma el CSR y guarda el certificado resultante en un archivo CRT
    if (signCSR(csrFilePath, privateKeyFilePath, certificateFilePath)) {
        std::cout << "El certificado ha sido firmado y guardado exitosamente." << std::endl;
    } else {
        std::cerr << "Error al firmar el CSR y guardar el certificado." << std::endl;
        return 1;
    }

    // Verifica la autenticidad del certificado utilizando la clave pública
    if (verifyCertificate(certificateFilePath, publicKeyFilePath)) {
        std::cout << "La autenticidad del certificado ha sido verificada correctamente." << std::endl;
    } else {
        std::cerr << "La autenticidad del certificado no pudo ser verificada." << std::endl;
        return 1;
    }

    return 0;
}
