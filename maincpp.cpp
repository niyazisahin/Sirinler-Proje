#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Oyuncu.h"
#include "Gozluklu.h"
#include "Gargamel.h"
#include "Azman.h"
#include <string.h>
#include <map>

using namespace std;

#define KENAR_BOSLUK 100

#define SAG_BORDER 13 * KUP_BOYUT + KENAR_BOSLUK
#define SOL_BORDER KENAR_BOSLUK
#define ALT_BORDER 11 * KUP_BOYUT + KENAR_BOSLUK
#define UST_BORDER KENAR_BOSLUK

#define ADIM_X 70
#define ADIM_Y 70

#define KUP_BOYUT 70

#define BASLANGICX 6 * KUP_BOYUT + KENAR_BOSLUK
#define BASLANGICY 5 * KUP_BOYUT + KENAR_BOSLUK


bool border_kontrol(sf::Vector2f pos, char harita[11][13]) {

	sf::Vector2f goreceli_pos = pos - sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK);
	int x  = (int)(goreceli_pos.x / ADIM_X);
	int y = (int)(goreceli_pos.y / ADIM_Y);
	cout << y << "-" << x << endl;

	if (harita[y][x] == '0')
		return false;
		
	cout << pos.x << "-" << pos.y << endl;

	if (pos.x < SOL_BORDER - 1 || pos.x > SAG_BORDER - KUP_BOYUT + 1)
		return false;

	if (pos.y < UST_BORDER - 1 || pos.y > ALT_BORDER - KUP_BOYUT + 1) 
		return false;

	return true;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(2 * KENAR_BOSLUK + 13 * KUP_BOYUT, 2 * KENAR_BOSLUK + 11 * KUP_BOYUT), "sirineyi Kurtar!");
	sf::RectangleShape rect[143];

	Dusman duzman_dizi[2];

	bool flag_left  = true;
	bool flag_right = true;
	bool flag_up    = true;
	bool flag_down  = true;

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

	map<char, sf::Vector2f> dusman_pozisyon = {
	{ 'A', sf::Vector2f(KENAR_BOSLUK + 3 * KUP_BOYUT, KENAR_BOSLUK) },
	{ 'B', sf::Vector2f(KENAR_BOSLUK + 10 * KUP_BOYUT, KENAR_BOSLUK) },
	{ 'C', sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK + 6 * KUP_BOYUT) },
	{ 'D', sf::Vector2f(KENAR_BOSLUK + 3 * KUP_BOYUT, ALT_BORDER) }
	};

	/* Texturelar */
	sf::Texture texture_gozluklu;

	if (!texture_gozluklu.loadFromFile("gozluklu.png")) {
		cout << "Gozluklu yuklenemedi" << endl;
	}

	sf::Texture texture_gargamel;

	if (!texture_gargamel.loadFromFile("gargamel.png")) {
		cout << "Gargamel yuklenemedi" << endl;
	}

	sf::Texture texture_azman;

	if (!texture_azman.loadFromFile("azman.png")) {
		cout << "azman yuklenemedi" << endl;
	}

	/* Oyuncu */
	Gozluklu gozluklu(0, "gozluklu", 0);
	gozluklu.setPos(sf::Vector2f(BASLANGICX, BASLANGICY));
	gozluklu.GetSprite()->setScale(sf::Vector2f(0.14, 0.14));
	gozluklu.GetSprite()->setTexture(texture_gozluklu);

	/* Harita Jenerasyonu */
	char haritaDizi[11][13];
	int ix = 0;
	int jx = 0;
	int sayac = 0;
	char ch;

	fstream fin("harita.txt", fstream::in);
	while ((char)fin.peek() != '0' && (char)fin.peek() != '1') {

		string m; // raw veri
		getline(fin, m);
		int flag = 0;

		/* Dosyadan okunacak veri */
		string veri;
	
		for (char x : m) {
			
			/* Kelime Atla */
			if (x != ':' && flag == 0)
				continue;
			else
				flag = 1;

			if (x == ','){
				flag = 0;
				continue;
			}

			if(x != ':')
				veri += x;

		}

		/* Dusman bilgileri */
		char karakter_tip = veri[0];
		char pozisyon = veri[veri.length() - 1];

		cout << veri << endl;
		cout << karakter_tip << ':' << pozisyon << endl;

		switch (karakter_tip) {

			case 'A' : 
			{
				Azman azman(sayac+1, "azman");
				azman.setPos(dusman_pozisyon[pozisyon]);
				azman.GetSprite()->setScale(sf::Vector2f(0.15, 0.15));
				azman.GetSprite()->setTexture(texture_azman);
				duzman_dizi[sayac++] = azman;
			}
			break;

			case 'G' :
			{
				Gargamel gargamel(sayac+1, "gargamel");
				gargamel.setPos(dusman_pozisyon[pozisyon]);
				gargamel.GetSprite()->setScale(sf::Vector2f(0.035, 0.035));
				gargamel.GetSprite()->setTexture(texture_gargamel);
				duzman_dizi[sayac++] = gargamel;
			}
			break;

		}
	}

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


		/* Keyboard input */
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		/// ///////////////////LEFT////////////////////////
		if (left && flag_left) {

			// yürüceði pozisyon
			sf::Vector2f gelecek_pos = gozluklu.GetPos() + sf::Vector2f(-ADIM_X, 0);

			if (border_kontrol(gelecek_pos, haritaDizi))
				gozluklu.setPos(gelecek_pos);

			cout << "sol tusa tiklandi" << endl;
			flag_left = false;

		} else if (!left && !flag_left)
			flag_left = true;
		/// ///////////////////////////////////////////////


		/// ///////////////////RIGHT/////////////////////////
		if (right && flag_right) {

			// yürüceði pozisyon
			sf::Vector2f gelecek_pos = gozluklu.GetPos() + sf::Vector2f(ADIM_X, 0);

			if (border_kontrol(gelecek_pos, haritaDizi))
				gozluklu.setPos(gelecek_pos);

			cout << "sag tusa tiklandi" << endl;
			flag_right = false;

		}
		else if (!right && !flag_right)
			flag_right = true;
		/// ///////////////////////////////////////////////


		/// ///////////////////UP//////////////////////////
		if (up && flag_up) {

			// yürüceði pozisyon
			sf::Vector2f gelecek_pos = gozluklu.GetPos() + sf::Vector2f(0, -ADIM_Y);

			if (border_kontrol(gelecek_pos, haritaDizi))
				gozluklu.setPos(gelecek_pos);

			cout << "yukari tusa tiklandi" << endl;

			flag_up = false;
		}
		else if (!up && !flag_up)
			flag_up = true;
		/// ///////////////////////////////////////////////


		/// //////////////////DOWN//////////////////////////
		if (down && flag_down) {

			// yürüceði pozisyon
			sf::Vector2f gelecek_pos = gozluklu.GetPos() + sf::Vector2f(0, ADIM_Y);

			if (border_kontrol(gelecek_pos, haritaDizi))
				gozluklu.setPos(gelecek_pos);

			cout << "asagi tusa tiklandi" << endl;

			flag_down = false;
		}
		else if (!down && !flag_down)
			flag_down = true;
		/// ///////////////////////////////////////////////


		/* Küp baþlangýç kordinatlarý */
		float x = KENAR_BOSLUK, y = KENAR_BOSLUK;
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
				rect[sayac].setSize(sf::Vector2f(KUP_BOYUT, KUP_BOYUT));
				rect[sayac].setPosition(x, y);
				rect[sayac].setOutlineColor(black);
				rect[sayac].setOutlineThickness(1.0f);

				/* Pencereye çizmek */
				window.draw(rect[sayac]);
				sayac++;
				x += KUP_BOYUT;
			}
			y += KUP_BOYUT;
			x = KENAR_BOSLUK;

		}

		// Baþlangýç noktasý (mavi)
		rect[71].setFillColor(blue);

		/* Drawing objects */
		window.draw(rect[71]);
		window.draw(*(gozluklu.GetSprite()));
		
		/* Dusmanlarý ciz */
		for (auto dusman : duzman_dizi) {
			window.draw(*(dusman.GetSprite()));
		}

		window.display();


	}

	return 0;
}