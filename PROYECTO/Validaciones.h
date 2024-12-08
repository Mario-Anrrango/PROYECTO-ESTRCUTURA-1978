#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <cctype>

using namespace std;


class Validaciones {
public:
    string ingresarString(const string& msj);
};

string Validaciones::ingresarString(const string& msj) {
    string input;
    char c;

    cout << msj;

    while (true) {
        c = getch();

        if (isalpha(c) || c == ' ') {
            input += c;
            cout << c;
        } else if (c == '\b' && !input.empty()) {
            input.pop_back();
            cout << "\b \b";
        } else if (c == '\r') {
            if (!input.empty()) {
                break;
            } else {
                cout << "\a";
            }
        } else {
            cout << "\a";
        }
    }

    cout << endl;
    return input;
}
#endif