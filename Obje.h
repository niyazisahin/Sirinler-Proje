#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
class Obje
{
private:
	int id;
	string tip;
	sf::Vector2f pos;
	sf::Sprite* sprite;
	int puan;


public:
	Obje(int _id, string _tip, sf::Vector2f _pos, int _puan)
	{
		this->id = _id;
		this->tip = _tip;
		this->sprite = new sf::Sprite();
		this->setPos(_pos);
		this->puan = _puan;

	}

	int getId() { return id; }
	string getTip() { return tip; }
	sf::Vector2f getPos() { return pos; }
	sf::Sprite* getSprite() { return sprite; }
	int getPuan() { return puan; }

	void setId(int _id) { this->id = _id; }
	void setTip(string _tip) { this->tip = _tip; }
	void setSprite(sf::Sprite* _sprite) { this->sprite = _sprite; }
	void setPos(sf::Vector2f pos);
	void setPuan(int _puan) { this->puan = _puan; }


};

