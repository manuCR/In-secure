#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include "Cifrado.hpp"
#include <vector>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

Cifrado::Cifrado(){
    
}

void Cifrado::encryptMessage(const std::string& message, const std::string& publicKeyPath, std::vector<unsigned char> result) {
    // Cargar la clave pública
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
    if (!publicKeyFile) {
        std::cerr << "Error al abrir el archivo de clave pública" << std::endl;
        result[0] = 0;
    }

    RSA* rsa = PEM_read_RSAPrivateKey(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);

    if (!rsa) {
        std::cerr << "Error al leer la clave pública" << std::endl;
        result[0] = 0;
    }

    std::string encryptedMessage;
    encryptedMessage.resize(RSA_size(rsa));

    // Encriptar el mensaje
    int encryptedLength = RSA_private_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()),
                                             &result[0], rsa, RSA_PKCS1_PADDING);                                             

    RSA_free(rsa);
    if (encryptedLength == -1) {
        std::cerr << "Error al encriptar el mensaje" << std::endl;
        result[0] = 0;
    }
    
}

std::string Cifrado::decryptMessage(std::vector<unsigned char> encryptedMessage, const std::string& privateKeyPath) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        std::cerr << "Error al abrir el archivo de clave privada" << std::endl;
        return "";
    }
    std::cout<< encryptedMessage.size()<< " encriptar" <<std::endl;
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
     int decryptedLength = RSA_public_decrypt(512, reinterpret_cast<const unsigned char*>(&encryptedMessage[0]),
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

