// Copyright [2023] pgallino

#include "./server_partida.h"
#define EXITO 1
#define FALLO 0

Partida::Partida(
    uint32_t codigo,
    const std::vector<char>& scenario) :
    codigo(codigo),
    scenario(scenario),
    jugadores() {
}

void Partida::agregar_jugador(Queue<std::vector<char>>* jugador) {
    jugadores.push_back(jugador);
}

void Partida::push_broadcast(const std::vector<char>& mensaje) {
    for (auto & jugador : jugadores) { try {
        jugador->push(mensaje);
    } catch (ClosedQueue& err) {
        continue;
    }
    }
}

void Partida::limpiar_jugadores(void) {
    jugadores.erase(std::remove_if(jugadores.begin(),
    jugadores.end(),
    [&](const Queue<std::vector<char>>* jugador)
    { return jugador->is_closed(); }),
    jugadores.end());
}
