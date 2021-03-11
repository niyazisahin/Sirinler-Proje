#pragma once
#include "Oyuncu.h"
#include <iostream>

class Tembel :
    public Oyuncu
{
private:

public:
    Tembel(int _id, string _ad, int _skor) : Oyuncu(_id, _ad, "oyuncu", _skor) {

        this->setHiz(1);

    }
};

