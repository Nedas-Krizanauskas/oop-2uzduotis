#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Studentas.cpp" // studentas

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::accumulate;
using std::setw;
using std::left;
using std::ifstream;
using std::fstream;


// dabartinis laikas naudojant milliseconds
auto getTimeNow() {
	auto duration = std::chrono::system_clock::now().time_since_epoch();
	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

bool startsWith(string s, string query) {
	return s.rfind(query, 0) == 0;
}

int gautiAtsitiktini() {
	return rand() % 10 + 1;
}

int parse(string s) {
	try {
		return stoi(s);
	}
	catch (std::invalid_argument const& e) {
		return -2;
	}
}

int arPazymys(string s) {
	// return -1 jei nera geras
	int i = parse(s);
	if (i == 0) {
		return gautiAtsitiktini();
	}
	else
		if (i == -1) {
			return -1;
		}
		else
			if (i == -2) {
				cout << "Netinkamas skaicius!" << endl;
				return -2;
			}
			else if (i < 1 || i > 10) {
				cout << "Netinkamas skaicius! Limitai yra nuo 1 iki 10" << endl;
				return -2;
			}

	return i;
}

bool gautiAtsakyma(string ats) {
	if (ats == "taip") {
		return true;
	}
	else if (ats == "ne") {
		return false;
	}

	cout << "Neteisingas atsakymas, priimame kaip atsakyma 'Ne'." << endl;
	return false;
}



Studentas generuotiStudenta(int poz, int pazymiuSk) {
	Studentas stud;
	string vardas = "Vardas";
	string pavarde = "Pavarde";

	int tempPaz;

	vardas += std::to_string(poz);
	pavarde += std::to_string(poz);

	stud.pakeistiVarda(vardas);
	//stud.vardas = "Vardas";
	stud.pakeistiPavarde(pavarde);
	double visasVidurkis = 0.0;

	for (int i = 0; i < pazymiuSk; i++) {
		tempPaz = gautiAtsitiktini();
		stud.pridetiPazymi(tempPaz);

		visasVidurkis += tempPaz;
	}

	visasVidurkis /= (pazymiuSk * 1.0);
	visasVidurkis *= 0.4;

	stud.pakeistiEgzamina(gautiAtsitiktini());
	stud.pakeistiVidurki(visasVidurkis + (stud.egzaminas() * 0.6));

	return stud;
}
