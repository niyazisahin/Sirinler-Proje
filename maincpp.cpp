#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Oyuncu.h"
#include "Gozluklu.h"

using namespace std;


#define BASLANGICX 555 + 180
#define BASLANGICY 360 + 90

int main()
{
	sf::RenderWindow window(sf::VideoMode(1570, 990), "sirineyi Kurtar!");
	sf::RectangleShape rect[143];


	sf::Color black = sf::Color::Black;
	sf::Color white = sf::Color::White;
	sf::Color red = sf::Color::Red;
	sf::Color green = sf::Color::Green;
	sf::Color blue = sf::Color::Blue;
	sf::Color yellow = sf::Color::Yellow;
	sf::Color magenta = sf::Color::Magenta;
	sf::Color cyan = sf::Color::Cyan;
	sf::Color transparent = sf::Color::Transparent;
	sf::Color gray = sf::Color(128, 128, 128);
	sf::Color pink = sf::Color(255, 192, 203);
	//sf::Color gray = sf::Color(128, 128, 128);


	/* Texturelar */
	sf::Texture texture_gozluklu;

	if (!texture_gozluklu.loadFromFile("gozluklu.png")) {
		cout << "Gozluklu yuklenemedi" << endl;
	}

	/* Oyuncu */

	Gozluklu gozluklu(0, "gozluklu", 0);
	gozluklu.GetSprite()->setPosition(BASLANGICX, BASLANGICY);
	gozluklu.GetSprite()->setScale(sf::Vector2f(0.18, 0.18));
	gozluklu.GetSprite()->setTexture(texture_gozluklu);
	
	/* Harita Jenerasyonu */
	char haritaDizi[11][13];
	int ix = 0;
	int jx = 0;
	char ch;
	fstream fin("harita.txt", fstream::in);
	while (fin >> noskipws >> ch) {

		if (ch == '1' || ch == '0') {
			/*continue;*/

			haritaDizi[ix][jx] = ch;

			cout << " " << ix << " " << jx;

			if (ix == 10 && jx == 12)
				break;

			if (jx == 12)
			{
				ix++;
				ix = ix % 11;
				cout << "\n";
			}
			jx++;
			jx = jx % 13;
		}

	}
	cout << "\n\n";

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 13; j++) {
			printf(" %c ", haritaDizi[i][j]);
		}
		cout << "\n";
	}


	/* Game Loop */
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(white); // Ekran bufferýný beyaz yap

		/* Küp baþlangýç kordinatlarý */
		float x = 200, y = 0;
		int sayac = 0;

		for (int i = 0; i < 11; i++) {

			for (int j = 0; j < 13; j++) {

				if (haritaDizi[i][j] == '1')
				{
					rect[sayac].setFillColor(white);
				}
				else {

					rect[sayac].setFillColor(gray);
				}

				/* Küplerin Ayarlanmasý */
				rect[sayac].setSize(sf::Vector2f(90, 90));
				rect[sayac].setPosition(x, y);
				rect[sayac].setOutlineColor(black);
				rect[sayac].setOutlineThickness(1.0f);

				/* Pencereye çizmek */
				window.draw(rect[sayac]);
				sayac++;
				x += 90;
			}
			y += 90;
			x = 200;

		}

		// Baþlangýç noktasý (mavi)
		rect[71].setFillColor(blue);

		/* Drawing objects */
		window.draw(rect[71]);
		window.draw(*(gozluklu.GetSprite()));

		window.display();

	}

	return 0;
}