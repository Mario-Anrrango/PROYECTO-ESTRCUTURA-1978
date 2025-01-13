#include "menu.h"

int menuInteractivo(const vector<string>& opciones, const string& titulo) {
    int seleccion = 0;
    const int numOpciones = opciones.size();

    while (true) {
        system("cls");

        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        " << titulo << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numOpciones; ++i) {
            if (i == seleccion) {
                cout << " > " << opciones[i] << " < " << endl;
            } else {
                cout << "   " << opciones[i] << endl;
            }
        }

        cout << "========================================" << endl;

        char tecla = _getch();

        if (tecla == 'a' || tecla == 72) { // Flecha arriba o 'a'
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        } else if (tecla == 's' || tecla == 80) { // Flecha abajo o 's'
            seleccion = (seleccion + 1) % numOpciones;
        } else if (tecla == 13) {
            return seleccion;
        }
    }
}