#pragma once
#include "Karakter.h"
class Dusman :
    public Karakter
{
private:
	int dusmanId;
	string dusmanAd;
	string dusmanTur;

public:
	int PuaniGoster();

	/* Getters */
	int getOyuncuId() { return this->dusmanId; }
	string getOyuncuAd() { return this->dusmanAd; }
	string getOyuncuTur() { return this->dusmanTur; }




	/* Setters */
	void setDusmanId(int dusmanId) { this->dusmanId = dusmanId; }
	void setOyuncuAd(string dusmanAd) { this->dusmanAd = dusmanAd; }
	void setOyuncuTur(string dusmanTur) { this->dusmanTur = dusmanTur; }

};

