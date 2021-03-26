#include "Oyuncu.h"

#define KUP_BOYUT 70
#define KENAR_BOSLUK 100

#define SAG_BORDER (13 * KUP_BOYUT + KENAR_BOSLUK)
#define ALT_BORDER (11 * KUP_BOYUT + KENAR_BOSLUK)

using namespace std;

void Oyuncu::PuaniGoster(sf::RenderWindow* puan_ekrani) {
	
	sf::Text puan;
	sf::Font font;

	font.loadFromFile("arial.ttf");
	puan.setFont(font);

	puan.setString("Oyuncu Puani : " + to_string(this->skor));
	puan.setPosition(sf::Vector2f(SAG_BORDER -200,  20));
	puan.setFillColor(sf::Color::Black);
	
	puan.setCharacterSize(25);
	puan_ekrani->draw(puan);
}


