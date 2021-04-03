# Objektinis Programavimas 2 uzd.

## Idiegimas
git clone https://github.com/Nedas-Krizanauskas/oop-2uzduotis/.git

cd oop-2uzduotis.

clang++ -std=c++11 main.cpp -o main

./main


# Spartos analize
|Funkcija|n = 10|n = 100|n = 1000|n = 10,000|n = 100,000|
|----|---|---|----|------|------|
|Duomenu Generavimas         |0,002s|0,008s|0,064s|0,637s|6,605s|
|Duomenų nuskaitymas iš failo|0,001s|0,009s|0,090s|0,893s|9,430s|
|Duomenų išrikiavimas        |0s|0,001s|0,014s|0,127s|1,213s|
|Is Viso                     |0,006s|0,029s|0,181s|1,997s|22,179s|
