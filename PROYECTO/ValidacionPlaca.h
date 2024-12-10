#ifndef VALIDACION_PLACA_H
#define VALIDACION_PLACA_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <stdexcept>
#include "Nodo.h"
#include "Lista.h"

using namespace std;

template <typename T>
class Placa {
public:
    string ingresarPlaca(Nodo<T>* aux);

private:
    void convertirAMayusculas(string& placa);
};

template <typename T>
string Placa<T>::ingresarPlaca(Nodo<T>* aux) {
    string placa;
    unordered_set<string> provinciasValidas = {
        "A", "B", "C", "E", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
    };

    while (true) {
        placa = "";
        cout << "Ingrese la placa: ";
        getline(cin, placa);

        // Eliminar espacios
        placa.erase(remove(placa.begin(), placa.end(), ' '), placa.end());

        if (placa.length() != 7) {
            cout << "\nLa placa debe tener exactamente 7 caracteres. Intente de nuevo." << endl;
            continue;
        }

        // Validar la inicial de la provincia
        if (provinciasValidas.count(string(1, toupper(placa[0]))) == 0) {
            cout << "\nInicial de provincia no válida. Intente de nuevo." << endl;
            continue;
        }

        // Validar el formato de la placa
        if (!regex_match(placa, regex("^[A-Z]{1,3}[0-9]{4}$"))) {
            cout << "\nFormato de placa incorrecto. Intente de nuevo." << endl;
            continue;
        }


        break;  // Si todo es válido, salimos del ciclo
    }

    return placa;
}
#endif