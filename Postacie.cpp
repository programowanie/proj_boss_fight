#include "Postacie.h"
#include <stdlib.h>
#include <stdio.h>




string Bohater::opis() {
	return "| Klasa | HP | ATAK | UNIK | BLOK |\n| " + _klasa + " | " + to_string(_hp) + " | " + to_string(_atak.moc) + " | " + to_string(_unik) + " | " + " |\n";	
}

int Bohater::heal(int ile) {
	if(_hp + ile >= _hpMax) _hp = _hpMax;
	else _hp += ile;
}

int Bohater::dmg(int ile) {
	_hp -= ile;
	printf("Smok trafia %sA zadając %d obrażeń", _klasa.c_str(), ile);
}

bool Bohater::zyje() {
	if(_hp > 0) return 1;
	else return 0;
}

Healer::Healer(int intel, int sila, int wytrz, int zre, int kryt) {
	_intel = intel;
	_sila = sila;
	_wytrz = wytrz;
	_zre = zre;
	_kryt = kryt;
	_klasa = "HEALER";
	_hpMax = _hp = _wytrz * 10;
	_atak.moc = _intel * 2;
	_atak.szansa = rand()%100;
	_unik = _zre * 2;
}

Tank::Tank(int intel, int sila, int wytrz, int zre, int kryt) {
	_intel = intel;
	_sila = sila;
	_wytrz = wytrz;
	_zre = zre;
	_kryt = kryt;
	_klasa = "TANK";
	_hpMax = _hp = _wytrz * 20;
	_atak.moc = _sila;
	_atak.szansa = (_sila + _zre) + rand()%50;
	_unik = _zre * 5;
	_blok.moc = (_wytrz + _zre) * 2;
	_blok.szansa = rand()%100;
	_prowokacja.szansa = 2 * _intel;
	_prowokacja.moc = 2 * _sila;
}

Dps::Dps(int intel, int sila, int wytrz, int zre, int kryt) {
	_intel = intel;
	_sila = sila;
	_wytrz = wytrz;
	_zre = zre;
	_kryt = kryt;
	_klasa = "DPS";
	_hpMax = _hp = _wytrz * 7;
	_atak.moc = (_sila + _zre);
	_atak.szansa = (_sila + _zre)+ rand()%50;
	_unik = _zre * 8;
}

Boss::Boss(int sila, int zre, int hp, int ulti) {
	_sila = sila;
	_zre = zre;
	_hp = hp;
	_ulti = ulti;
	_atak.moc = (_sila + _zre);
	_prow = 0;
}

int Boss::sprow(int a) {
	_prow = a;
}

int lowHp(Bohater tank, Bohater dps, Bohater healer) {
	int hptab[3] = {int((double(tank.hp()) / double(tank.hpMax()))*100), int((double(dps.hp()) / double(dps.hpMax()))*100), int((double(healer.hp()) / double(healer.hpMax()))*100)};
	int indeksy[3] = {1, 2, 3};
	for(int i = 0; i < 3; i++) {
	 	for(int j = 0; j < 2; j++) {
	 		if(hptab[j] > hptab[j+1]) {
	 			swap(hptab[j], hptab[j+1]);
	 			swap(indeksy[j], indeksy[j+1]);
	 		}
	 	}
	}
	return indeksy[0];
}