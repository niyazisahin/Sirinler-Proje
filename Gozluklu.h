#pragma once
#include "Oyuncu.h"
#include <iostream>

class Gozluklu :
    public Oyuncu
{
private:

public:
    Gozluklu(int _id, string _ad, int _skor) : Oyuncu(_id, _ad, "oyuncu", _skor) {
        
        this->setHiz(2);

    }

};

