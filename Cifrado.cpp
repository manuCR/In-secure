#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

std::string encryptMessage(const std::string& message, const std::string& publicKeyPath) {
    // Cargar la clave pública
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
    if (!publicKeyFile) {
        std::cerr << "Error al abrir el archivo de clave pública" << std::endl;
        return "";
    }

    RSA* rsa = PEM_read_RSA_PUBKEY(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave pública" << std::endl;
        return "";
    }

    // Obtener el tamaño máximo del bloque de encriptación
    int maxLength = RSA_size(rsa) - 42; // RSA_PKCS1_PADDING

    // Preparar el buffer de salida
    std::string encryptedMessage;
    encryptedMessage.resize(RSA_size(rsa));

    // Encriptar el mensaje
    int encryptedLength = RSA_public_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()),
                                             reinterpret_cast<unsigned char*>(&encryptedMessage[0]), rsa, RSA_PKCS1_PADDING);

    RSA_free(rsa);

    if (encryptedLength == -1) {
        std::cerr << "Error al encriptar el mensaje" << std::endl;
        return "";
    }

    // Ajustar el tamaño del mensaje encriptado
    encryptedMessage.resize(encryptedLength);

    return encryptedMessage;
}

std::string decryptMessage(const std::string& encryptedMessage, const std::string& privateKeyPath) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        std::cerr << "Error al abrir el archivo de clave privada" << std::endl;
        return "";
    }

    RSA* rsa = PEM_read_RSAPrivateKey(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave privada" << std::endl;
        return "";
    }

    // Preparar el buffer de salida
    std::string decryptedMessage;
    decryptedMessage.resize(RSA_size(rsa));

    // Descifrar el mensaje
    int decryptedLength = RSA_private_decrypt(encryptedMessage.size(),
                                               reinterpret_cast<const unsigned char*>(encryptedMessage.data()),
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
