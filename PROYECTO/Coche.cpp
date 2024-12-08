#include "Coche.h"
#include "Lista.h"
#include "Menu.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Coche InsertarDatos() {
    string placa, modelo, color, marca;

    cout << "Ingrese la placa: ";
    cin >> placa;

    cout << "Ingrese la marca: ";
    cin >> marca;

    cout << "Ingrese el color: ";
    cin >> color;

    cout << "Ingrese el modelo: ";
    cin >> modelo;

    return Coche(placa, modelo, color, marca);
}

// Implementación del menú usando la función genérica
void Coche::menu(ListaCircularDoble<Coche>& lista) {
    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Buscar Coche por la Placa",
        "Salir"
    };

    while (true) {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion) {
            case 0: {
                Coche nuevoCoche = InsertarDatos();
                lista.insertar(nuevoCoche);
                break;
            }
            case 1: {
                system("cls");
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                cout << "       HISTORIAL DE AUTOS               " << endl;
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                lista.mostrar(lista.getPrimero());
                break;
            }
            case 2: {
                system("cls");
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                cout << "  BIENVENIDOS A LA BUSQUEDA DE COCHES   " << endl;
                cout << "========================================" << endl;
                cout << "========================================" << endl;
                string placa;
                cout << "Ingrese la placa: ";
                cin >> placa;
                lista.buscarPorPlaca(placa);
                break;
            }
            case 3: {
                cout << "Saliendo..." << endl;
                return;
            }
            default:
                break;
        }

        system("pause");
    }
}
