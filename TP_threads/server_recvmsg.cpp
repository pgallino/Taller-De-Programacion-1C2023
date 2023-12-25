#include "server_recvmsg.h"

Hilo_RecvMsg::Hilo_RecvMsg(Server_protocol& protocol, 
    Queue<std::vector<char>>& cola, 
    Juego& juego,
    const std::atomic<bool>& keep_talking) :
    protocol(std::ref(protocol)),
    cola(std::ref(cola)),
    juego(std::ref(juego)),
    codigo_partida(0),
    is_running(true),
    keep_talking(keep_talking) {
}

void Hilo_RecvMsg::run() {
    uint8_t cod_accion;
    std::vector<char> mensaje;
    while (keep_talking) {
        bool was_closed = false;
        std::vector<char> comando = protocol.recibir_mensaje(cod_accion, &was_closed);
        if (was_closed) {
            cola.close();
            break;
        }
        if (cod_accion == CREATE) {
            logica_create(comando, mensaje);
        } else if (cod_accion == JOIN) {
            logica_join(comando, mensaje);
        } else if (cod_accion == BROADCAST) {
            logica_broadcast(comando, mensaje);
        }
        mensaje.clear();
    }
    is_running = false;
}

void Hilo_RecvMsg::logica_create(const std::vector<char>& comando, std::vector<char>&mensaje) {
    uint32_t cod_partida = juego.crear_partida(comando, &(this->cola));
    codigo_partida = cod_partida;
    cod_partida = ntohl(cod_partida);
    char *buf1 = (char*)&cod_partida;
    mensaje.insert(mensaje.end(), buf1, buf1 + CUATRO_BYTES);
    cola.push(mensaje);
}

void Hilo_RecvMsg::logica_join(const std::vector<char>& comando, std::vector<char>&mensaje) {
    uint32_t cod_partida = *(uint32_t*) comando.data();
    uint8_t ok = juego.unir_partida(cod_partida, &(this->cola));
    if (ok == 0) codigo_partida = cod_partida;
    char *buf1 = (char*)&ok;
    mensaje.insert(mensaje.end(), buf1, buf1 + UN_BYTE);
    cola.push(mensaje);
}

void Hilo_RecvMsg::logica_broadcast(const std::vector<char>& comando, std::vector<char>&mensaje) {
    mensaje.insert(mensaje.end(), UN_BYTE, READ);
    uint16_t largo = comando.size();
    largo = ntohs(largo);
    char *buf1 = (char*)&largo;
    mensaje.insert(mensaje.end(), buf1, buf1 + DOS_BYTES);
    mensaje.insert(mensaje.end(), comando.data(), comando.data() + comando.size());
    juego.broadcast_partida(codigo_partida, mensaje);
}

bool Hilo_RecvMsg::is_dead(void) const {
    return !is_running;
}
