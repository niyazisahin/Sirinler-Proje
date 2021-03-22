#pragma once
#include "Obje.h"

#define ALTIN_PUAN 5

class Alt�n :
    public Obje
{
public:
    
    int olum_suresi = 5;

    void sure_azalt() {
        this->olum_suresi -= 1;
    }

    Alt�n(int _id, string _tip, sf::Vector2f _pos) : Obje(_id, _tip, _pos, ALTIN_PUAN) {

    }
};

