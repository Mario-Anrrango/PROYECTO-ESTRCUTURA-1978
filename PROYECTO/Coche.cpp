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
#include "Propietario.h"

using namespace std;

Coche InsertarDatos(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
{
    Validaciones validaciones;
    Placa<Coche> validador;

    string placa, modelo, color, marca;
    int anio = 0;

    while (true)
    {
        placa = validador.ingresarPlaca(lista.getPrimero());

        Nodo<Coche> *temp = lista.getPrimero();
        bool placaDuplicada = false;

        if (temp != nullptr)
        {
            do
            {
                Coche cocheActual = temp->getDato();

                if (cocheActual.getPlaca() == placa && cocheActual.getHoraSalida() == chrono::system_clock::time_point())
                {
                    cout << "\nEl coche con la placa " << placa << " ya esta en el parqueadero. Ingrese una placa nueva." << endl;
                    placaDuplicada = true;
                    break;
                }

                temp = temp->getSiguiente();
            } while (temp != lista.getPrimero());
        }

        if (!placaDuplicada)
        {
            break;
        }
    }

    Nodo<Coche> *tempHistorial = listaHistorial.getPrimero();
    if (tempHistorial != nullptr)
    {
        do
        {
            Coche cocheHistorial = tempHistorial->getDato();

            if (cocheHistorial.getPlaca() == placa)
            {
                cout << "\nLa placa " << placa << " fue encontrada en el historial. Recuperando datos..." << endl;
                modelo = cocheHistorial.getModelo();
                color = cocheHistorial.getColor();
                marca = cocheHistorial.getMarca();

                cout << "Marca: " << marca << "\nColor: " << color << "\nModelo: " << modelo << "\n";

                vector<string> opciones = {"Si", "No"};
                int seleccion = menuInteractivo(opciones, "Auto encontrado en el sistema. \n  Desea sobreescribir los datos del historial?");

                if (seleccion == 0) 
                {
                    system("cls");
                     cout << "========================================" << endl;
                     cout << "========================================" << endl;
                     cout << "        Datos Recuperados Exitosamente  " << endl;
                     cout << "========================================" << endl;
                    cout << "========================================" << endl;

    
                  cout << "\nMarca:    " << marca << endl;
                  cout << "Modelo:   " << modelo << endl;
                  cout << "Color:    " << color << endl;
                  cout << "Placa:    " << placa << endl;
                    return Coche(placa, modelo, color, marca, anio);
                }
                else 
                {
                    system("cls");
                    cout << "\nPor favor, ingrese los datos manualmente:" << endl;
                    break;
                }
            }

            tempHistorial = tempHistorial->getSiguiente();
        } while (tempHistorial != listaHistorial.getPrimero());
    }

    marca = validaciones.ingresarString("Ingrese la marca: ");
    color = validaciones.ingresarString("Ingrese el color: ");
    modelo = validaciones.ingresarString("Ingrese el modelo: ");

    return Coche(placa, modelo, color, marca, anio);
}







void Coche::menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios)
{
    Placa<Coche> validador;
    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Busqueda de Coche Por Placa",
        "Busqueda Avanzada",
        "Liberar el parqueadero",
        "Ayuda",
        "Salir"};
    string archivo = "autos.txt";
    string archivoHistorial = "autos_historial.txt";
    string archivoPropietarios = "propietarios.txt";

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion)
        {
        case 0:
        {
            Coche nuevoCoche = InsertarDatos(lista,listaHistorial);
            Propietario propietario = propietario.insertarDatosPropietario(listaPropietarios, nuevoCoche.getPlaca());
            
             lista.insertar(nuevoCoche, "autos.txt");
            listaHistorial.insertar(nuevoCoche, "autos_historial.txt");
            break;
        }
      case 1:
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "         Menu de Lista de Coches        " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesLista = {
            "Mostrar Coches en Parqueadero",
            "Mostrar Historial Completo de Coches",
            "Volver al Menu Principal"};

        int seleccionLista = menuInteractivo(opcionesLista, "Menu de Lista de Coches");

        switch (seleccionLista)
        {
        case 0: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   LISTA DE COCHES EN EL PARQUEADERO    " << endl;
            cout << "========================================" << endl;
            lista.mostrar(lista.getPrimero()); 
            system("pause");
            break; 
        }
        case 1: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   HISTORIAL COMPLETO DE COCHES         " << endl;
            cout << "========================================" << endl;
            listaHistorial.mostrar(listaHistorial.getPrimero()); 
            system("pause");
            break; 
        }
        case 2: 
        {
            cout << "Regresando al menu principal..." << endl;
            salirSubmenu = true; 
            break;
        }
        default:
            cout << "Opción inválida. Inténtelo de nuevo." << endl;
            system("pause");
            break;
        }
    }
    break; 
}
        case 2: 
{
    bool salirSubmenu = false;
    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        Menu de Busqueda por Placa      " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesBusqueda = {
            "Buscar en Parqueadero",
            "Buscar en Historial",
            "Volver al Menu Principal"};

        int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda por Placa");

        switch (seleccionBusqueda)
        {
        case 0: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   BUSQUEDA DE PLACA EN PARQUEADERO     " << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
            cin >> placa;
            lista.buscarPorPlaca(placa);
            system("pause");
            break; 
        }
        case 1: 
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "   BUSQUEDA DE PLACA EN HISTORIAL       " << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa a buscar(Utilize mayusculas para validar su placa): ";
            cin >> placa;
            listaHistorial.buscarPorPlaca(placa);
            system("pause");
            break; 
        }
        case 2: 
        {
            cout << "Regresando al menu principal..." << endl;
            salirSubmenu = true; 
            break;
        }
        default:
            cout << "Opción inválida. Inténtelo de nuevo." << endl;
            system("pause");
            break;
        }
    }
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

            menuBusquedaAvanzada(lista, listaHistorial);
            break;
        }
        case 4:
          {
            system("cls");
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            cout << "  BIENVENIDOS A LA GESTION DE ESTACIONAMIENTO " << endl;
            cout << "========================================" << endl;
            cout << "========================================" << endl;
            string placa;
            cout << "Ingrese la placa del coche que  va a  dejar el estacionamiento: ";
            cin >> placa;
            listaHistorial.salirDelParqueadero(placa);
            lista.eliminarPorPlaca(placa);
            break;
        }
     
        case 5:
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
        case 6:
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

void Coche::menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
{

    Validaciones validaciones;
    vector<string> opciones = {
        "Buscar en Parqueadero",
        "Buscar en Historial de Coches",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Busqueda Avanzada");

        switch (seleccion)
        {
        case 0: 
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Parqueadero");

            switch (seleccionBusqueda)
            {
            case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Modelo" << endl;
                    cout << "========================================" << endl;
                    string modelo;
                    cout << "Ingrese el modelo: ";
                    modelo = validaciones.ingresarString("Ingrese el modelo: ");
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
                    color = validaciones.ingresarString("Ingrese el color: ");

                    lista.BusquedaAvanzada("color", color,"");
                    break;
                }
            case 2:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Anio/Fecha" << endl;
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
                    marca = validaciones.ingresarString("Ingrese la marca: ");
                    
                    lista.BusquedaAvanzada("marca", marca,"");
                    break;
                }
            case 4:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Hora" << endl;
                    cout << "========================================" << endl;
                    string HoraEntrada1, HoraEntrada2;
                    cout << "Ingrese la hora de entrada 1: ";
                    cin >> HoraEntrada1;
                    cout << "Ingrese la hora de entrada 2: ";
                    cin >> HoraEntrada2;
                    lista.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
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
            break;
        }

        case 1: 
        {
            vector<string> opcionesBusqueda = {
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"};

            int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda en Historial");

            switch (seleccionBusqueda)
            {
            case 0:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Modelo" << endl;
                    cout << "========================================" << endl;
                    string modelo;
                    cout << "Ingrese el modelo: ";
                    modelo = validaciones.ingresarString("Ingrese el modelo: ");
                    listaHistorial.BusquedaAvanzada("modelo", modelo,"");
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
                    color = validaciones.ingresarString("Ingrese el color: ");
                    listaHistorial.BusquedaAvanzada("color", color,"");
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
                    listaHistorial.BusquedaAvanzada("fecha", fecha,"");
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
                    marca = validaciones.ingresarString("Ingrese la marca: ");
                    listaHistorial.BusquedaAvanzada("marca", marca,"");
                    break;
                }
            case 4:
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "  Buscar por Hora" << endl;
                    cout << "========================================" << endl;
                    string HoraEntrada1, HoraEntrada2;
                    cout << "Ingrese la hora de entrada 1: ";
                    cin >> HoraEntrada1;
                    cout << "Ingrese la hora de entrada 2: ";
                    cin >> HoraEntrada2;
                    listaHistorial.BusquedaAvanzada("hora", HoraEntrada1, HoraEntrada2);
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
            break;
        }

        case 2: 
            cout << "Saliendo..." << endl;
            return;

        default:
            cout << "Opción invalida. Intentalo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}
