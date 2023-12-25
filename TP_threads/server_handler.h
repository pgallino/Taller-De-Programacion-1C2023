// Copyright [2023] pgallino

#ifndef SERVER_HANDLER_H_
#define SERVER_HANDLER_H_

#include <utility>
#include <string>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <atomic>
#include "server_protocol.h"
#include "server_queue.h"
#include "server_juego.h"
#include "server_sendmsg.h"
#include "server_recvmsg.h"
#define MAX_SIZE 10

class Handler {
    private:
    Server_protocol server_protocol;
    Queue<std::vector<char>> cola;
    Juego& juego;
    std::atomic<bool> keep_talking;
    Hilo_SendMsg sendmsg;
    Hilo_RecvMsg recvmsg;

    public:
    Handler(Socket &&peer, Juego &juego);

    void lanzar_hilos(void);

    bool are_dead(void) const;

    void kill(void);
    void join(void);

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;

    Handler(Handler&&) = delete;
    Handler& operator=(Handler&&) = delete;
};

#endif  // SERVER_HANDLER_H_
