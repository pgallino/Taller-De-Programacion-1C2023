// Copyright [2023] pgallino

#include <utility>
#include "server_protocol.h"
#define DOS_BYTES 2
#define UN_BYTE 1
#define CUATRO_BYTES 4
#define CREATE 0X01
#define JOIN 0x02
#define BROADCAST 0x03

Server_protocol::Server_protocol(
        Socket &&aceptado) :
    skt(std::move(aceptado)) {
}

std::vector<char> Server_protocol::recibir_mensaje(uint8_t& cod_accion, bool* was_closed) {
    std::vector<char> partial;
    char buf[UN_BYTE] = {0};
    skt.recvall(buf, UN_BYTE, was_closed);
    uint8_t accion = *(uint8_t*) buf;
    cod_accion = accion;
    if (accion == CREATE) {
        recibir_x_longitud(partial, was_closed);
    } else if (accion == JOIN) {
        recibir_4_bytes(partial, was_closed);
    } else if (accion == BROADCAST) {
        recibir_x_longitud(partial, was_closed);
    }
    return partial;
}

void Server_protocol::enviar_mensaje(const std::vector<char>& mensaje, bool* was_closed) {
    skt.sendall(mensaje.data(), mensaje.size(), was_closed);
}

void Server_protocol::recibir_x_longitud(std::vector<char>& partial, bool* was_closed) {
    char buf1[DOS_BYTES] = {0};
    skt.recvall(buf1, DOS_BYTES, was_closed);
    uint16_t largo = *(uint16_t*) buf1;
    largo = htons(largo);
    char* buf2 = (char*) malloc(sizeof(char) * largo);
    skt.recvall(buf2, largo, was_closed);
    partial.insert(partial.end(), buf2, buf2 + largo);
    free(buf2);
}

void Server_protocol::recibir_4_bytes(std::vector<char>& partial, bool* was_closed) {
    char buf1[CUATRO_BYTES] = {0};
    skt.recvall(buf1, CUATRO_BYTES, was_closed);
    uint32_t codigo = *(uint32_t*) buf1;
    codigo = htonl(codigo);
    char *buf2 = (char*)&codigo;
    partial.insert(partial.end(), buf2, buf2 + CUATRO_BYTES);
}

void Server_protocol::close_socket(void) {
    skt.shutdown(2);
    skt.close();
}
