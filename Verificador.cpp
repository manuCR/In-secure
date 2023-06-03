#include <iostream>
#include <fstream>
#include <string>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

bool verifySignature(const std::string& publicKeyFile, const std::string& messageFile, const std::string& signatureFile) {
    // Cargar la clave pública desde el archivo CRT
    FILE* publicKeyFilePtr = fopen(publicKeyFile.c_str(), "r");
    if (!publicKeyFilePtr) {
        std::cerr << "Error al abrir el archivo de clave pública." << std::endl;
        return false;
    }
    RSA* rsa = PEM_read_RSA_PUBKEY(publicKeyFilePtr, NULL, NULL, NULL);
    fclose(publicKeyFilePtr);

    if (!rsa) {
        std::cerr << "Error al cargar la clave pública." << std::endl;
        return false;
    }

    // Leer el mensaje firmado
    std::ifstream messageStream(messageFile.c_str());
    if (!messageStream.is_open()) {
        std::cerr << "Error al abrir el archivo del mensaje firmado." << std::endl;
        RSA_free(rsa);
        return false;
    }
    std::string message((std::istreambuf_iterator<char>(messageStream)), std::istreambuf_iterator<char>());
    messageStream.close();

    // Leer la firma
    std::ifstream signatureStream(signatureFile.c_str());
    if (!signatureStream.is_open()) {
        std::cerr << "Error al abrir el archivo de la firma." << std::endl;
        RSA_free(rsa);
        return false;
    }
    std::string signature((std::istreambuf_iterator<char>(signatureStream)), std::istreambuf_iterator<char>());
    signatureStream.close();

    // Verificar la firma
    int result = RSA_verify(NID_sha256, reinterpret_cast<const unsigned char*>(message.c_str()), message.length(),
                            reinterpret_cast<const unsigned char*>(signature.c_str()), signature.length(), rsa);

    RSA_free(rsa);

    if (result != 1) {
        std::cerr << "La firma no es válida." << std::endl;
        return false;
    }

    std::cout << "La firma es válida. Se verificó la identidad del firmante." << std::endl;
    return true;
}
int main() {
    std::string publicKeyFile = "/home/valery.murcia/In-secure/Certificados/CAGrupo5.csr";
    std::string privateKeyFilePath = "/home/valery.murcia/In-secure/Certificados/CAGrupo5p.csr";

    std::string encryptedMessage = encryptMessage(message, publicKeyPath);


    std::string messageFile = "ruta_a_tu_mensaje_firmado.txt";
    std::string signatureFile = "ruta_a_tu_firma.txt";


    if (verifySignature(publicKeyFile, messageFile, signatureFile)) {
        // Aquí puedes realizar las acciones correspondientes cuando la firma es válida
    }

    return 0;
}
