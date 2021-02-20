#include <iostream>
#include "funkcijos.h" // programos funkcijos, studentu info

void nuskaityti(vector<Studentas> *studentai, bool *vidurkis);
void spausdintiRezultatus(vector<Studentas> studentai, bool *vidurkis);

int main() {
  bool vidurkis = true;

  vector<Studentas> studentai;
  nuskaityti(&studentai, &vidurkis);
  spausdintiRezultatus(studentai, &vidurkis);
}

void nuskaityti(vector<Studentas> *studentai, bool *vidurkis) {
  string s_temp;
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
      stud.vidurkis = apvalinti((accumulate(stud.pazymiai.begin(),  stud.pazymiai.end(), 0.0) / stud.pazymiai.size()) * 0.4);
    } else {
      // maz - didz sort'as
      sort(stud.pazymiai.begin(), stud.pazymiai.end());

      // medianos skaiciavimas, tikrinama ar lyginis skaicius pazymiu ar ne
      stud.mediana = stud.pazymiai.size() % 2 == 0 ? 
      (stud.pazymiai[dydis / 2 - 1] + stud.pazymiai[dydis / 2]) / 2 : stud.pazymiai[dydis/ 2];
    }

    studentai -> push_back(stud);
    cout << "------------------------------------------------------------" << endl;
  }
}

void spausdintiRezultatus(vector<Studentas> studentai, bool *vidurkis) {
  cout << left
	<< setw(15) << "Vardas"
	<< setw(15) << "Pavarde";

  cout << setw(15) << 
  (vidurkis ?  "Galutinis (Vid.)" : "Galutinis (Med.)" ) << endl;
		
  cout << "------------------------------------------------------------" << endl;

  Studentas stud;
  for(int i = 0; i < studentai.size(); i++) {
    stud = studentai[i];
    cout << left
			<< setw(15) << stud.vardas
			<< setw(15) << stud.pavarde;

      cout << setw(15) << (stud.egzaminas + (vidurkis ? stud.vidurkis : stud.mediana)) << endl;
  }
}
