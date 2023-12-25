#include "server_aceptador.h"

Hilo_aceptador::Hilo_aceptador(const std::string& servname) :
    skt(servname.c_str()),
    juego() {
}

void Hilo_aceptador::run(void) { try {
    while (true) {
        Socket peer = skt.accept();
        Handler* handler = new Handler(std::move(peer), std::ref(juego));
        handlers.push_back(handler);
        handler->lanzar_hilos();
        limpiar_handlers_finalizados();
    }
    } catch (const SktError& err) {
        esperar_handlers();
    } catch (...) {
        std::cerr << "Something went wrong\n";
    }
}

void Hilo_aceptador::close(void) {
    skt.shutdown(2);
    skt.close();
}

void Hilo_aceptador::esperar_handlers(void) {
    for (auto & handler : handlers) {
        if (!handler->are_dead()) (handler)->kill();
        (handler)->join();
        delete handler;
    }
    handlers.clear();
}

void Hilo_aceptador::limpiar_handlers_finalizados(void) {
    handlers.remove_if([](Handler* handler) { 
        if (handler->are_dead()) {
            handler->join();
            delete handler;
            return true;
        }
        return false;
    });
}
