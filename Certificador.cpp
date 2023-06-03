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

    X509_REQ* csr = PEM_read_X509_REQ(csrFile, NULL, NULL, NULL);
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

    RSA* privateKey = PEM_read_RSAPrivateKey(privateKeyFile, NULL, NULL, NULL);
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

std::string decryptMessage(char* encryptedMessage, const std::string& privateKeyPath) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        std::cerr << "Error al abrir el archivo de clave privada" << std::endl;
        return "";
    }

    RSA* rsa = PEM_read_RSA_PUBKEY(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave privada" << std::endl;
        return "";
    }

    // Preparar el buffer de salida
    std::string decryptedMessage;
    decryptedMessage.resize(RSA_size(rsa));

    // Descifrar el mensaje
     int decryptedLength = RSA_public_decrypt(512, reinterpret_cast<const unsigned char*>(encryptedMessage),
                                               reinterpret_cast<unsigned char*>(&decryptedMessage[0]), rsa,
                                               RSA_PKCS1_PADDING);
    RSA_free(rsa);

    if (decryptedLength == -1) {
        std::cerr << "Error al descifrar el mensaje" << std::endl;
        return "";
    }

    // Ajustar el tamaño del mensaje descifrado
    decryptedMessage.resize(decryptedLength);

    return decryptedMessage;
}

int main() {
    std::string message = "un patito muy feito, era muy queridito";
    std::string publicKeyPath = "/home/valery.murcia/In-secure/pub.pem";
    std::string privateKeyPath = "/home/valery.murcia/In-secure/key.pem";

    // Encriptar el mensaje
    std::string encryptedMessage = encryptMessage(message, publicKeyPath);

    if (encryptedMessage.empty()) {
        std::cerr << "Error al encriptar el mensaje" << std::endl;
        return 1;
    }

    std::cout << "Mensaje encriptado: " << encryptedMessage << std::endl;

    // Descifrar el mensaje
    std::string decryptedMessage = decryptMessage(encryptedMessage, privateKeyPath);

    if (decryptedMessage.empty()) {
        std::cerr << "Error al descifrar el mensaje" << std::endl;
        return 1;
    }

    std::cout << "Mensaje descifrado: " << decryptedMessage << std::endl;

    return 0;
}