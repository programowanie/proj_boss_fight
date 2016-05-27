#include <string>
using namespace std;

struct parametr {
	int moc, szansa;
};

class Bohater {
protected:
	string _klasa;
	int _intel;
	int _sila;
	int _wytrz;
	int _zre;
	int _kryt;
	int _hpMax;
	int _hp;
	parametr _atak;
	int _unik;
	parametr _blok;
	parametr _prowokacja;
public:
	string klasa() { return _klasa; }
	int intel() { return _intel; }
	int sila() { return _sila; }
	int wytrz() { return _wytrz; }
	int zre() { return _zre; }
	int kryt() { return _kryt; }
	int hp() { return _hp; }
	int hpMax() { return _hpMax; }
	parametr atak() { return _atak; }
	int unik() { return _unik; }
	parametr blok() { return _blok; }
	parametr prowokacja() { return _prowokacja; }
	int dmg(int ile);
	int heal(int ile);
	bool zyje();
	string opis();
};

class Healer :public Bohater { public: Healer(int, int, int, int, int); };	
class Tank :public Bohater { public: Tank(int, int, int, int, int); };
class Dps :public Bohater { public: Dps(int, int, int, int, int); };

class Boss {
	int _sila;
	int _zre;
	int _hp;
	int _ulti; // szansa na użycie ulta
	int _prow;
	parametr _atak;
public:
	Boss(int sila, int zre, int hp, int ulti);
	int sila() { return _sila; }
	int zre() { return _zre; }
	int hp() { return _hp; }
	int ulti() { return _ulti; }
	int dmg(int ile) { _hp -= ile; }
	int prow() { return _prow; }
	int sprow(int a);
	int kprow() { _prow--; }
	parametr atak() { return _atak; }
};

int lowHp(Bohater, Bohater, Bohater);