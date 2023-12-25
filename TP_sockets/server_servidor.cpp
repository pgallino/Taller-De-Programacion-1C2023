// Copyright [2022] pgallino

#include "./server_servidor.h"

Server::Server(
        const std::string& servname, 
        const int limx,
        const int limy) :
    protocol(servname),
    juego(limx, limy) {
}

void Server::start(void) {
    bool was_closed = false;
    while (!was_closed) {
        std::vector<int8_t> comando = protocol.recibir_mensaje(&was_closed);
        if (was_closed) break;
        juego.procesar_comandos(comando);
        std::vector<uint16_t> estado = juego.devolver_estado();
        protocol.enviar_mensaje(estado);
        imprimir_estado(estado);
    }
}

void Server::imprimir_estado(const std::vector<uint16_t>& estado) {
    if (estado[0] == 0) {
        std::cout << "Shooting? 0\n";
        std::cout << "Moving? 0\n";
        std::cout << "Reloading? 0\n";
    } else if (estado[0] == 1) {
        std::cout << "Shooting? 1\n";
        std::cout << "Moving? 0\n";
        std::cout << "Reloading? 0\n";
    } else if (estado[0] == 2) {
        std::cout << "Shooting? 0\n";
        std::cout << "Moving? 1\n";
        std::cout << "Reloading? 0\n";
    } else if (estado[0] == 3) {
        std::cout << "Shooting? 1\n";
        std::cout << "Moving? 1\n";
        std::cout << "Reloading? 0\n";
    } else {
        std::cout << "Shooting? 0\n";
        std::cout << "Moving? 0\n";
        std::cout << "Reloading? 1\n";
    }
    std::cout << "Position? " << estado[1] << " " << estado[2] << "\n";
    std::cout << "Rounds? " << estado[3] << "\n\n";
}
