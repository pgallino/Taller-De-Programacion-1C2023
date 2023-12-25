// Copyright [2023] pgallino

#include "./client_protocol.h"
#define DOS_BYTES 2
#define UN_BYTE 1
#define CUATRO_BYTES 4

Client_protocol::Client_protocol(
        const std::string& hostname,
        const std::string& servname) :
    hostname(hostname),
    servname(servname),
    skt(hostname.c_str(), servname.c_str()) {
}

void Client_protocol::enviar_mensaje(const uint8_t& codigo, const std::string& mensaje) {
    bool was_closed = false;
    std::vector<char> partial;
    if (codigo == CREATE) {
        armar_mensaje_largo_x(partial, mensaje, codigo);
    } else if (codigo == JOIN) {
        uint32_t num_cod = stoi(mensaje);
        num_cod= ntohl(num_cod);
        char *cod = (char*)&num_cod;
        partial.insert(partial.end(), UN_BYTE, codigo);
        partial.insert(partial.end(), cod, cod + CUATRO_BYTES);
    } else if (codigo == BROADCAST) {
        armar_mensaje_largo_x(partial, mensaje, codigo);
    }
    skt.sendall(partial.data(), partial.size(), &was_closed);
}

std::vector<char> Client_protocol::recibir_mensaje(const uint8_t& codigo) {
    bool was_closed = false;
    std::vector<char> partial;
    if (codigo == CREATE) {
        char buf[CUATRO_BYTES] = {0};
        skt.recvall(buf, CUATRO_BYTES, &was_closed);
        uint32_t cod = *(uint32_t*) buf;
        cod = htonl(cod);
        char *buf1 = (char*)&cod;
        partial.insert(partial.end(), buf1, buf1 + CUATRO_BYTES);
    } else if (codigo == JOIN) {
        char buf[UN_BYTE] = {0};
        skt.recvall(buf, UN_BYTE, &was_closed);
        partial.insert(partial.end(), buf, buf + UN_BYTE);
    } else if (codigo == READ) {
        char buf[UN_BYTE] = {0};
        skt.recvall(buf, UN_BYTE, &was_closed);
        char buf1[DOS_BYTES] = {0};
        skt.recvall(buf1, DOS_BYTES, &was_closed);
        uint16_t largo = *(uint16_t*) buf1;
        largo = htons(largo);
        char* buf2 = (char*) malloc(sizeof(char) * largo);
        char* buf3 = buf2;
        skt.recvall(buf3, largo, &was_closed);
        partial.insert(partial.end(), buf3, buf3 + largo);
        free(buf2);
    }
    return partial;
}

void Client_protocol::armar_mensaje_largo_x(std::vector<char>& partial,
    const std::string& mensaje,
    const uint8_t& codigo) {
    uint16_t largo = mensaje.size();
    largo = ntohs(largo);
    char *largo_char = (char*)&largo;
    partial.insert(partial.end(), UN_BYTE, codigo);
    partial.insert(partial.end(), largo_char, largo_char + DOS_BYTES);
    partial.insert(partial.end(), mensaje.data(), mensaje.data() + mensaje.size());
}
