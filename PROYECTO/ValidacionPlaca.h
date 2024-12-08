#ifndef VALIDACION_PLACA_H
#define VALIDACION_PLACA_H
#include <iostream>
#include <string>
#include <unordered_set>
#include <regex>
#include <algorithm>

using namespace std;

class Placa {
public:

    string ingresarPlaca();

private:

    void convertirAMayusculas(string& placa);
};

string Placa::ingresarPlaca() {
    string placa;
    unordered_set<string> provinciasValidas = {
        "A", "B", "C", "E", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
    };

    while (true) {
        placa = "";
        cout << "Ingrese la placa: ";

        char c;
        int count = 0;

        while (count < 7 && (c = getchar()) != '\n') {
            if (count < 3 && isalpha(c)) {
                placa += toupper(c);
                count++;
            } else if (count >= 3 && count < 7 && isdigit(c)) {
                placa += c;
                count++;
            } else if (c == 8 && count > 0) {
                placa.pop_back();
                count--;
            }
        }

        if ((placa.length() == 6 || placa.length() == 7) &&
            provinciasValidas.count(placa.substr(0, 1)) &&
            regex_match(placa, regex("^[A-Z]{1,3}[0-9]{4}$"))) {
            break;
        } else {
            cout << "\nFormato de placa inválido o provincia no válida. Vuelva a intentarlo." << endl;
        }
    }

    return placa;
}

#endif