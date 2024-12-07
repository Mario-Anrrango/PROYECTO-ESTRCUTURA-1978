#include "Coche.h"
#include <iostream>
#include "Lista.h"

using namespace std;

Coche InsertarDatos(){
    string placa;
    string modelo;
    string color;
    string marca;

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



void Coche::menu(ListaCircularDoble<Coche>& lista) {

    
    Coche nuevoCoche;
    int opcion;

    do {
        cout << "========================================" << endl;
        cout << "        Menu de Parqueadero               " << endl;
        cout << "========================================" << endl;
        cout << "1. Insertar Coche" << endl;
        cout << "2. Mostrar Lista de Coches" << endl;
        cout << "3. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                nuevoCoche = InsertarDatos();
                lista.insertar(nuevoCoche);
                break;

            case 2:
                lista.mostrar(lista.getPrimero());
                break;

            case 3:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción inválida, por favor elige otra opción." << endl;
                break;
        }
    } while (opcion != 3);

    return;
}
