#include "Cifrado.hpp"


Cifrado::Cifrado(Feedback * feedback){
    this->feedback = feedback;
}

std::vector<unsigned char> Cifrado::encryptMessage(const std::string& message, const std::string& publicKeyPath) {
    // Cargar la clave pública
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
    if (!publicKeyFile) {
        printError("Error al abrir el archivo de clave privada",  false);
        return std::vector<unsigned char>(0);
    }

    RSA* rsa = PEM_read_RSAPrivateKey(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);

    if (!rsa) {
        printError("Error al leer la clave privada",  false);
        return std::vector<unsigned char>(0);
    }

    // Encriptar el mensaje
    std::vector<unsigned char> result{std::vector<unsigned char>(RSA_size(rsa), 0)};
    int encryptedLength = RSA_private_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()),
                                             &result[0], rsa, RSA_PKCS1_PADDING);                                             

    RSA_free(rsa);
    if (encryptedLength == -1) {
        printError("Error al encriptar el mensaje",  false);
    }

    return result;
    
}

std::string Cifrado::decryptMessage(std::vector<unsigned char> encryptedMessage, const std::string& privateKeyPath, bool tok) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        printError("Error al abrir el archivo de clave pública",  tok);
        return "";
    }
    RSA* rsa = PEM_read_RSA_PUBKEY(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        printError("Error al leer la clave pública",  tok);
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
        printError("Error al descifrar el mensaje",  tok);
        return "";
    }

    // Ajustar el tamaño del mensaje descifrado
    decryptedMessage.resize(decryptedLength);

    return decryptedMessage;
}

void Cifrado::printError(std::string mensaje, bool tok) {
    if (!tok) {
        feedback->agregarFeedback(mensaje);
    }
}

int Cifrado::chunkSize(const std::string& privateKeyPath) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        return 0;
    }
    RSA* rsa = PEM_read_RSAPrivateKey(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        printError("Error al leer la clave publica", false);
        return 0;
    }
    int rsaSize = RSA_size(rsa) - 42;
    RSA_free(rsa);
    return rsaSize;
}
