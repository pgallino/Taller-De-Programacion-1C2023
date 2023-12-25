// Copyright [2022] pgallino

#ifndef COMMON_JUEGO_H_
#define COMMON_JUEGO_H_
#include <string>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>

/*Clase correspondiente a la lógica del juego*/

class Juego {
    private:
    bool shooting = false;
    bool moving = false;
    bool reloading = false;
    int posx = 0;
    int posy = 0;
    int limx;
    int limy;
    int dirx = 0;
    int diry = 0;
    int rondas = 10;

    /*ejecuta comando shooting*/
    void procesar_shooting(int8_t param);

    /*cambia posx*/
    bool cambiar_posx(int8_t param1);

    /*cambia posy*/
    bool cambiar_posy(int8_t param2);

    /*ejecuta comando mooving*/
    void procesar_moving(int8_t param1, int8_t param2);

    /*ejecuta comando reload*/
    void procesar_reload(void);

    public:
    explicit Juego(const int limx, const int limy);

    /*recibe conjunto de comandos y los ejecuta*/
    void procesar_comandos(const std::vector<int8_t>& comandos);

    /*retorna estado del juego*/
    std::vector<uint16_t> devolver_estado(void);

    Juego(const Juego&) = delete;
    Juego& operator=(const Juego&) = delete;

    Juego(Juego&&) = delete;
    Juego& operator=(Juego&&) = delete;
};

#endif  // COMMON_JUEGO_H_
