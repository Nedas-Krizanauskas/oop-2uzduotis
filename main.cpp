#include <iostream>
#include "funkcijos.h" // programos funkcijos

void nuskaityti(vector<Studentas>* studentai, bool* vidurkis, bool* isFailo, string fileName);
void nuskaitytiIsFailo(vector<Studentas>* studentai, bool* isFailo, string fileName);
void spausdintiRezultatus(vector<Studentas> studentai, bool* vidurkis, bool* isFailo);
void kurtiFailus();

int main() {
	bool vidurkis = true, isFailo = false;

	vector<Studentas> studentai, vargsiukai;
	nuskaityti(&studentai, &vidurkis, &isFailo, "kursiokai.txt");
	spausdintiRezultatus(studentai, &vidurkis, &isFailo);
}

void nuskaityti(vector<Studentas>* studentai, bool* vidurkis, bool* isFailo, string fileName) {
	string s_temp;

	cout << "Studentu pazymiu rusiavimo programa (Sukure: Nedas Krizanauskas)." << endl;
	cout << "" << endl;
	cout << "Pasirinkite tolesni zingsni:" << endl;
	cout << "- 1: Pradeti spartos analize" << endl;
	cout << "- 2: Nuskaityti studentu duomenis is failo (kursiokai.txt)" << endl;
	cout << "- 3: Ivesti studentu duomenis ranka" << endl;
	cout << "" << endl;
	cout << "Iveskite uzduoties skaiciu, kad pradeti:" << endl;

	cin >> s_temp;


	int i_temp, dydis;
	i_temp= parse(s_temp);

	switch (i_temp) {
	case 1: {
		kurtiFailus();
		return;
	}
	case 2: {
		nuskaitytiIsFailo(studentai, isFailo, fileName);
		return;
	}
	case 3: {
		break;
	}
	 default: {
		 cout << "Nerasta uzduotis, programa stabdoma." << endl;
		return;
	}
	}

	// Gauna studentu skaiciu
	int studentuSk;
	cout << "Iveskite studentu skaiciu:" << endl;
	cin >> studentuSk;

	// Vidurkio skaiciavimas
	cout << "Vesti studentu vidurki? [taip = vidurkis, ne = mediana]:" << endl;
	cin >> s_temp;

	*vidurkis = gautiAtsakyma(s_temp);

	// Studentu informacijos kolekcija
	for (int i = 1; i < studentuSk + 1; i++) {
		Studentas stud;

		cout << "#" << i << " Studento Vardas:" << endl;
		cin >> stud.vardas();

		cout << "#" << i << " Studento Pavarde:" << endl;
		cin >> stud.pavarde();
		int p = 1;
		while (true) {
			cout << "Iveskite " << p << " pazymi [1 - 10], 0 = atsitiktinis, -1 = pabaigti:" << endl;
			cin >> s_temp;
			i_temp = arPazymys(s_temp);

			if (i_temp == -1) {
				break;
			}

			stud.pazymiai().push_back(i_temp);
			p++;
		}

		bool egzAtsitiktinis;
		cout << "Ar egzamino rezultatas atsitiktinis [taip/ne]:" << endl;

		cin >> s_temp;

		// Egzamino rezultato gavimas
		egzAtsitiktinis = gautiAtsakyma(s_temp);
		if (egzAtsitiktinis) {
			stud.pakeistiEgzamina(gautiAtsitiktini());
		}
		else {
			cout << "Egzamino rezultatas [1 - 10]:" << endl;
			cin >> s_temp;

			i_temp = arPazymys(s_temp);

			// netinkamas balas
			if (i_temp == -2) {
				continue;
			}

			stud.pakeistiEgzamina(i_temp * 0.6);
		}

		dydis = stud.pazymiai().size();

		if (vidurkis) {
			stud.skaiciuotiVidurki();
		}
		else {
			// maz - didz sort'as
			//sort(stud.pazymiai.begin(), stud.pazymiai.end());

			// medianos skaiciavimas, tikrinama ar lyginis skaicius pazymiu ar ne
			stud.pakeistiEgzamina(stud.skaiciuotiMediana());
			//stud.skaiciuotiMediana(); //TODO: fix
		}

		studentai->push_back(stud);
		cout << "------------------------------------------------------------" << endl;
	}
}

void nuskaitytiIsFailo(vector<Studentas>* studentai, bool* isFailo, string fileName) {
	int pazymiuSkaicius = 0, dabarSk = 1, paz;
	ifstream kursiokai;
	try {
		kursiokai.open(fileName);
	}
	catch (std::exception& e) {
		cout << "Nerastas failas" << endl;
		return;
	}

	string duom;
	Studentas stud;

	bool loop = true; // false jei klaida duomenyse

	int rezultatas = 0;
	// rezultatas = 0, tai dar vis skaitoma pirma eilute
	// rezultatas = 1, skaitomas vardas
	// rezultatas = 2, skaitoma pavarde
	// rezultatas = 3, skaitomas paz.
	// rezultats = 4, skaitomas egz
loop:while (kursiokai >> duom && loop) {
	switch (rezultatas) {
	case 0: {
		if (startsWith(duom, "ND")) {
			pazymiuSkaicius++;
		}
		else if (startsWith(duom, "Egz")) {
			rezultatas++;
		}
		break;
	}
	case 1: {
		stud.pakeistiVarda(duom);
		rezultatas++;
		break;
	}
	case 2: {
		stud.pakeistiPavarde(duom);
		rezultatas++;
		break;
	}
	case 3: {
		if (dabarSk >= pazymiuSkaicius) {
			rezultatas++;
			dabarSk = 1;
			break;
		}

		dabarSk++;
		paz = parse(duom);
		if (paz == -2 || arPazymys(duom) == -2) {
			loop = false;
			cout << "Ivestas neteisingas pazymys studento: " << stud.vardas() << " " << stud.pavarde() << endl;
			cout << "Pazymio ivestis: " << duom << ", pazymio nr.: " << dabarSk << endl;
			break;
		}

		stud.pazymiai().push_back(paz);
		break;
	}
	case 4: {
		stud.pakeistiEgzamina(parse(duom));

		// Medianai sort'ina
		//sort(stud.pazymiai.begin(), stud.pazymiai.end());
		stud.skaiciuotiVidurki();
		stud.skaiciuotiMediana();

		studentai->push_back(stud);
		//stud = {};

		rezultatas = 1;
		break;
	}
	}
}

}

void spausdintiRezultatus(vector<Studentas> studentai, bool* vidurkis, bool* isFailo) {
	cout << std::fixed;
	cout << std::setprecision(2);

	cout << left
		<< setw(15) << "Vardas"
		<< setw(15) << "Pavarde";

	if (!isFailo) {
		cout << setw(15) <<
			(vidurkis ? "Galutinis (Vid.)" : "Galutinis (Med.)") << endl;
	}
	else {
		cout << setw(16) << "Galutinis (Vid.)";
		cout << setw(16) << "Galutinis (Med.)" << endl;
	}
	cout << "------------------------------------------------------------" << endl;

	Studentas stud;
	for (int i = 0; i < studentai.size(); i++) {
		stud = studentai[i];
		cout << left
			<< setw(15) << stud.vardas()
			<< setw(15) << stud.pavarde();

		if (!isFailo) {
			cout << setw(15) << (stud.egzaminas() + (vidurkis ? stud.vidurkis() : stud.mediana())) << endl;
		}
		else {
			cout << setw(16) << (stud.egzaminas() + stud.vidurkis());
			cout << setw(16) << stud.mediana() << endl;
		}
	}
}
void rasytiFaila(vector<Studentas> studentai, string fileName) {
	Studentas stud;

	fstream write;
	write.open(fileName, fstream::out);

	write << "Vardas" << setw(10) << "Pavarde" << setw(8);
	for (int pazSk = 1; pazSk < 10 + 1; pazSk++) {
		write << "ND " << pazSk << setw(8);
	}

	write << "Egz.";
	write << endl;

	for (int i = 1; i < studentai.size() + 1; i++) {
		stud = studentai[i - 1];
		write << stud.vardas() << setw(15) << stud.pavarde() << setw(15);

		int pazymiuSk = stud.pazymiai().size();

		for (int paz = 0; paz < stud.pazymiai().size(); paz++) {
			write << stud.pazymiai()[paz] << setw(8);
		}

		write << stud.egzaminas();
		write << endl;
	}
}

void generuotiFaila(int size) {
	auto pradzia = getTimeNow();

	string fileName;
	fileName += std::to_string(size);
	fileName += ".txt";

	vector<Studentas> studentai;
	for (int i = 0; i < size; i++) {
		studentai.push_back(generuotiStudenta(i, 10));
	}

	rasytiFaila(studentai, fileName);
	auto pabaiga = getTimeNow();

	cout << "Sukurtas failas " << fileName << ", uztruko: " << (pabaiga - pradzia) << "ms" << endl;
}


void kurtiFailus() {
	vector<int> failuDydziai;
	failuDydziai.push_back(10);
	failuDydziai.push_back(100);
	failuDydziai.push_back(1000);
	failuDydziai.push_back(10000);
	//failuDydziai.push_back(100000);

	string s_temp;
	bool t = true;
	Studentas stud;

	cout << "Kurti spartos analizes failus? (UZTRUKS DAUG LAIKO!)" << endl;
	cin >> s_temp;

	// jeip ats = taip, kuriam naujus spartos analizes failus
	if (gautiAtsakyma(s_temp)) {

		for (int i = 0; i < failuDydziai.size(); i++) {
			int dydis = failuDydziai[i];
			cout << "Kuriam " << dydis << ".txt faila" << endl;
			generuotiFaila(dydis);
		}
	}

	cout << "Pradedama spartos analize" << endl;

	for (int i = 0; i < failuDydziai.size(); i++) {
		auto failoPradzia = getTimeNow();
		vector<Studentas> studentai, vargsai, galvociai;

		int dydis = failuDydziai[i];
		string name;
		name += std::to_string(dydis);
		name += ".txt";

		long pradzia = getTimeNow();
		nuskaitytiIsFailo(&studentai, &t, name);
		long pabaiga = getTimeNow();

		cout << dydis << " failas nuskaitytas per " << (pabaiga - pradzia) << "ms" << endl;

		pradzia = getTimeNow();
		for (int s = 0; s < studentai.size(); s++) {
			stud = studentai[s];
			if (stud.vidurkis() < 5) {
				vargsai.push_back(stud);
			}
			else {
				galvociai.push_back(stud);
			}
		}
		pabaiga = getTimeNow();

		cout << dydis << " dalijimo i 2 grupes (<5, >=5) laikas: " << (pabaiga - pradzia) << "ms" << endl;

		pradzia = getTimeNow();
		rasytiFaila(vargsai, "vargsuFile.txt");
		pabaiga = getTimeNow();

		cout << dydis << " vargsu failas uztruko: " << (pabaiga - pradzia) << "ms" << endl;

		pradzia = getTimeNow();
		rasytiFaila(galvociai, "galvociuFile.txt");
		pabaiga = getTimeNow();

		cout << dydis << " galvociu failas uztruko: " << (pabaiga - pradzia) << "ms" << endl;

		auto failoPabaiga = getTimeNow();
		cout << dydis << " failo testas uztruko "
			<< (failoPabaiga - failoPradzia) << "ms, sekundes: " << ((failoPabaiga - failoPradzia) / 1000.00) << endl;
	}
}
