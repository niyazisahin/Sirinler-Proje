#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Oyuncu.h"
#include "Gozluklu.h"
#include "Gargamel.h"
#include "Azman.h"
#include <string.h>
#include <map>
#include <vector>
#include "Tembel.h"
#include "Mantar.h"
#include "Altýn.h"
#include <time.h>

using namespace std;

/* Makrolar */
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

#define BITIS_X 12
#define BITIS_Y 7

/* Obje listeleri */
vector<Mantar> mantarListesi;
vector<Altýn>  altýnListesi;
 
/* Global texturelar */
sf::Texture texture_mantar;
sf::Texture texture_altin;

int mantar_saniye = 0;
int altin_saniye = 0;

/* Spritelar üst üste geliyor mu kontrol fonksiyonu */
bool sprite_cakýsma(sf::Sprite* s1, sf::Sprite* s2) {
	
	sf::Vector2f pos1 = s1->getPosition();
	sf::Vector2f pos2 = s2->getPosition();

	int x1 = (int)( pos1.x / ADIM_X);
	int x2 = (int)( pos2.x / ADIM_X);
	int y1 = (int)( pos1.y / ADIM_Y);
	int y2 = (int)( pos2.y / ADIM_Y);

	return (x1 == x2) && (y1 == y2);
}

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

/* Yeni mantar üretilmesi fonksiyonu */
void yeniMantar(char harita[11][13]) {
	
	int x = 0, y = 0;

	do{
		x = rand() % 13;
		y = rand() % 11;
	} while (harita[y][x] == '0');

	Mantar yenimantar(0, "mantar", sf::Vector2f(SOL_BORDER + x * KUP_BOYUT, UST_BORDER + y * KUP_BOYUT));
	
	yenimantar.getSprite()->setTexture(texture_mantar);
	mantarListesi.push_back(yenimantar);

}

/* Yeni altýn üretme fonksiyonu */
void yeniAltin(char harita[11][13]) {

	int x = 0, y = 0;

	do {
		x = rand() % 13;
		y = rand() % 11;
	} while (harita[y][x] == '0');

	Altýn yeniAltin(0, "altin", sf::Vector2f(SOL_BORDER + x * KUP_BOYUT, UST_BORDER + y * KUP_BOYUT));

	yeniAltin.getSprite()->setTexture(texture_altin);
	altýnListesi.push_back(yeniAltin);

}



int main()
{
	sf::RenderWindow window(sf::VideoMode(2 * KENAR_BOSLUK + 13 * KUP_BOYUT, 2 * KENAR_BOSLUK + 11 * KUP_BOYUT), "sirineyi Kurtar!");
	sf::RectangleShape rect[143];

	sf::Clock clock;

	srand((unsigned)time(NULL));

	vector<Dusman> duzman_dizi;

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
	sf::Color transparent_green = sf::Color(0, 255, 0, 125);

	map<char, sf::Vector2f> dusman_pozisyon = {
	{ 'A', sf::Vector2f(KENAR_BOSLUK + 3 * KUP_BOYUT, KENAR_BOSLUK) },
	{ 'B', sf::Vector2f(KENAR_BOSLUK + 10 * KUP_BOYUT, KENAR_BOSLUK) },
	{ 'C', sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK + 5 * KUP_BOYUT) },
	{ 'D', sf::Vector2f(KENAR_BOSLUK + 3 * KUP_BOYUT, ALT_BORDER -KUP_BOYUT) }
	};

	/* Texturelar */
	sf::Texture texture_gozluklu = Texture_Yukle("gozluklu.png");
	sf::Texture texture_tembel = Texture_Yukle("tembel.png");
	sf::Texture texture_gargamel = Texture_Yukle("gargamel.png");
	sf::Texture texture_azman = Texture_Yukle("azman.png");
	sf::Texture texture_sirine = Texture_Yukle("sirine.png");

	sf::Texture texture_win = Texture_Yukle("win.png");
	sf::Texture texture_lose = Texture_Yukle("lose.png");

	texture_mantar = Texture_Yukle("mantar.png");
	texture_altin = Texture_Yukle("altin.png");

	/* Karakter Seçimi */
	
	sf::Texture texture_gozluklu_b = Texture_Yukle("gozluklu1.png");
	sf::Texture texture_tembel_b = Texture_Yukle("tembel1.png");

	sf::Sprite gozluklu_buton(texture_gozluklu_b);
	sf::Sprite tembel_buton(texture_tembel_b);
	sf::Sprite sirine(texture_sirine);
	sf::Sprite win(texture_win);
	sf::Sprite lose(texture_lose);

	tembel_buton.setPosition(sf::Vector2f(SOL_BORDER - 40, UST_BORDER));
	gozluklu_buton.setPosition(sf::Vector2f(SAG_BORDER - 472, UST_BORDER));
	sirine.setPosition(sf::Vector2f(SAG_BORDER + 10 , ALT_BORDER - KUP_BOYUT * 4));
	win.setPosition(sf::Vector2f(350 ,400));
	lose.setPosition(sf::Vector2f(350 ,400));


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
				azman.setHiz(1);
				duzman_dizi.push_back(azman);
			}
			break;

			case 'G' :
			{
				Gargamel gargamel(sayac+1, "gargamel");
				gargamel.setPos(dusman_pozisyon[pozisyon]);
				gargamel.GetSprite()->setScale(sf::Vector2f(0.035, 0.035));
				gargamel.GetSprite()->setTexture(texture_gargamel);
				gargamel.setHiz(2);
				duzman_dizi.push_back(gargamel);
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
	bool oyun_baslama_flag   = false;
	bool oyun_kazandýn_flag  = false;
	bool oyun_kaybettin_flag = false;

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
						Gozluklu gozluklu(0, "gozluklu", 20);
						gozluklu.setPos(sf::Vector2f(BASLANGICX, BASLANGICY));
						gozluklu.GetSprite()->setTexture(texture_gozluklu);
						gozluklu.GetSprite()->setScale(0.15, 0.15);
						oyuncu = gozluklu;
						oyun_baslama_flag = true;
					}

					if (tb_bounds.contains(sf::Vector2f(x, y))) {
						Tembel tembel(1, "tembel", 20);
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

			for (auto mantar : mantarListesi)
				window.draw(*(mantar.getSprite()));

			for (auto altin : altýnListesi)
				window.draw(*(altin.getSprite()));

		}

		
		if (oyun_baslama_flag) {

			vector<sf::Vector2f> gargamel_pozlarý;
			for (auto dusman : duzman_dizi) {
				if (dusman.getTur() == "gargamel") {

					sf::Vector2f goreceli_pos = dusman.GetPos() - sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK);
					int x = (int)(goreceli_pos.x / ADIM_X);
					int y = (int)(goreceli_pos.y / ADIM_Y);

					gargamel_pozlarý.push_back(sf::Vector2f(x,y));
				}
			}

			for (auto dusman : duzman_dizi) {

				struct blok* tmp = dusman.EnKýsaYol(haritaDizi, oyuncu.GetPos(), gargamel_pozlarý);
				if(tmp != nullptr){
					while (tmp->parent != NULL) {

						sf::RectangleShape rect;
						rect.setPosition(sf::Vector2f(tmp->x * KUP_BOYUT + SOL_BORDER, tmp->y * KUP_BOYUT + UST_BORDER));
						rect.setFillColor(transparent_green);
						rect.setSize(sf::Vector2f(KUP_BOYUT, KUP_BOYUT));
						window.draw(rect);
						tmp = tmp->parent;
					}
				}
			}
		}

		if(oyun_baslama_flag)
			oyuncu.PuaniGoster(&window);

		if (oyun_kazandýn_flag) {
			window.clear(white);
			window.draw(win);
		}
		
		if (oyun_kaybettin_flag) {
			window.clear(white);
			window.draw(lose);
		}

		window.display();

		if (!oyun_baslama_flag || oyun_kazandýn_flag || oyun_kaybettin_flag)
			continue;


		/* Mantar saniye azaltýlmasý */
		if (mantar_saniye <= 0) {
			mantar_saniye = rand() % 16 + 5;
			yeniMantar(haritaDizi);
		}

		/* Altýn saniye azaltýlmasý */
		if (altin_saniye <= 0) {
			altin_saniye = rand() % 8 + 3;

			for (int i = 0; i < 5; i++)
				yeniAltin(haritaDizi);

		}

		/* Altýn ve mantarlarýn süreleri dolduysa silme iþlemi */
		if (clock.getElapsedTime() > sf::seconds(1)) {
			mantar_saniye--;
			altin_saniye--;

			int counter = 0;
			for (auto &mantar : mantarListesi) {
				mantar.sure_azalt();
				
				if (mantar.olum_suresi <= 0) {
					mantarListesi.erase(mantarListesi.begin() + counter);
				}
				counter++;
			}

			
			counter = 0;
			for (auto &altin : altýnListesi) {
				altin.sure_azalt();
				
				if (altin.olum_suresi <= 0) {
					altýnListesi.erase(altýnListesi.begin() + counter);
					counter = -1;
				}
				counter++;
			}


			clock.restart();
		}

		/* Keyboard input */
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		bool moved = false;

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
			moved = true;

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
			moved = true;

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
			moved = true;
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
			moved = true;
		}
		else if (!down && !flag_down)
			flag_down = true;
		/// ///////////////////////////////////////////////

		if (moved) {

			vector<sf::Vector2f> gargamel_pozlarý;
			for (auto dusman : duzman_dizi) {
				if (dusman.getTur() == "gargamel") {

					sf::Vector2f goreceli_pos = dusman.GetPos() - sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK);
					int x = (int)(goreceli_pos.x / ADIM_X);
					int y = (int)(goreceli_pos.y / ADIM_Y);

					gargamel_pozlarý.push_back(sf::Vector2f(x, y));
				}
			}

			for (auto& dusman : duzman_dizi) {
				struct blok* tmp = dusman.EnKýsaYol(haritaDizi, oyuncu.GetPos(), gargamel_pozlarý);

				if(tmp != nullptr){
					if (tmp->parent != NULL) {
						while (tmp->parent->parent != NULL) {

							if (dusman.getHiz() == 2 && tmp->parent->parent->parent == NULL) {
								break;
							}

							tmp = tmp->parent;
						}
						dusman.setPos(sf::Vector2f(tmp->x * KUP_BOYUT + SOL_BORDER, tmp->y * KUP_BOYUT + UST_BORDER));
					}
				}

				if (sprite_cakýsma(dusman.GetSprite(), oyuncu.GetSprite())) {
					oyuncu.setOyuncuSkor(oyuncu.getOyuncuSkor() - 15);
				}
			}
		}

		sf::Vector2f goreceli_pos = oyuncu.GetPos() - sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK);
		int x = (int)(goreceli_pos.x / ADIM_X);
		int y = (int)(goreceli_pos.y / ADIM_Y);

		if (x == BITIS_X && y == BITIS_Y)
			oyun_kazandýn_flag = true;
		
		if (oyuncu.getOyuncuSkor() <= 0) {
			oyuncu.setOyuncuSkor(0); // oyun tekrar baþlatýlýrsa eksi gözükmemesi
			oyun_kaybettin_flag = true;
		}
		

		/* Mantarlarýn üzerine gelindiðinde altýnlarýn yok olmasý */
		int counter = 0;
		for (auto mantar : mantarListesi) {
			
			if (sprite_cakýsma(mantar.getSprite(), oyuncu.GetSprite())) {
				oyuncu.setOyuncuSkor(oyuncu.getOyuncuSkor() + mantar.getPuan());
				cout << "Oyuncu Skoru : " << oyuncu.getOyuncuSkor() << endl;
				mantarListesi.erase(mantarListesi.begin() + counter);
			}

			counter++;
		}

		/* Altýnlarýn üzerine gelindiðinde altýnlarýn yok olmasý */
		counter = 0;
		for (auto altin : altýnListesi) {

			if (sprite_cakýsma(altin.getSprite(), oyuncu.GetSprite())) {
				oyuncu.setOyuncuSkor(oyuncu.getOyuncuSkor() + altin.getPuan());
				cout << "Oyuncu Skoru : " << oyuncu.getOyuncuSkor() << endl;
				altýnListesi.erase(altýnListesi.begin() + counter);
				counter = -1;
			}

			counter++;
		}

	}

	return 0;
}
