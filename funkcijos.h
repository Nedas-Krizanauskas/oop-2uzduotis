#include <iostream>
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
struct Studentas {
	string vardas, pavarde;
	float mediana, vidurkis, egzaminas;
	vector<int> pazymiai;

	bool operator<(const Studentas& a) const
	{
		return vidurkis < a.vidurkis;
	}
};

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

float apvalinti(float input) {
	return ((int)(input * 100.0 + 0.5)) / 100.0;
}

int parse(string s) {
	try {
		return stoi(s);
	}
	catch (std::invalid_argument const& e) {
		return -2;
	}
}

float skaiciuotiMediana(Studentas stud) {
	int dydis = stud.pazymiai.size();
	return dydis % 2 == 0 ? (stud.pazymiai[dydis / 2.0 - 1.0] + stud.pazymiai[dydis / 2.0]) / 2.0 : stud.pazymiai[dydis / 2.0];
}

float skaiciuotiVidurki(Studentas stud) {
	return apvalinti((accumulate(stud.pazymiai.begin(), stud.pazymiai.end(), 0.0) / stud.pazymiai.size()) * 0.4);
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
	stud.vardas = "Vardas";
	stud.pavarde = "Pavarde";

	int tempPaz;

	stud.vardas += std::to_string(poz);
	stud.pavarde += std::to_string(poz);

	double visasVidurkis = 0.0;

	for (int i = 0; i < 10; i++) {
		tempPaz = gautiAtsitiktini();
		stud.pazymiai.push_back(tempPaz);

		visasVidurkis += tempPaz;
	}

	visasVidurkis /= (pazymiuSk * 1.0);
	visasVidurkis *= 0.4;

	stud.egzaminas = gautiAtsitiktini();
	stud.vidurkis = visasVidurkis + (stud.egzaminas * 0.6);

	return stud;
}
