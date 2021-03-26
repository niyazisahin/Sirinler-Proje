#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

struct blok {
	int x;
	int y;
	int dist;
	struct blok* parent;
};

class Karakter
{
private : 
	int id;
	string ad;
	string tur;
	sf::Vector2f pos;
	sf::Sprite *sprite;
	int hiz = 0;


public:
	Karakter(int  _id, string _ad, string _tur) : id(_id), ad(_ad), tur(_tur)
	{
		sprite = new sf::Sprite();
	}

	Karakter() : id(0), ad("Turk Robot"), tur("Korkusuz Turk")
	{ }

	/* Getters */
	int getId() { return this->id; }
	string getAd() { return this->ad; }
	string getTur() { return this->tur; }
	sf::Vector2f GetPos() { return pos; } // g küçük
	sf::Sprite* GetSprite() { return sprite; } // g küçük
	int getHiz() { return this->hiz; }

	/* Setters */
	void setId(int id) { this->id = id; }
	void setAd(string ad) { this->ad = ad; }
	void setTur(string tur) { this->tur = tur; }
	void setPos(sf::Vector2f pos);
	void setHiz(int hiz) { this->hiz = hiz; }


	struct blok* EnKýsaYol(char harita[11][13], sf::Vector2f hedefPos, vector<sf::Vector2f> dusman_liste); // (0,1)(0,2)

};

