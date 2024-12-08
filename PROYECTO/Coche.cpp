#include "Coche.h"
#include "Lista.h"
#include "Menu.h"
#include <iostream>
#include "ValidacionPlaca.h"
#include "Validaciones.h"

using namespace std;

Coche InsertarDatos() {
    Validaciones validaciones;
    Placa validador;
    string placa, modelo, color, marca;

    placa = validador.ingresarPlaca();

    marca = validaciones.ingresarString("Ingrese la marca: ");

    color = validaciones.ingresarString("Ingrese el color: ");

    modelo = validaciones.ingresarString("Ingrese el modelo: ");

    return Coche(placa, modelo, color, marca);
}

// Implementación del menú usando la función genérica
void Coche::menu(ListaCircularDoble<Coche>& lista) {
    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Buscar Coche por la Placa",
        "Eliminar Coche por Placa",
        "Ayuda",
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
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "  BIENVENIDOS A LA ELIMINACIÓN DE COCHES" << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        string placa;
        cout << "Ingrese la placa del coche a eliminar: ";
        cin >> placa;
        lista.eliminarPorPlaca(placa);
        break;
    }
    case 4: {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "               (i)AYUDA                 " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        break;
    }
    case 5: {
        cout << "Saliendo..." << endl;
        return;
    }
    default:
        cout << "Opción inválida. Inténtelo de nuevo." << endl;
        break;
}

system("pause");

    }

}