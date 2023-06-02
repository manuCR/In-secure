#include <iostream>
#include <fstream>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

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

bool validateCertificate(const std::string& certificateFilePath, const std::string& publicKeyFilePath) {
    // Abrir el archivo de certificado CRT
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

    // Validar la identidad del certificado
    int result = X509_verify(certificate, publicKey);
    if (result != 1) {
        std::cerr << "La identidad del certificado no es válida" << std::endl;
        X509_free(certificate);
        EVP_PKEY_free(publicKey);
        return false;
    }

    // La identidad del certificado es válida
    X509_free(certificate);
    EVP_PKEY_free(publicKey);
    return true;
}

int main() {
    std::string csrFilePath = "/home/valery.murcia/In-secure/Certificados/sofia.csr";
    std::string privateKeyFilePath = "/home/valery.murcia/In-secure/Certificados/CAGrupo5p.csr";
    std::string outputFilePath = "/home/valery.murcia/In-secure/Certificados/sofia.crt";
    std::string publicKeyFilePath = "/home/valery.murcia/In-secure/Certificados/CAGrupo5.csr";

    // Crear el certificado CRT
    if (signCSR(csrFilePath, privateKeyFilePath, outputFilePath)) {
        std::cout << "Certificado CRT creado exitosamente." << std::endl;

    } else {
        std::cerr << "Error al crear el certificado CRT." << std::endl;
    }

    return 0;
}
