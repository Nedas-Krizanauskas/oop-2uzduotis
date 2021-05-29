#include <iostream>
#include <list>
#include <vector>
#include <numeric>

using namespace std;

class Studentas {
    private:
        string vardas_, pavarde_;
        float mediana_, vidurkis_, egzaminas_;
        vector<int> pazymiai_;

    public:
        inline string vardas() const { return vardas_; }
        inline string pavarde() {
            return pavarde_;
        }
        inline float mediana() {
            return mediana_;
        }
        inline float vidurkis() {
            return vidurkis_;
        }
        inline float egzaminas() {
            return egzaminas_;
        }
        inline vector<int> pazymiai() {
            return pazymiai_;
        }

        inline void pakeistiVarda(string _vardas) {
            this->vardas_ = _vardas;
        }

        inline void pakeistiPavarde(string _pvd) {
            this->pavarde_ = _pvd;
        }
        inline void pakeistiEgzamina(float _egz) {
            this->egzaminas_ = _egz;
        }
        inline void pakeistiMediana(float _med) {
            this->mediana_ = _med;
        }
        inline void pakeistiVidurki(float _vid) {
            this->vidurkis_ = _vid;
        }
        
        void pridetiPazymi(int pazymys) {
            pazymiai_.push_back(pazymys);
        }

        float skaiciuotiMediana() {
            int dydis = pazymiai_.size();
            mediana_ = dydis % 2 == 0 ? (pazymiai_[dydis / 2.0 - 1.0] + pazymiai_[dydis / 2.0]) / 2.0 : pazymiai_[dydis / 2.0];
            return mediana_;
        }

        float skaiciuotiVidurki() {
            vidurkis_ = apvalinti((accumulate(pazymiai_.begin(), pazymiai_.end(), 0.0) / pazymiai_.size()) * 0.4);
            return vidurkis_;
        }

        float apvalinti(float input) {
            return ((int)(input * 100.0 + 0.5)) / 100.0;
        }

};
