#pragma once
#include "Karakter.h"
class Oyuncu :
	public Karakter
{
private:
	int skor = 0;

public:
	/* Constructor */
	Oyuncu(int _id, string _ad, string _tur, int _skor) : Karakter(_id, _ad, _tur) {
		this->skor = _skor;
	}

	Oyuncu() : Karakter() {
		this->skor = 0;
	}

	void PuaniGoster(sf::RenderWindow* puan_ekrani);

	/* Getters */
	int getOyuncuSkor() { return this->skor; }


	/* Setters */
	void setOyuncuSkor(int  skor) { this->skor = skor; }


};


