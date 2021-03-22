#pragma once
#include "Obje.h"

#define MANTAR_PUAN 50

class Mantar :
    public Obje
{
public:
    int olum_suresi = 7;

    void sure_azalt() {
        this->olum_suresi -= 1;
    }

    Mantar(int _id, string _tip, sf::Vector2f _pos) : Obje(_id, _tip, _pos, MANTAR_PUAN) {

    }

};

