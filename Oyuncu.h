#pragma once
#include "Karakter.h"
class Oyuncu :
    public Karakter
{
private:
    int oyuncuId;
    string oyuncuAd;
    string oyuncuTur;
    int skor;

public:
    int PuaniGoster();

	/* Getters */
	int getOyuncuId() { return this->oyuncuId; }
	string getOyuncuAd() { return this->oyuncuAd; }
	string getOyuncuTur() { return this->oyuncuTur; }
	int getOyuncuSkor() { return this->skor; }



	/* Setters */
	void setOyuncuId(int oyuncuId) { this->oyuncuId = oyuncuId; }
	void setOyuncuAd(string oyuncuAd) { this->oyuncuAd = oyuncuAd; }
	void setOyuncuTur(string oyuncuTur) { this->oyuncuTur = oyuncuTur; }
	void setOyuncuSkor(int  skor) { this->skor = skor; }


};



