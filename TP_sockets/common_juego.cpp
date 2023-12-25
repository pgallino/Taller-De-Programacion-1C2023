// Copyright [2022] pgallino

#include <string>
#include <cstdint>
#include <iostream>
#include <vector>
#include "common_juego.h"

Juego::Juego(const int limx, const int limy) {
    this->limx = limx;
    this->limy = limy;
}

void Juego::procesar_shooting(int8_t param) {
    if (param == 1 && rondas > 0) {
        this->shooting = true;
    } else {
        this->shooting = false;
    }
}
bool Juego::cambiar_posx(int8_t param1) {
    if ((0 <= (this->posx + param1)) &&
    ((this->posx + param1) < limx)) {
        this->posx += param1;
        this->dirx = param1;
        return true;
    }
    this->dirx = 0;
    return false;
}

bool Juego::cambiar_posy(int8_t param2) {
    if ((0 <= (this->posy + param2)) &&
    ((this->posy + param2) < limy)) {
        this->posy += param2;
        this->diry = param2;
        return true;
    }
    this->diry = 0;
    return false;
}


void Juego::procesar_moving(int8_t param1, int8_t param2) {
    if ((param1 == 0) && (param2 == 0)) {
        this->moving = false;
    } else if ((cambiar_posx(param1) && cambiar_posy(param2)) ||
    (cambiar_posy(param2) && (cambiar_posx(param1)))) {
        this->moving = true;
    } else {
        this->moving = false;
    }
}

void Juego::procesar_reload(void) {
    this->reloading = true;
    this->moving = false;
    this->shooting = false;
    this->rondas = 10;
}

// recibe un vector con comandos
void Juego::procesar_comandos(const std::vector<int8_t>& comandos) {
    if (rondas <= 0) this->shooting = false;
    int8_t accion = comandos[0];
    if (accion == 1) {
        procesar_shooting(comandos[1]);
        if (this->moving) {
            procesar_moving(this->dirx, this->diry);
        }
    } else if (accion == 2) {
        procesar_moving(comandos[1], comandos[2]);
    } else if (accion == 3) {
        procesar_reload();
    } else if (accion == 0) {
        if (this->moving) {
            procesar_moving(this->dirx, this->diry);
        }
    }
    if (this->shooting) this->rondas -= 1;
    this->reloading = false;
}

std::vector<uint16_t> Juego::devolver_estado(void) {
    std::vector<uint16_t> estado;
    if (!(this->shooting || this->moving || this->reloading)) {
        estado.push_back(0);
    } else if (this->shooting && this->moving) {
        estado.push_back(3);
    } else if (this->reloading) {
        estado.push_back(4);
    } else if (this->shooting) {
        estado.push_back(1);
    } else if (this->moving) {
        estado.push_back(2);
    }
    estado.push_back(this->posx);
    estado.push_back(this->posy);
    estado.push_back(this->rondas);
    return estado;
}
