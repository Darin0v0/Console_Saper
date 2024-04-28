#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>


using namespace std;

const int ROZMIAR_TABLICY = 8;
const int LICZBA_MIN = 10;
const char UKRYTA_KOMORKA = '#';
const char MINA_KOMORKA = '*';
const char PUSTA_KOMORKA = ' ';

vector<vector<char>> tablica(ROZMIAR_TABLICY, vector<char>(ROZMIAR_TABLICY, UKRYTA_KOMORKA));
vector<vector<bool>> odkryte(ROZMIAR_TABLICY, vector<bool>(ROZMIAR_TABLICY, false));
vector<vector<bool>> lokalizacjeMin(ROZMIAR_TABLICY, vector<bool>(ROZMIAR_TABLICY, false));

void generujMiny() {
    int liczba = 0;
    while (liczba < LICZBA_MIN) {
        int wiersz = rand() % ROZMIAR_TABLICY;
        int kolumna = rand() % ROZMIAR_TABLICY;
        if (!lokalizacjeMin[wiersz][kolumna]) {
            lokalizacjeMin[wiersz][kolumna] = true;
            liczba++;
        }
    }
}

bool czyPoprawnaKomorka(int wiersz, int kolumna) {
    return wiersz >= 0 && wiersz < ROZMIAR_TABLICY && kolumna >= 0 && kolumna < ROZMIAR_TABLICY;
}

int liczbaSasiednichMin(int wiersz, int kolumna) {
    int liczba = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nowyWiersz = wiersz + i;
            int nowaKolumna = kolumna + j;
            if (czyPoprawnaKomorka(nowyWiersz, nowaKolumna) && lokalizacjeMin[nowyWiersz][nowaKolumna]) {
                liczba++;
            }
        }
    }
    return liczba;
}

void odkryjKomorke(int wiersz, int kolumna) {
    if (!czyPoprawnaKomorka(wiersz, kolumna) || odkryte[wiersz][kolumna]) {
        return;
    }

    odkryte[wiersz][kolumna] = true;
    tablica[wiersz][kolumna] = '0' + liczbaSasiednichMin(wiersz, kolumna);

    if (tablica[wiersz][kolumna] == '0') {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nowyWiersz = wiersz + i;
                int nowaKolumna = kolumna + j;
                odkryjKomorke(nowyWiersz, nowaKolumna);
            }
        }
    }
}

void wyswietlTablice(bool pokazMiny) {
    cout << "   ";
    for (int kolumna = 0; kolumna < ROZMIAR_TABLICY; kolumna++) {
        cout << kolumna << " ";
    }
    cout << endl;

    for (int wiersz = 0; wiersz < ROZMIAR_TABLICY; wiersz++) {
        cout << wiersz << "  ";
        for (int kolumna = 0; kolumna < ROZMIAR_TABLICY; kolumna++) {
            if (odkryte[wiersz][kolumna] || (pokazMiny && lokalizacjeMin[wiersz][kolumna])) {
                cout << tablica[wiersz][kolumna] << " ";
            } else {
                cout << UKRYTA_KOMORKA << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(nullptr));

    generujMiny();

    int pozostaleKomorki = ROZMIAR_TABLICY * ROZMIAR_TABLICY - LICZBA_MIN;
    bool koniecGry = false;

    cout << "Witaj w Saperze!" << endl;
 
    while (!koniecGry) {
        wyswietlTablice(false);
        int wiersz, kolumna;
        cout << "Podaj wiersz i kolumnę (oddzielone spacją): ";
        cin >> wiersz >> kolumna;

        if (!czyPoprawnaKomorka(wiersz, kolumna) || odkryte[wiersz][kolumna]) {
            cout << "Nieprawidłowy ruch! Spróbuj ponownie." << endl;
             system("cls");
            continue;
        }

        if (lokalizacjeMin[wiersz][kolumna]) {
            koniecGry = true;
            cout << "Koniec gry! Uderzyłeś w minę." << endl;
            system("cls");
            wyswietlTablice(true);
        } else {
            odkryjKomorke(wiersz, kolumna);
            pozostaleKomorki--;

            if (pozostaleKomorki == 0) {
                koniecGry = true;
                cout << "Gratulacje! Wygrałeś grę!" << endl;
                system("cls");
                wyswietlTablice(true);
            }
        }
    }

    return 0;
}
