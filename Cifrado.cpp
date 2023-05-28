#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Cifrado.hpp"

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

Cifrado::Cifrado(){
    
}

std::string Cifrado::encryptMessage(const std::string& message, const std::string& publicKeyPath) {
    // Cargar la clave pública
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
    if (!publicKeyFile) {
        std::cerr << "Error al abrir el archivo de clave pública" << std::endl;
        return "";
    }

    RSA* rsa = PEM_read_RSAPrivateKey(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave pública" << std::endl;
        return "";
    }

    std::cout << "Tamaño máximo  antes " << std::endl;
    // int maxLength = RSA_public_encrypt(0, nullptr, nullptr, rsa, RSA_PKCS1_PADDING);

    // std::cout << "Tamaño máximo del bloque de encriptación: " << maxLength << " bytes" << std::endl;

    std::string encryptedMessage;
    encryptedMessage.resize(RSA_size(rsa));

    // Encriptar el mensaje
    int encryptedLength = RSA_private_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()),
                                             reinterpret_cast<unsigned char*>(&encryptedMessage[0]), rsa, RSA_PKCS1_PADDING);                                             

    RSA_free(rsa);

    if (encryptedLength == -1) {
        std::cerr << "Error al encriptar el mensaje" << std::endl;
        return "";
    }

    // Ajustar el tamaño del mensaje encriptado
    encryptedMessage.resize(encryptedLength);
    std::cout << "encrypted message lenght: " << message.length() << std::endl;
    std::cout << "encrypted lenght: " << encryptedLength << std::endl;
    std::cout << "encrypted message: " << encryptedMessage.length() << std::endl;

    return encryptedMessage;
}

std::string Cifrado::decryptMessage(char*  encryptedMessage, const std::string& privateKeyPath) {
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

