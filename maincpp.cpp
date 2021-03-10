#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;


int main()
{
	sf::RenderWindow window(sf::VideoMode(1170, 990), "sirineyi Kurtar!");
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


	sf::Texture sirine;
	sf::Texture gargamel;

	if (!sirine.loadFromFile("sirine.png")) {
		cout << "Sirine yüklenmedi";
	}


	if (!gargamel.loadFromFile("gargamel.png")) {
		cout << "Gargamel yüklenmedi!";
	}

	sf::Sprite spriteSirine(sirine);
	spriteSirine.setScale(sf::Vector2f(0.1, 0.1));
	
	sf::Sprite spriteGargamel(gargamel);
	spriteGargamel.setScale(sf::Vector2f(0.1, 0.1));


	spriteSirine.setPosition(1090, 630);


	char haritaDizi[11][13];
	int ix = 0;
	int jx = 0;
	char ch;
	fstream fin("harita.txt", fstream::in);
	while (fin >> noskipws >> ch) {

		//cout << ch; // Or whatever


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

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();


		float x = 0, y = 0;

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
				rect[sayac].setSize(sf::Vector2f(90, 90));
				rect[sayac].setPosition(x, y);
				window.draw(rect[sayac]);
				sayac++;
				x += 90;
			}
			y += 90;
			x = 0;

		}
		// Baþlangýç noktasý (mavi)
		rect[71].setFillColor(blue);
		window.draw(rect[71]);

		window.draw(spriteSirine);
		window.draw(spriteGargamel);
		window.display();
		int adim = 90;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			// left key is pressed: move our character
			spriteSirine.setPosition(1090-adim, 630);
		}

	}

	return 0;
}