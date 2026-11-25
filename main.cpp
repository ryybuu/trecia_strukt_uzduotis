#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>


using namespace std;

void stars();

void main_menu();

bool nuskaityti_duomenis(int &uzsakymo_prekiu_kiekis, string kategorijos[100], string pavadinimai[100],
                         double kainos[100], int kiekiai[100]);


int main() {
    int meniu_pasirinkimas;
    string kategoriju_pavadinimai[3] = {"Dviraciai", "Dalys", "Aksesuarai"};
    int uzsakymo_prekiu_kiekis;

    string kategorijos[100] = {};
    string pavadinimai[100] = {};
    double kainos[100] = {};
    int kiekiai[100] = {};

    if (!nuskaityti_duomenis(uzsakymo_prekiu_kiekis, kategorijos, pavadinimai,
                             kainos, kiekiai)) {
        return 1;
    }

    do {
        main_menu();
        cin >> meniu_pasirinkimas;
        switch (meniu_pasirinkimas) {
            case 1:
                cout << "Visos uzsakymo prekes:" << endl;
                cout << string(119, '-') << endl;

                cout << left
                        << setw(13) << "Kategorija"
                        << setw(50) << "Pavadinimas"
                        << setw(10) << "Kaina"
                        << setw(10) << "Kiekis"
                        << setw(10) << "Suma"
                        << setw(10) << "Nuolaida";
                cout << right << setw(10) << "Galutine suma"
                        << endl;

                cout << string(119, '-') << endl;

                for (int i = 0; i < uzsakymo_prekiu_kiekis; i++) {
                    double suma = kainos[i] * kiekiai[i];
                    double nuolaida = 0;
                    if (kiekiai[i] >= 10) {
                        nuolaida = suma * 0.1;
                    }
                    cout << left << fixed << setprecision(2)
                            << setw(13) << kategorijos[i]
                            << setw(50) << pavadinimai[i]
                            << setw(10) << kainos[i]
                            << setw(10) << kiekiai[i]
                            << setw(10) << suma
                            << setw(10) << nuolaida;
                    cout << right << setw(10) << suma - nuolaida
                            << endl;
                }
                break;
            case 2:
                int kat_ivestis;
                do {
                    cout << "Pasirinkite kategorija, kurios prekes norite pamatyti:" << endl;
                    cout << "1." << kategoriju_pavadinimai[0] << endl;
                    cout << "2." << kategoriju_pavadinimai[1] << endl;
                    cout << "3." << kategoriju_pavadinimai[2] << endl;

                    cin >> kat_ivestis;
                } while (kat_ivestis < 1 || kat_ivestis > 3);

                cout << "Kategorija: " << kategoriju_pavadinimai[kat_ivestis - 1] << endl;
                cout << left
                        << setw(50) << "Pavadinimas"
                        << setw(10) << "Kaina"
                        << setw(10) << "Kiekis" << endl;
                for (int i = 0; i < uzsakymo_prekiu_kiekis; i++) {
                    if (kategorijos[i] == kategoriju_pavadinimai[kat_ivestis - 1]) {
                        cout << left
                                << setw(50) << pavadinimai[i]
                                << setw(10) << fixed << setprecision(2) << kainos[i]
                                << setw(10) << kiekiai[i] << endl;
                    }
                }
                break;
        }
    } while (meniu_pasirinkimas != 7);

    return 0;
}

void stars() {
    for (int i = 1; i < 50; i++) {
        cout << "*";
    }
    cout << endl;
}

void main_menu() {
    cout << endl;
    stars();
    cout << setw(25) << "MENIU" << endl;
    stars();
    cout << "1. Perziureti visas uzsakymo prekes." << endl;
    cout << "2. Perziureti pasirinktos kategorijos prekes." << endl;
    cout << "3. Perziureti viso uzsakymo sumas." << endl;
    cout << "4. Perziureti sumas pagal kategorijas." << endl;
    cout << "5. Parodyti visa uzzsakymo ataskaita." << endl;
    cout << "6. Issaugoti visa ataskaita i faila." << endl;
    cout << "7. Iseiti." << endl;
    stars();
    cout << "Pasirinkima iveskite cia:" << endl;
}

bool nuskaityti_duomenis(int &uzsakymo_prekiu_kiekis, string kategorijos[100], string pavadinimai[100],
                         double kainos[100], int kiekiai[100]) {
    ifstream uzsakymo_failas("uzsakymas.txt");
    char delimiter(';');

    if (!uzsakymo_failas.is_open()) {
        cout << "Nepavyko atidaryti failo" << endl;
        return false;
    }

    uzsakymo_failas >> uzsakymo_prekiu_kiekis;
    uzsakymo_failas.ignore();

    if (uzsakymo_prekiu_kiekis < 1 || uzsakymo_prekiu_kiekis > 100) {
        cout << "Prekiu irasu kiekis neteisingas turetu buti 1-100" << endl;
        return false;
    }

    for (int i = 0; i < uzsakymo_prekiu_kiekis; i++) {
        getline(uzsakymo_failas, kategorijos[i], delimiter);
        getline(uzsakymo_failas, pavadinimai[i], delimiter);
        uzsakymo_failas >> kainos[i];
        uzsakymo_failas.ignore(1, delimiter);
        uzsakymo_failas >> kiekiai[i];
        uzsakymo_failas.ignore();
    }

    uzsakymo_failas.close();

    return true;
}
