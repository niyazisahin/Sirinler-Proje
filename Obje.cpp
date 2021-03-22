#include "Obje.h"

void Obje::setPos(sf::Vector2f pos) {
	this->sprite->setPosition(pos);
	this->pos = pos;
}
