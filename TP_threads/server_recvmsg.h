#ifndef SERVER_RECVMSG_H_
#define SERVER_RECVMSG_H_

#include <atomic>
#include <vector>
#include "server_thread.h"
#include "server_protocol.h"
#include "server_queue.h"
#include "server_juego.h"
#define CREATE 0x01
#define JOIN 0x02
#define BROADCAST 0x03
#define READ 0x04
#define CUATRO_BYTES 4
#define DOS_BYTES 2
#define UN_BYTE 1

class Hilo_RecvMsg: public Thread {
private:
    Server_protocol& protocol;  // por referencia
    Queue<std::vector<char>>& cola;
    Juego& juego;
    uint32_t codigo_partida;
    std::atomic<bool> is_running;
    const std::atomic<bool>& keep_talking;

    void logica_create(const std::vector<char>& comando,
    std::vector<char>&mensaje);
    void logica_join(const std::vector<char>& comando,
    std::vector<char>&mensaje);
    void logica_broadcast(const std::vector<char>& comando,
    std::vector<char>&mensaje);

protected:
    /*recibe un mensaje del cliente
    el juego procesa la accion
    pushea a la cola el mensaje a enviar*/
    void run() override;

public:
    Hilo_RecvMsg(Server_protocol& protocol,
    Queue<std::vector<char>>& cola,
    Juego& juego,
    const std::atomic<bool>& keep_talking);

    bool is_dead(void) const;

    Hilo_RecvMsg(const Hilo_RecvMsg&) = delete;
    Hilo_RecvMsg& operator=(const Hilo_RecvMsg&) = delete;

    Hilo_RecvMsg(Hilo_RecvMsg&&) = delete;
    Hilo_RecvMsg& operator=(Hilo_RecvMsg&&) = delete;
};

#endif  // SERVER_RECVMSG_H_
