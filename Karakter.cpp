#include "Karakter.h"

int** Karakter::EnK�saYol() {

}

void Karakter::KarakterResimYukle(sf::Texture texture) {

	this->sprite.setTexture(texture);

}

void Karakter::SetPos(sf::Vector2f pos) {
	this->pos = pos;
}

