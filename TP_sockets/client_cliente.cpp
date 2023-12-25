// Copyright [2022] pgallino

#include "./client_cliente.h"
#include <fstream>

Client::Client(
        const std::string& hostname,
        const std::string& servname,
        const std::string& nombre_archivo) :
    protocol(hostname, servname),
    parser(),
    nombre_archivo(nombre_archivo) {
}

void Client::start(void) {
    std::string linea;
    std::ifstream archivo(nombre_archivo.c_str());
    while (getline(archivo, linea)) {
        std::vector<int8_t> comandos = parser.procesar_linea_comandos(linea);
        if ((comandos.size()) == 0) continue;
        protocol.enviar_mensaje(comandos);
        std::vector<uint16_t> respuesta = protocol.recibir_mensaje();
        procesar_respuesta(respuesta);
    }
}

void Client::procesar_respuesta(
    const std::vector<uint16_t>& respuesta) {
    uint16_t accion = respuesta[0];
    if (accion == IDLE) {
        std::cout << "Shooting? 0\n";
        std::cout << "Moving? 0\n";
        std::cout << "Reloading? 0\n";
    } else if (accion == SHOOTING) {
        std::cout << "Shooting? 1\n";
        std::cout << "Moving? 0\n";
        std::cout << "Reloading? 0\n";
    } else if (accion == MOVING) {
        std::cout << "Shooting? 0\n";
        std::cout << "Moving? 1\n";
        std::cout << "Reloading? 0\n";
    } else if (accion == SHO_MOV) {
        std::cout << "Shooting? 1\n";
        std::cout << "Moving? 1\n";
        std::cout << "Reloading? 0\n";
    } else {
        std::cout << "Shooting? 0\n";
        std::cout << "Moving? 0\n";
        std::cout << "Reloading? 1\n";
    }
    std::cout << "Position? " << respuesta[1] << " " << respuesta[2] << "\n";
    std::cout << "Rounds? " << respuesta[3] << "\n\n";
}
