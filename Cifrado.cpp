#include "Cifrado.hpp"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

Cifrado::Cifrado(Feedback * feedback){
    this->feedback = feedback;
}

std::vector<unsigned char> Cifrado::encryptMessage(const std::string& message, const std::string& privateKeyPath) {
    std::vector<unsigned char> result(512, 0);
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        feedback->agregarFeedback("Error al abrir el archivo de la llave privada");
        return result;
    }

    EVP_PKEY* privateKey = PEM_read_PrivateKey(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!privateKey) {
        feedback->agregarFeedback("Error al leer la llave privada");
        return result;
    }

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(privateKey, NULL);
    if (!ctx) {
        feedback->agregarFeedback("Error al crear el contexto de la llave privada");
        EVP_PKEY_free(privateKey);
        return result;
    }

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        feedback->agregarFeedback("Error al inicializar el cifrado de la llave privada");
        EVP_PKEY_free(privateKey);
        EVP_PKEY_CTX_free(ctx);
        return result;
    }

    size_t outputLen = result.size();
    if (EVP_PKEY_encrypt(ctx, &result[0], &outputLen, reinterpret_cast<const unsigned char*>(message.data()),
                         message.size()) <= 0) {
        feedback->agregarFeedback("Error al encriptar el mensaje");
        EVP_PKEY_free(privateKey);
        EVP_PKEY_CTX_free(ctx);
        return result;
    }

    EVP_PKEY_free(privateKey);
    EVP_PKEY_CTX_free(ctx);

    return result;
    
}

std::string Cifrado::decryptMessage(std::vector<unsigned char> encryptedMessage, const std::string& publicKeyPath) {
    // Cargar la clave privada
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
    if (!publicKeyFile) {
        return "";
    }
    EVP_PKEY* publicKey = PEM_read_PUBKEY(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);

    if (!publicKey) {
        feedback->agregarFeedback("Error al leer la llave pública");
        return "";
    }

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(publicKey, NULL);
    if (!ctx) {
        feedback->agregarFeedback("Error al crear el contexto de la llave pública");
        EVP_PKEY_free(publicKey);
        return "";
    }

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        feedback->agregarFeedback("Error al inicializar el descifrado de la llave pública");
        EVP_PKEY_free(publicKey);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }

    std::string decryptedMessage;
    decryptedMessage.resize(encryptedMessage.size());

    size_t outputLen = decryptedMessage.size();
    if (EVP_PKEY_decrypt(ctx, reinterpret_cast<unsigned char*>(&decryptedMessage[0]), &outputLen,
                         &encryptedMessage[0], encryptedMessage.size()) <= 0) {
        feedback->agregarFeedback("Error al descifrar el mensaje");
        EVP_PKEY_free(publicKey);
        EVP_PKEY_CTX_free(ctx);
        return "";
    }

    EVP_PKEY_free(publicKey);
    EVP_PKEY_CTX_free(ctx);

    decryptedMessage.resize(outputLen);
    return decryptedMessage;
}

