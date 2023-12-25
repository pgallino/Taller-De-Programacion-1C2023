#ifndef SERVER_SENDMSG_H_
#define SERVER_SENDMSG_H_

#include <atomic>
#include <vector>
#include "server_thread.h"
#include "server_queue.h"
#include "server_protocol.h"

class Hilo_SendMsg: public Thread {
private:
    Server_protocol& protocol; //por referencia
    Queue<std::vector<char>>& cola;
    std::atomic<bool> is_running;
    const std::atomic<bool>& keep_talking;

protected:
    /*popea de la cola el mensaje a enviar
    y lo envia al cliente*/
    void run() override;

public:
    Hilo_SendMsg(Server_protocol& protocol,
    Queue<std::vector<char>>& cola,
    const std::atomic<bool>& keep_talking);

    bool is_dead(void) const;

    Hilo_SendMsg(const Hilo_SendMsg&) = delete;
    Hilo_SendMsg& operator=(const Hilo_SendMsg&) = delete;

    Hilo_SendMsg(Hilo_SendMsg&&) = delete;
    Hilo_SendMsg& operator=(Hilo_SendMsg&&) = delete;
};

#endif  // SERVER_SENDMSG_H_
