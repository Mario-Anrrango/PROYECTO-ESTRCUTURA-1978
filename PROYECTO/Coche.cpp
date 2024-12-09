#include "Coche.h"
#include "Lista.h"
#include "Menu.h"
#include <iostream>
#include "ValidacionPlaca.h"
#include "Validaciones.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <conio.h>

using namespace std;

Coche InsertarDatos()
{
    Validaciones validaciones;
    Placa<Coche> validador;
    ListaCircularDoble<Coche> lista;
    string placa, modelo, color, marca;
    int año = 0;

    placa = validador.ingresarPlaca(lista.getPrimero());

    marca = validaciones.ingresarString("Ingrese la marca: ");

    color = validaciones.ingresarString("Ingrese el color: ");

    modelo = validaciones.ingresarString("Ingrese el modelo: ");

    return Coche(placa, modelo, color, marca, año);
}

void Coche::menu(ListaCircularDoble<Coche> &lista)
{
    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Buscar Coche por la Placa",
        "Busqueda Avanzada",
        "Eliminar Coche por Placa",
        "Liberar el parqueadero",
        "Ayuda",
        "Salir"};
    string archivo = "autos.txt";

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion)
        {
        case 0:
        {
            Coche nuevoCoche = InsertarDatos();
            lista.insertar(nuevoCoche);
            break;
        }
        case 1:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "       HISTORIAL DE AUTOS               " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            lista.mostrar(lista.getPrimero());
            break;
        }
        case 2:
        {
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
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "     BIENVENIDOS A LA BUSQUEDA AVANZADA  " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;

            menuBusquedaAvanzada(lista);
            break;
        }
        case 4:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "  BIENVENIDOS A LA DEPURACION DE COCHES" << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa del coche que se va eliminar: ";
            cin >> placa;
            lista.eliminarPorPlaca(placa);
            break;
        }
        case 5:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "  BIENVENIDOS A LA GESTION DE ESTACIONAMIENTO " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa del coche que se va dejar el estacionamiento: ";
            cin >> placa;
            lista.salirDelParqueadero(placa);
            break;
        }
        case 6:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "               (i)AYUDA                 " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string archivo = "ayuda.html";
            string comando = "start " + archivo;
            system(comando.c_str());
            break;
        }
        case 7:
        {
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

void Coche::menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista)
{
    vector<string> opciones = {
        "Buscar por Modelo",
        "Buscar por Color",
        "Buscar por Anio/Fecha",
        "Buscar por Marca",
        "Buscar por Hora",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Busqueda Avanzada");

        switch (seleccion)
        {
        case 0:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Modelo" << endl;
            cout << "========================================" << endl;
            string modelo;
            cout << "Ingrese el modelo: ";
            cin >> modelo;
            lista.BusquedaAvanzada("modelo", modelo,"");
            break;
        }
        case 1:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Color" << endl;
            cout << "========================================" << endl;
            string color;
            cout << "Ingrese el color: ";
            cin >> color;
            lista.BusquedaAvanzada("color", color,"");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Año/Fecha" << endl;
            cout << "========================================" << endl;
            string fecha;
            cout << "Ingrese la fecha (DD-MM-AAAA): ";
            cin >> fecha;
            lista.BusquedaAvanzada("fecha", fecha,"");
            break;
        }
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Marca" << endl;
            cout << "========================================" << endl;
            string marca;
            cout << "Ingrese la marca: ";
            cin >> marca;
            lista.BusquedaAvanzada("hora", "08:00:00", "12:00:00");
            break;
        }
        case 4:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Hora" << endl;
            cout << "========================================" << endl;
            string HoraEntrada1,HoraEntrada2;
            cout << "Ingrese la hora de entrada 1: ";
            cin >> HoraEntrada1;
            cout << "Ingrese la hora de entrada 2: ";
            cin >> HoraEntrada2;
            lista.BusquedaAvanzada("hora", HoraEntrada1,HoraEntrada2);
            break;
        }
        case 5:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opción invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}