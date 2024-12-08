#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

int menuInteractivo(const vector<string>& opciones, const string& titulo = "Menu Interactivo");
int menuInteractivo(const vector<string>& opciones, const string& titulo) {
    int seleccion = 0;
    const int numOpciones = opciones.size();

    while (true) {
        system("cls");
        
        // Título del menú
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        " << titulo << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        // Mostrar opciones
        for (int i = 0; i < numOpciones; ++i) {
            if (i == seleccion) {
                cout << " > " << opciones[i] << " < " << endl; // Resalta la opción seleccionada
            } else {
                cout << "   " << opciones[i] << endl; // Opciones no seleccionadas
            }
        }
        
        cout << "========================================" << endl;

        // Navegación con teclas
        char tecla = _getch();

        if (tecla == 'a' || tecla == 72) { // 'a' o flecha arriba
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        } else if (tecla == 's' || tecla == 80) { // 's' o flecha abajo
            seleccion = (seleccion + 1) % numOpciones;
        } else if (tecla == 13) { // Enter
            return seleccion;
        }
    }
}

#endif