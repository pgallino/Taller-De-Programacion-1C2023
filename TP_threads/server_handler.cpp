// Copyright [2023] pgallino

#include "./server_handler.h"

Handler::Handler(Socket &&peer, Juego &juego) : 
    server_protocol(std::move(peer)),
    cola(MAX_SIZE),
    juego(std::ref(juego)),
    keep_talking(true),
    sendmsg(std::ref(server_protocol), std::ref(cola), std::ref(keep_talking)),
    recvmsg(std::ref(server_protocol), std::ref(cola), std::ref(juego),
    std::ref(keep_talking)) {
}

void Handler::lanzar_hilos(void) {
    recvmsg.start();
    sendmsg.start();
}

bool Handler::are_dead(void) const {
    return ((sendmsg.is_dead()) && (recvmsg.is_dead()));
}

void Handler::join(void) {
    recvmsg.join();
    sendmsg.join();
}

void Handler::kill(void) {
    keep_talking = false;
    server_protocol.close_socket();
    //cola.close();
}
