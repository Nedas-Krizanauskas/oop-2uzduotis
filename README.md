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


Atlikta Naudojant Intel-i7 7700k 3.60ghz, 16GB RAM 2666Mhz, SSD

## Matavimai:

### Vector:

|Funkcija|n = 10|n = 100|n = 1000|n = 10,000|n = 100,000|
|----|---|---|----|------|------|
|Duomenų nuskaitymas iš failo|0,001s|0,009s|0,090s|0,893s|9,430s|
|Duomenų išrikiavimas |0s|0,001s|0,014s|0,127s|1,213s|

### List:
|Funkcija|n = 10|n = 100|n = 1000|n = 10,000|n = 100,000|
|----|---|---|----|------|------|
|Duomenų nuskaitymas iš failo|0,001s|0,009s|0,082s|0,723s|7,200s|
|Duomenų išrikiavimas |0s|0,001s|0,012s|0,109s|1,023s|

### Deque:
|Funkcija|n = 10|n = 100|n = 1000|n = 10,000|n = 100,000|
|----|---|---|----|------|------|
|Duomenų nuskaitymas iš failo|0,001s|0,010s|0,089s|0,821s|8,342s|
|Duomenų išrikiavimas |0s|0,002s|0,014s|0,122s|1,091s|
