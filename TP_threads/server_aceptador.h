#ifndef SERVER_ACEPTADOR_H_
#define SERVER_ACEPTADOR_H_

#include <list>
#include <string>
#include <utility>
#include "server_thread.h"
#include "common_socket.h"
#include "server_juego.h"
#include "server_handler.h"

class Hilo_aceptador: public Thread {
private:
    Socket skt;
    Juego juego;
    std::list<Handler*> handlers;

protected:
    void run(void) override;

public:
    explicit Hilo_aceptador(const std::string& servname);

    void close(void);

    void esperar_handlers(void);

    static bool esperarSiHaFinalizado(Handler* handler);

    void limpiar_handlers_finalizados(void);

    Hilo_aceptador(const Hilo_aceptador&) = delete;
    Hilo_aceptador& operator=(const Hilo_aceptador&) = delete;

    Hilo_aceptador(Hilo_aceptador&&) = delete;
    Hilo_aceptador& operator=(Hilo_aceptador&&) = delete;
};

#endif  // SERVER_ACEPTADOR_H_
