#include "Karakter.h"
#include <vector>
#include <iostream>

#define ADIM_X 70
#define ADIM_Y 70
#define SONSUZ 10000
#define KENAR_BOSLUK 100
#define SABIT_BIR 1


using namespace std;

void kucukBasaEkle(struct blok* ekle_blok, vector<struct blok* >* blok_liste) {
	int index = 0;

	for (auto b : *(blok_liste)) {
		if (b->dist > ekle_blok->dist) {
			blok_liste->insert(blok_liste->begin() + index, ekle_blok);
			break;
		}

		index++;
	}
	// eðer yukarýda listeye eklenmediyse herþeyden büyük demektir sonuna ekle
	if (index >= blok_liste->size()) {
		blok_liste->insert(blok_liste->begin() + index, ekle_blok);
	}
}


struct blok* Karakter::EnKýsaYol(char harita[11][13], sf::Vector2f hedefPos, vector<sf::Vector2f> gargamel_pozlarý) {

	vector<struct blok*> bakilmamis_blok;

	sf::Vector2f goreceli_pos = this->GetPos() - sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK);
	int ax = (int)(goreceli_pos.x / ADIM_X);
	int ay = (int)(goreceli_pos.y / ADIM_Y);

	sf::Vector2f hedef_goreceli_pos = hedefPos - sf::Vector2f(KENAR_BOSLUK, KENAR_BOSLUK);
	int hx = (int)(hedef_goreceli_pos.x / ADIM_X);
	int hy = (int)(hedef_goreceli_pos.y / ADIM_Y);

	// bakilmamis_bloklarý eklemek

	for(int y = 0; y < 11; y++){
		for (int x = 0; x < 13; x++) {
			// azman zýplama kontrol

			if (harita[y][x] == '1') {
				
				bool flag = 0;
				// azman gargamelin üstünden atlyamaz
				if (this->tur == "azman" && gargamel_pozlarý.size() > 0) {
					for (auto gargamel_poz : gargamel_pozlarý) {

						if ((gargamel_poz.y == y && gargamel_poz.x == x) && !(gargamel_poz.x == hx && gargamel_poz.y == hy)){ // gargamel o kutuda ama o kutuda þirin yoksa flag 1 yap bu kutuyu atla
							flag = 1;
						}

						if (ax == gargamel_poz.x && ay == gargamel_poz.y)
							flag = 1;

					}
				}


				if ((flag == 1)) {
					continue;
				}
			

				// yeni blok oluþtur
				struct blok* yeni_blok;
				yeni_blok = (struct blok*)malloc(sizeof(struct blok));
				yeni_blok->x = x;
				yeni_blok->y = y;
				yeni_blok->dist = ((x == ax && y == ay) ? 0 : SONSUZ);
				yeni_blok->parent = NULL;

				// yeni bloku küçükten büyük sýrasýna göre bakilmamis blok vektörüne ekle

				kucukBasaEkle(yeni_blok, &bakilmamis_blok);
					

			}
		}
	}

	
	while (bakilmamis_blok.size() > 0) {
		// en küçük distancelý bloku al ve onu listeden sil
		struct blok* suanki_blok = bakilmamis_blok[0];
		//cout << "SUANKI_BLOK" << suanki_blok << endl;
		bakilmamis_blok.erase(bakilmamis_blok.begin());

		// Hedef bulunduðu an
		if (hx == suanki_blok->x && hy == suanki_blok->y) {
			return suanki_blok;
		}
		else {
			// Bulunduðu yerin komþularýnýn distancesi 
			int yeni_distance = suanki_blok->dist + 1;
			int sbx = suanki_blok->x, sby = suanki_blok->y;
			// komsular x+1,y - x,y+1, x-1,y x,y-1 
			int index = 0;
			for(auto komsu_blok : bakilmamis_blok){

				bool flag1 = (sby == komsu_blok->y && sbx + 1 == komsu_blok->x);
				bool flag2 = (sby == komsu_blok->y && sbx - 1 == komsu_blok->x);
				bool flag3 = (sby + 1 == komsu_blok->y && sbx  == komsu_blok->x);
				bool flag4 = (sby - 1 == komsu_blok->y && sbx  == komsu_blok->x);

				if (flag1 || flag2 || flag3 || flag4) {

					komsu_blok->dist = yeni_distance;
					komsu_blok->parent = suanki_blok;
					bakilmamis_blok.erase(bakilmamis_blok.begin() + index);
					kucukBasaEkle(komsu_blok, &bakilmamis_blok);

				}

				index++;
			}
		}

	}

	return nullptr;
}

void Karakter::setPos(sf::Vector2f pos) {
	this->pos = pos;
	this->GetSprite()->setPosition(this->pos);

}

