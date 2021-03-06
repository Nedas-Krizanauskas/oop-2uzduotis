#include <iostream>
#include "funkcijos.h" // programos funkcijos, studentu info

void nuskaityti(vector<Studentas> *studentai, bool *vidurkis, bool *isFailo);
void nuskaitytiIsFailo(vector<Studentas> *studentai, bool*isFailo);
void spausdintiRezultatus(vector<Studentas> studentai, bool *vidurkis, bool* isFailo);

int main() {
  bool vidurkis = true, isFailo = false;

  vector<Studentas> studentai;
  nuskaityti(&studentai, &vidurkis, &isFailo);
  spausdintiRezultatus(studentai, &vidurkis, &isFailo);
}

void nuskaityti(vector<Studentas> *studentai, bool *vidurkis, bool *isFailo) {
  string s_temp;
  cout << "Ar nuskaityti duomenis is failo?" << endl;
  cin >> s_temp;

  // jeip ats = taip, tai skaitom duomenis is failo
  if(gautiAtsakyma(s_temp)) {
    nuskaitytiIsFailo(studentai, isFailo);
    return;
  }

  int i_temp, dydis;

  // Gauna studentu skaiciu
  int studentuSk;
  cout << "Iveskite studentu skaiciu:" << endl;
  cin >> studentuSk;

  // Vidurkio skaiciavimas
  cout << "Vesti studentu vidurki? [taip = vidurkis, ne = mediana]:" << endl;
  cin >> s_temp;

  *vidurkis = gautiAtsakyma(s_temp);

  // Studentu informacijos kolekcija
  for(int i = 1; i < studentuSk+1; i++) {
    Studentas stud;

    cout << "#" << i << " Studento Vardas:" << endl;
    cin >> stud.vardas;

    cout << "#" << i << " Studento Pavarde:" << endl;
    cin >> stud.pavarde;
    int p = 1;
    while(true) {    
        cout << "Iveskite " << p << " pazymi [1 - 10], 0 = atsitiktinis, -1 = pabaigti:" << endl;
        cin >> s_temp;
        i_temp = arPazymys(s_temp);

        if(i_temp == -1) {
          break;
        }

        stud.pazymiai.push_back(i_temp);
        p++;
    }

    bool egzAtsitiktinis;
    cout << "Ar egzamino rezultatas atsitiktinis [taip/ne]:" << endl;

    cin >> s_temp;
    
    // Egzamino rezultato gavimas
    egzAtsitiktinis = gautiAtsakyma(s_temp);
    if(egzAtsitiktinis) {
        stud.egzaminas = gautiAtsitiktini();
    } else {
      cout << "Egzamino rezultatas [1 - 10]:" << endl;
      cin >> s_temp;

      i_temp = arPazymys(s_temp);

      // netinkamas balas
      if(i_temp == -2) {
        continue;
      }

      stud.egzaminas = i_temp * 0.6;
    }
    
    dydis = stud.pazymiai.size();

    if(vidurkis) {
      stud.vidurkis = skaiciuotiVidurki(stud);
    } else {
      // maz - didz sort'as
      sort(stud.pazymiai.begin(), stud.pazymiai.end());

      // medianos skaiciavimas, tikrinama ar lyginis skaicius pazymiu ar ne
      stud.mediana = skaiciuotiMediana(stud);
    }

    studentai -> push_back(stud);
    cout << "------------------------------------------------------------" << endl;
  }
}

void nuskaitytiIsFailo(vector<Studentas> *studentai, bool* isFailo) {
  int pazymiuSkaicius = 0, dabarSk = 1, paz;
  ifstream kursiokai;
  kursiokai.open("kursiokai.txt");

  string duom;
  Studentas stud;

  bool loop = true; // false jei klaida duomenyse

  int rezultatas = 0;
  // rezultatas = 0, tai dar vis skaitoma pirma eilute
  // rezultatas = 1, skaitomas vardas
  // rezultatas = 2, skaitoma pavarde
  // rezultatas = 3, skaitomas paz.
  // rezultats = 4, skaitomas egz
  loop:while(kursiokai >> duom && loop) {
    switch(rezultatas) {
      case 0: {
        if(startsWith(duom, "ND")) {
          pazymiuSkaicius++;
        } else if(startsWith(duom, "Egz")) {
          rezultatas++;
        }
        break;
      }
      case 1: {
        stud.vardas = duom;
        rezultatas++;
        break;
      }
      case 2: {
        stud.pavarde = duom;
        rezultatas++;
        break;
      }
      case 3: {
        if(dabarSk >= pazymiuSkaicius) {
          rezultatas++;
          dabarSk = 1;
          break;
        }

        dabarSk++;
        paz = parse(duom);
        if(paz == -2 || arPazymys(duom) == -2) {
          loop = false;
          cout << "Ivestas neteisingas pazymys studento: " << stud.vardas << " " << stud.pavarde << endl;
          cout << "Pazymio ivestis: " << duom << ", pazymio nr.: " << dabarSk << endl;
          break;
        }

        stud.pazymiai.push_back(paz);
        break;
      }
      case 4: {
        stud.egzaminas = parse(duom);
        
        // Medianai sort'ina
        sort(stud.pazymiai.begin(), stud.pazymiai.end());
        stud.vidurkis = skaiciuotiVidurki(stud);
        stud.mediana = skaiciuotiMediana(stud);

        studentai -> push_back(stud);
        stud = {};

        rezultatas = 1;
        break;
      }
    }
  }

}

void spausdintiRezultatus(vector<Studentas> studentai, bool *vidurkis, bool *isFailo) {

  cout << std::fixed;
  cout << std::setprecision(2);

  cout << left
	<< setw(15) << "Vardas"
	<< setw(15) << "Pavarde";

  if(!isFailo) {
    cout << setw(15) << 
    (vidurkis ?  "Galutinis (Vid.)" : "Galutinis (Med.)" ) << endl;
	} else {
    cout << setw(16) << "Galutinis (Vid.)" ;
    cout << setw(16) << "Galutinis (Med.)" << endl;
  }
  cout << "------------------------------------------------------------" << endl;

  Studentas stud;
  for(int i = 0; i < studentai.size(); i++) {
    stud = studentai[i];
    cout << left
			<< setw(15) << stud.vardas
			<< setw(15) << stud.pavarde;

      if(!isFailo) {
        cout << setw(15) << (stud.egzaminas + (vidurkis ? stud.vidurkis : stud.mediana)) << endl;
      } else {
        cout << setw(16) << (stud.egzaminas + stud.vidurkis);
        cout << setw(16) << stud.mediana << endl;
      }
  }
}
