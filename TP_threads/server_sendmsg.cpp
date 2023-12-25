#include "server_sendmsg.h"

Hilo_SendMsg::Hilo_SendMsg(Server_protocol& protocol,
    Queue<std::vector<char>>& cola,
    const std::atomic<bool>& keep_talking) :
    protocol(std::ref(protocol)),
    cola(std::ref(cola)),
    is_running(true),
    keep_talking(keep_talking) {
}

void Hilo_SendMsg::run() { try {
    while (keep_talking) {
        bool was_closed = false;
        std::vector<char> mensaje = cola.pop();
        protocol.enviar_mensaje(mensaje, &was_closed);
        if (was_closed) break;
    }
    is_running = false;
    } catch (ClosedQueue& err) {
        is_running = false;
    }
}

bool Hilo_SendMsg::is_dead(void) const {
    return !is_running;
}
