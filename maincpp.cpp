#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Oyuncu.h"
#include "Gozluklu.h"
#include "Gargamel.h"
#include "Azman.h"
#include <string.h>
#include <map>
#include "Tembel.h"

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

sf::Texture Texture_Yukle(string texture_isim) {

	sf::Texture m;

	if (!m.loadFromFile(texture_isim)) {
		cout << texture_isim << " yuklenemedi" << endl;
	}

	return m;
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
	sf::Texture texture_gozluklu = Texture_Yukle("gozluklu.png");
	sf::Texture texture_tembel = Texture_Yukle("tembel.png");
	sf::Texture texture_gargamel = Texture_Yukle("gargamel.png");
	sf::Texture texture_azman = Texture_Yukle("azman.png");
	sf::Texture texture_sirine = Texture_Yukle("sirine.png");

	/* Karakter Seçimi */
	
	sf::Texture texture_gozluklu_b = Texture_Yukle("gozluklu1.png");
	sf::Texture texture_tembel_b = Texture_Yukle("tembel1.png");

	sf::Sprite gozluklu_buton(texture_gozluklu_b);
	sf::Sprite tembel_buton(texture_tembel_b);
	sf::Sprite sirine(texture_sirine);

	tembel_buton.setPosition(sf::Vector2f(SOL_BORDER - 40, UST_BORDER));
	gozluklu_buton.setPosition(sf::Vector2f(SAG_BORDER - 472, UST_BORDER));
	sirine.setPosition(sf::Vector2f(SAG_BORDER + 10 , ALT_BORDER - KUP_BOYUT * 4));

	tembel_buton.setScale(2, 2);
	gozluklu_buton.setScale(2, 2);
	sirine.setScale(0.1, 0.1);

	sf::FloatRect gb_bounds = gozluklu_buton.getGlobalBounds();
	sf::FloatRect tb_bounds = tembel_buton.getGlobalBounds();

	/* Oyuncu */
	Oyuncu oyuncu(0, "oyuncu", "oyuncu" , 0);

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

	////////////////Dosyadan Okuma Bitiþ///////////////

	/// ////////////Küplerin Ekrana Çizimi/////////////
	/* Küp baþlangýç kordinatlarý */
	float x = KENAR_BOSLUK, y = KENAR_BOSLUK;
	sayac = 0;

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
			sayac++;
			x += KUP_BOYUT;
		}
		y += KUP_BOYUT;
		x = KENAR_BOSLUK;

	}
	/// ////////////////////////////////////////
	
	// karakter seçimi kontrol
	bool oyun_baslama_flag = false;

	/* Game Loop */
	while (window.isOpen()) {

		sf::Event event;
		
		while (window.pollEvent(event)) {

			/*Buton Kontrol*/
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && !oyun_baslama_flag)
				{
					int x = event.mouseButton.x, y = event.mouseButton.y;
				
					cout << "mouse x: " << x << endl;
					cout << "mouse y: " << y << endl;				
					
					if (gb_bounds.contains( sf::Vector2f(x,y)) ) {
						Gozluklu gozluklu(0, "gozluklu", 0);
						gozluklu.setPos(sf::Vector2f(BASLANGICX, BASLANGICY));
						gozluklu.GetSprite()->setTexture(texture_gozluklu);
						gozluklu.GetSprite()->setScale(0.15, 0.15);
						oyuncu = gozluklu;
						oyun_baslama_flag = true;
					}

					if (tb_bounds.contains(sf::Vector2f(x, y))) {
						Tembel tembel(1, "tembel", 0);
						tembel.setPos(sf::Vector2f(BASLANGICX, BASLANGICY));
						tembel.GetSprite()->setTexture(texture_tembel);
						tembel.GetSprite()->setScale(0.08, 0.07);
						oyuncu = tembel;
						oyun_baslama_flag = true;
					}

				}
			}

			if (event.type == sf::Event::Closed)
				window.close();

		}

		window.clear(white); // Ekran bufferýný beyaz yap
		

		if (!oyun_baslama_flag){

			/* Butonlar */
			window.draw(gozluklu_buton);
			window.draw(tembel_buton);
		
		}
		else {

			/* Harita ciz*/
			for (auto r : rect)
				window.draw(r);

			/* Oyuncu ciz*/
			window.draw(*(oyuncu.GetSprite()));
			
			/* Sirine ciz*/
			window.draw(sirine);

			/* Dusmanlarý ciz */
			for (auto dusman : duzman_dizi)
				window.draw(*(dusman.GetSprite()));

		}

		window.display();

		if (!oyun_baslama_flag)
			continue;


		/* Keyboard input */
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		/// ///////////////////LEFT////////////////////////
		if (left && flag_left) {

			// yürüceði pozisyon
			for (int i = 1; i < oyuncu.getHiz() + 1; i++) {
				// yürüceði pozisyon
				sf::Vector2f gelecek_pos = oyuncu.GetPos() + sf::Vector2f(-ADIM_X, 0);

				if (border_kontrol(gelecek_pos, haritaDizi))
					oyuncu.setPos(gelecek_pos);

			}
			cout << "sol tusa tiklandi" << endl;
			flag_left = false;

		} else if (!left && !flag_left)
			flag_left = true;
		/// ///////////////////////////////////////////////

				
		/// ///////////////////RIGHT/////////////////////////
		if (right && flag_right) {

			for (int i = 1; i < oyuncu.getHiz() + 1; i++) {
				// yürüceði pozisyon
				sf::Vector2f gelecek_pos = oyuncu.GetPos() + sf::Vector2f(ADIM_X, 0);

				if (border_kontrol(gelecek_pos, haritaDizi))
					oyuncu.setPos(gelecek_pos);
				
			}

			cout << "sag tusa tiklandi" << endl;
			flag_right = false;

		}
		else if (!right && !flag_right)
			flag_right = true;
		/// ///////////////////////////////////////////////


		/// ///////////////////UP//////////////////////////
		if (up && flag_up) {

			// yürüceði pozisyon
			for (int i = 1; i < oyuncu.getHiz() + 1; i++) {
				// yürüceði pozisyon
				sf::Vector2f gelecek_pos = oyuncu.GetPos() + sf::Vector2f(0, -ADIM_Y);

				if (border_kontrol(gelecek_pos, haritaDizi))
					oyuncu.setPos(gelecek_pos);

			}

			cout << "yukari tusa tiklandi" << endl;

			flag_up = false;
		}
		else if (!up && !flag_up)
			flag_up = true;
		/// ///////////////////////////////////////////////


		/// //////////////////DOWN//////////////////////////
		if (down && flag_down) {

			// yürüceði pozisyon
			for (int i = 1; i < oyuncu.getHiz() + 1; i++) {
				// yürüceði pozisyon
				sf::Vector2f gelecek_pos = oyuncu.GetPos() + sf::Vector2f(0, ADIM_Y);

				if (border_kontrol(gelecek_pos, haritaDizi))
					oyuncu.setPos(gelecek_pos);

			}
			
			cout << "asagi tusa tiklandi" << endl;

			flag_down = false;
		}
		else if (!down && !flag_down)
			flag_down = true;
		/// ///////////////////////////////////////////////

	}

	return 0;
}