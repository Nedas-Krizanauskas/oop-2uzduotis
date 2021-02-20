#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::accumulate;
using std::setw;
using std::left;

struct Studentas {
  string vardas, pavarde;
  float mediana, vidurkis, egzaminas;
  vector<int> pazymiai;
};

int gautiAtsitiktini() {
  return rand() % 10 + 1;
}

int parse(string s) {
  try {
    return stoi(s);
  } catch (std::invalid_argument const &e) {
    return -2;
  }
}

int arPazymys(string s) {
  // return -1 jei nera geras
  int i = parse(s);
  if(i == 0) {
    return gautiAtsitiktini();
  } else
  if(i == -1) {
    return -1;
  } else
  if(i == -2) {
    cout << "Netinkamas skaicius!" << endl;
    return -2;
  } else if(i < 1 || i > 10) {
    cout << "Netinkamas skaicius! Limitai yra nuo 1 iki 10" << endl;
    return -2;
  }

  return i;
}

bool gautiAtsakyma(string ats) {
  if(ats == "taip") {
    return true;
  } else if(ats == "ne") {
    return false;
  }

  cout << "Neteisingas atsakymas, priimame kaip atsakyma 'Ne'." << endl;
  return false;
}

float apvalinti(float input) {
  return ((int)(input * 100 + 0.5)) / 100;
}
