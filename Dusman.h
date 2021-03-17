#pragma once
#include "Karakter.h"
class Dusman :
    public Karakter
{
private:
	int hiz;

public:
	Dusman(int _id, string _ad, string _tur, int _hiz) : Karakter(_id, _ad, _tur) {
		this->hiz = _hiz;
	}

	Dusman() : Karakter()
	{

	}


};

