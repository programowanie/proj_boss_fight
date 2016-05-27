#include <iostream>
#include "Postacie.h"
#include "interface.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
	
	setbuf(stdout, NULL);
	srand(time(NULL));
	int statystyki[3][5];
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 5; j++) 
			statystyki[i][j] = 0;
	}

	inter(statystyki);
	
	Healer resto(statystyki[0][0], statystyki[0][1], statystyki[0][2], statystyki[0][3], statystyki[0][4]);
	Tank guardian(statystyki[1][0], statystyki[1][1], statystyki[1][2], statystyki[1][3], statystyki[1][4]);
	Dps feral(statystyki[2][0], statystyki[2][1], statystyki[2][2], statystyki[2][3], statystyki[2][4]);
	Boss Smok(50, 50, 2500, 30);

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 5; j++) 
			cout << statystyki[i][j] << " ";
		cout << endl;
	}

	cout << resto.opis() << endl;
	cout << guardian.opis() << endl;
	cout << feral.opis() << endl;
	 
	//Ustalenie kolejności ataku
	int tab_zre[3] = {guardian.zre(), feral.zre(), Smok.zre()};
	int kolejnosc[3] = {1, 2, 3};
	for(int i = 0; i < 3; i++) {
	 	for(int j = 0; j < 2; j++) {
	 		if(tab_zre[j] < tab_zre[j+1]) {
	 			swap(tab_zre[j], tab_zre[j+1]);
	 			swap(kolejnosc[j], kolejnosc[j+1]);
	 		}
	 	}
	}

	for(int i = 0; i < 3; i++) cout << tab_zre[i] << " " << kolejnosc[i] << endl;

	//WALKA
	while(Smok.hp() > 0 && (guardian.zyje() || feral.zyje() || resto.zyje())) {
	 	static int x = 0;
	 	if(kolejnosc[x] == 1 && guardian.zyje()) { //tura Tanka
	 		printf("\n| TANK  | DPS  |HEALER |  SMOK  |\n|  %d  |  %d |  %d  |  %d  |  ", guardian.hp(), feral.hp(), resto.hp(), Smok.hp());
	 	 	if(Smok.prow()) {
	 	 		if(guardian.atak().szansa > rand()%100) {
	 	 			int randomValue = rand()%30 - rand()%30;
	 	 			Smok.dmg(guardian.atak().moc + randomValue);
	 	 			printf("TANK trafia zadając %d obrażeń", guardian.atak().moc + randomValue);
	 	 			if(x != 2) usleep(500000);
	 	 		}
	 	 		else {
	 	 			printf("TANK nie trafia");
	 	 			if(x != 2) usleep(500000);
	 	 		}
	 		}
	 		else if(guardian.prowokacja().szansa > rand()%100) { //próba prowokacji
	 			printf("TANK sprowokował Smoka na 2 tury");
	 			Smok.sprow(2);
	 			if(x != 2) usleep(500000);
	 		}
	 		else {
	 			printf("TANK próbował sprowokować Smoka, ale nie wyszło");
	 			if(x != 2) usleep(500000);
	 		}
	 	}
	 	else if(kolejnosc[x] == 2 && feral.zyje()) { //tura Dpsa
	 		printf("\n| TANK  | DPS  |HEALER |  SMOK  |\n|  %d  |  %d |  %d  |  %d  |  ", guardian.hp(), feral.hp(), resto.hp(), Smok.hp());
	 		if(feral.atak().szansa > rand()%100) {
	 			int randomValue = rand()%30 - rand()%30;
	 	 		Smok.dmg(feral.atak().moc + randomValue);
	 	 		printf("DPS trafia zadając %d obrażeń", feral.atak().moc + randomValue);
	 	 		if(x != 2) usleep(500000);
	 		}
	 		else {
	 			printf("DPS nie trafia");
	 			if(x != 2) usleep(500000);
	 		}
	 	}
	 	else if(kolejnosc[x] == 3) { //tura Bosa
	 		printf("\n| TANK  | DPS  |HEALER |  SMOK  |\n|  %d  |  %d |  %d  |  %d  |  ", guardian.hp(), feral.hp(), resto.hp(), Smok.hp());
	 		int randomValue = rand()%30 - rand()%30;
	 		if(Smok.prow()) {
	 			guardian.dmg(Smok.atak().moc + randomValue);	 		
	 			if(x != 2) usleep(500000);
	 			Smok.kprow();
	 		}
	 		else {
	 			int cel = rand()%3;
	 			if(cel == 0) {
	 				if(guardian.zyje()) {
	 					guardian.dmg(Smok.atak().moc + randomValue);	 		
	 					if(x != 2) usleep(500000);
	 				} else cel = 1;
	 			} 
	 			if(cel == 1) {
	 				if(feral.zyje()) {
	 					feral.dmg(Smok.atak().moc + randomValue);
	 					if(x != 2) usleep(500000); 
	 				} else cel = 2;
	 			}
	 			if(cel == 2) {
	 				if(resto.zyje()) {
	 					resto.dmg(Smok.atak().moc + randomValue);
	 					if(x != 2) usleep(500000);
	 				}
	 				else if(guardian.zyje()) {
	 					guardian.dmg(Smok.atak().moc + randomValue);	 		
	 					if(x != 2) usleep(500000);
	 				} 
	 			}
	 		}
	 	}	
	 	//tura Healera
	  	if(x == 2 && resto.zyje()) {
	 		int minHp = lowHp(guardian, feral, resto);
	 		int randomValue = rand()%20 - rand()%20;
	 		if(minHp == 1 && guardian.zyje()) {
	 			guardian.heal(resto.atak().moc) + randomValue;
	 			printf(", a HEALER leczy TANKa za %d hp", resto.atak().moc + randomValue);
	 			usleep(500000);
	 		}
	 		else if(feral.zyje() && feral.hp() < resto.hp() && feral.hp() != feral.hpMax()) {
	 			feral.heal(resto.atak().moc + randomValue);
	 			printf(", a HEALER leczy DPSa za %d hp", resto.atak().moc + randomValue);
	 			usleep(500000);
	 		}
	 		else {
	 			resto.heal(resto.atak().moc + randomValue);
	 			printf(", a HEALER leczy siebie za %d hp", resto.atak().moc + randomValue);
	 			usleep(500000);
	 		}
	 	}
	 	x++;
	 	if(x == 3) x = 0; // każdy atakował -> kolejka od nowa
	}
	printf("\n| TANK  | DPS  |HEALER |  SMOK  |\n|  %d  |  %d |  %d  |  %d  |  ", guardian.hp(), feral.hp(), resto.hp(), Smok.hp()); //Stan po końcu walki
}