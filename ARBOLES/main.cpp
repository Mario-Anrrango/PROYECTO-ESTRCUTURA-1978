#include "ArbolAVL.h"
#include "menu.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ArbolAVL arbol;
    vector<string> opciones = {
        "Insertar un elemento",
        "Mostrar recorrido en orden",
        "Buscar un elemento",
        "Eliminar un elemento",
        "Salir"
    };

    while (true) {
        int seleccion = menuInteractivo(opciones, "Menu Interactivo del Arbol AVL");

        if (seleccion == 0) { 
            int clave;
            cout << "Ingrese el valor a insertar: ";
            cin >> clave;
            arbol.insertar(clave);
            cout << "Elemento insertado correctamente.\n";
            system("pause");
        } else if (seleccion == 1) { 
            cout << "Recorrido en orden del Arbol AVL: ";
            arbol.imprimirEnOrden();
            cout << endl;
            system("pause");
        } else if (seleccion == 2) { 
            int clave;
            cout << "Ingrese el valor a buscar: ";
            cin >> clave;
            Nodo* nodoEncontrado = arbol.buscar(clave);
            if (nodoEncontrado) {
                cout << "Elemento " << clave << " encontrado en el arbol.\n";
            } else {
                cout << "Elemento " << clave << " no encontrado.\n";
            }
            system("pause");
        } else if (seleccion == 3) { 
            int clave;
            cout << "Ingrese el valor a eliminar: ";
            cin >> clave;
            bool eliminado = arbol.eliminar(clave);
            if (eliminado) {
                cout << "Elemento " << clave << " eliminado correctamente.\n";
            } else {
                cout << "Elemento " << clave << " no encontrado para eliminar.\n";
            }
            system("pause");
        } else if (seleccion == 4) {
            cout << "Saliendo del programa...\n";
            break;
        }
    }

    return 0;
}