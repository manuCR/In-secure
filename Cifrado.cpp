#include "Cifrado.hpp"


Cifrado::Cifrado(Feedback * feedback){
    this->feedback = feedback;
}

std::vector<unsigned char> Cifrado::encryptMessage(const std::string& message, const std::string& publicKeyPath) {
    // Cargar la clave pública
    std::vector<unsigned char> result{std::vector<unsigned char>(512, 0)};
    FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
    if (!publicKeyFile) {
        feedback->agregarFeedback("Error al abrir el archivo de clave privada");
        return result;
    }

    RSA* rsa = PEM_read_RSAPrivateKey(publicKeyFile, NULL, NULL, NULL);
    fclose(publicKeyFile);

    if (!rsa) {
        feedback->agregarFeedback("Error al leer la clave privada");
        return result;
    }

    std::string encryptedMessage;
    encryptedMessage.resize(RSA_size(rsa));

    // Encriptar el mensaje
    int encryptedLength = RSA_private_encrypt(message.size(), reinterpret_cast<const unsigned char*>(message.data()),
                                             &result[0], rsa, RSA_PKCS1_PADDING);                                             

    RSA_free(rsa);
    if (encryptedLength == -1) {
        feedback->agregarFeedback("Error al encriptar el mensaje");
    }

    return result;
    
}

std::string Cifrado::decryptMessage(std::vector<unsigned char> encryptedMessage, const std::string& privateKeyPath) {
    // Cargar la clave privada
    FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
    if (!privateKeyFile) {
        feedback->agregarFeedback("Error al abrir el archivo de clave pública");
        return "";
    }
    RSA* rsa = PEM_read_RSA_PUBKEY(privateKeyFile, NULL, NULL, NULL);
    fclose(privateKeyFile);

    if (!rsa) {
        feedback->agregarFeedback("Error al leer la clave pública");
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
        feedback->agregarFeedback("Error al descifrar el mensaje");
        return "";
    }

    // Ajustar el tamaño del mensaje descifrado
    decryptedMessage.resize(decryptedLength);

    return decryptedMessage;
}



