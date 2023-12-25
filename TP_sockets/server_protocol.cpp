// Copyright [2022] pgallino

#include "./server_protocol.h"

Protocol_server::Protocol_server(
        const std::string& servname) :
    servname(servname),
    skt(servname.c_str()),
    peer(skt.accept()) {
}

std::vector<int8_t> Protocol_server::recibir_mensaje(bool *was_closed) {
    char buf[2] = {0};
    std::vector<int8_t> comandos;
    for (int i = 0; i < 3; i++) {
        peer.recvall(buf, 1, was_closed);
        int8_t comando = *(int8_t*) buf;
        if (i == 0) {
            comandos.push_back(comando);
            if (comando == NOP || comando == RELOAD) break;
            continue;
        }
        if (comandos[0] == SHOOTING && (i == 1)) {
            comandos.push_back(comando);
            break;
        }
        comandos.push_back(comando);
    }
    return comandos;
}

void Protocol_server::enviar_mensaje(std::vector<uint16_t>& mensaje) {
    std::vector<uint8_t> mensaje_serializado;
    mensaje_serializado.push_back((uint8_t) mensaje[0]);
    for (int i = 1; i < 4; i++) {
        uint8_t partA = (uint8_t)((mensaje[i] & 0xFF00) >> 8);
        uint8_t partB = (uint8_t)(mensaje[i] & 0x00FF);
        mensaje_serializado.push_back(partA);
        mensaje_serializado.push_back(partB);
    }
    bool was_closed = false;
    peer.sendall(mensaje_serializado.data(), 7, &was_closed);
}

