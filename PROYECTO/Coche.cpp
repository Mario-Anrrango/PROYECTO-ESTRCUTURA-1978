#include "Coche.h"
#include <iostream>
#include "Lista.h"
#include <cstdlib>

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
    string placa; 

    do {
        cout << "========================================" << endl;
        cout << "        Menu de Parqueadero               " << endl;
        cout << "========================================" << endl;
        cout << "1. Insertar Coche" << endl;
        cout << "2. Mostrar Lista de Coches" << endl;
        cout << "3. Buscar Coche Por La Placa" << endl;
        cout << "4. Salir" << endl;
        cout << "========================================" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                nuevoCoche = InsertarDatos();
                lista.insertar(nuevoCoche);
                break;

            case 2:
                system("cls");
                std::cout << "========================================" << std::endl;
                std::cout << "========================================" << std::endl;
                std::cout << "       Historial de Autos                " << std::endl;
                std::cout << "========================================" << std::endl;
                std::cout << "========================================" << std::endl;
                lista.mostrar(lista.getPrimero());
                break;

            case 3:
                system("cls");
                std::cout << "========================================" << std::endl;
                std::cout << "========================================" << std::endl;
                std::cout << "   Bienvenido A La Busqueda De Coches   " << std::endl;
                std::cout << "========================================" << std::endl;
                std::cout << "========================================" << std::endl;
                cout << "Ingrese La Placa ->" << endl;
                cin >> placa;
                lista.buscarPorPlaca(placa);
                break;

            case 4:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción inválida, por favor elige otra opción." << endl;
                break;
        }
    } while (opcion != 4); // Cambié la condición de salida a 4, porque el "case 4" debería salir del bucle

    return;
}