// Copyright [2022] pgallino

#include "./client_protocol.h"

Client_protocol::Client_protocol(
        const std::string& hostname,
        const std::string& servname) :
    hostname(hostname),
    servname(servname),
    skt(hostname.c_str(), servname.c_str()) {
}

void Client_protocol::enviar_mensaje(std::vector<int8_t>& comando) {
    bool was_closed = false;
    skt.sendall(comando.data(), comando.size(), &was_closed);
}

std::vector<uint16_t> Client_protocol::recibir_mensaje() {
    bool was_closed = false;

    /* ya se que va a tener 4 lugares*/
    std::vector<uint16_t> mensaje = {0, 0, 0, 0};

    /* obtengo accion */
    skt.recvall(&mensaje[0], 1, &was_closed);

    /* obtengo numeros */
    for (int i = 1; i < 4; i++) {
        skt.recvall(&mensaje[i], 2, &was_closed);
        mensaje[i] = htons(mensaje[i]);
    }
    return mensaje;
}
