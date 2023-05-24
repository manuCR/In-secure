#include <iostream>
#include <cstdlib>

int main() {
    // Generar clave RSA
    //std::system("openssl genrsa -out key.pem 2048");

    // Mostrar información de la clave privada
    //std::system("openssl rsa -in key.pem -text -noout");

    // Guardar clave pública en el archivo "pub.pem"
    //std::system("openssl rsa -in key.pem -pubout -out pub.pem");

    // Mostrar información de la clave pública
    //std::system("openssl rsa -in pub.pem -pubin -text -noout");

    // Encriptar datos
    std::system("openssl rsautl -encrypt -inkey pub.pem -pubin -in Archivo.txt -out Archivo.bin");

    // Desencriptar datos encriptados
    std::system("openssl rsautl -decrypt -inkey key.pem -in Archivo.bin");

    return 0;
}
