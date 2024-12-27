#include <iostream>
#include <vector>
#include <conio.h>
#include "Propietario.h"
#include "Coche.h"
#include "Lista.h"
#include "Validaciones.h"
#include "ValidacionPlaca.h"
#include "Menu.h"

using namespace std;

Coche coche;

template <typename T>
void menuEliminarPlaca(ListaCircularDoble<Propietario> &listaPropietarios)
{
    Placa<Propietario> validador;
    Validaciones validaciones;
    system("cls");
    cout << "========================================" << endl;
    cout << "========================================" << endl;
    cout << "    ELIMINAR PLACA DE PROPIETARIO       " << endl;
    cout << "========================================" << endl;
    cout << "========================================" << endl;

    string cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
    Nodo<T> *aux = listaPropietarios.getPrimero();
    bool encontrado = false;

    do {
        if (aux->getDato().getCedula() == cedula) {
            encontrado = true;
            cout << "========================================" << endl;
            cout << "   PROPIETARIO REGISTRADO" << endl;
            cout << "========================================" << endl;
            cout << aux->getDato() << endl;

            vector<string> placas = aux->getDato().getPlacas();

            if (placas.empty()) {
                cout << "Este propietario no tiene placas asociadas." << endl;
                return;
            }
            
            vector<string> opcionesPlacas = placas;
            opcionesPlacas.push_back("Volver");
            int seleccion = menuInteractivo(opcionesPlacas, "Seleccionar Placa a Eliminar");

            if (seleccion == opcionesPlacas.size() - 1) {
                return;
            }

            string placa = placas[seleccion];

            vector<string> placasActualizadas = aux->getDato().eliminarPlaca(placa);

            
            Propietario propietarioActualizado(aux->getDato().getNombre(), aux->getDato().getApellido(), 
                                               aux->getDato().getCedula(), aux->getDato().getCorreo());

            propietarioActualizado.setPlacas(placasActualizadas);

            
            aux->setDato(propietarioActualizado);
            cout << aux->getDato() << endl;

            listaPropietarios.GuardarPropietarios("propietarios.txt");

            break;
        }
        aux = aux->getSiguiente();
    } while (aux != listaPropietarios.getPrimero() && !encontrado);

    if (!encontrado) {
        cout << "No se encontró un propietario con esa cédula." << endl;
    }
}




int menuInteractivo(const vector<string> &opciones, const string &titulo)
{
    int seleccion = 0;
    const int numOpciones = opciones.size();

    while (true)
    {
        system("cls");

        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "        " << titulo << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numOpciones; ++i)
        {
            if (i == seleccion)
            {
                cout << " > " << opciones[i] << " < " << endl;
            }
            else
            {
                cout << "   " << opciones[i] << endl;
            }
        }

        cout << "========================================" << endl;

        char tecla = _getch();

        if (tecla == 'a' || tecla == 72)
        {
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        }
        else if (tecla == 's' || tecla == 80)
        {
            seleccion = (seleccion + 1) % numOpciones;
        }
        else if (tecla == 13)
        {
            return seleccion;
        }
    }
}

void menuGestionPropietarios(ListaCircularDoble<Propietario> &listaPropietarios)
{ 
    
    bool salirSubmenu = false;
    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "========================================" << endl;
        cout << "      Menu de Gestion de Propietarios   " << endl;
        cout << "========================================" << endl;
        cout << "========================================" << endl;

        vector<string> opcionesPropietarios = {
            "Agregar Propietario",
            "Mostrar Propietarios",
            "Busqueda Avanzada",
            "Eliminar Placa de Propietario",
            "Volver al Menu Principal"};

        int seleccionPropietarios = menuInteractivo(opcionesPropietarios, "Menu de Gestion de Propietarios");
       
       
        switch (seleccionPropietarios)
        {
        case 0:
            {
                Propietario nuevoPropietario = nuevoPropietario.agregarPropietario();
                listaPropietarios.insertar(nuevoPropietario);
                listaPropietarios.GuardarPropietarios("propietarios.txt");
                break;
            }
        case 1:
            listaPropietarios.mostrar(listaPropietarios.getPrimero());
            system("pause");
            break;
        case 2:
            {
                system("cls");
                cout << "========================================" << endl;
                cout << "          BUSQUEDA AVANZADA             " << endl;
                cout << "========================================" << endl;
                menuBusquedaAvanzadaPropietario(listaPropietarios);
                system("pause");
                break;
            }
        case 3:
          {
            menuEliminarPlaca<Propietario>(listaPropietarios);
           
        }
        case 4:
            salirSubmenu = true;
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    }
}

void menuBusquedaAvanzadaPropietario(ListaCircularDoble<Propietario> &listaPropietarios)
{

  Validaciones validaciones;
    vector<string> opcionesBusqueda = {
        "Buscar por Cedula",
        "Buscar por Correo",
        "Buscar por Nombre",
        "Buscar por Apellido",
        "Volver al Menu Principal"};

    while (true)
    {
        int seleccionBusqueda = menuInteractivo(opcionesBusqueda, "Menu de Busqueda Avanzada");

        switch (seleccionBusqueda)
        {
        case 0:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Cedula" << endl;
            cout << "========================================" << endl;
            string cedula;
            cout << "Ingrese la cedula: ";
            cedula = validaciones.ingresarCedula("Ingrese la cedula: ");
            listaPropietarios.BusquedaAvanzadaPropietario("cedula", cedula, "");
            break;
        }
        case 1:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Correo" << endl;
            cout << "========================================" << endl;
            string correo;
            cout << "Ingrese el correo: ";
            correo = validaciones.ingresarCorreo("Ingrese el correo: ");
            listaPropietarios.BusquedaAvanzadaPropietario("correo", correo, "");
            break;
        }
        case 2:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Nombre" << endl;
            cout << "========================================" << endl;
            string nombre;
            cout << "Ingrese el nombre: ";
            nombre = validaciones.ingresarString("Ingrese el nombre: ");
            listaPropietarios.BusquedaAvanzadaPropietario("nombre", nombre, "");
            break;
        }
        case 3:
        {
            system("cls");
            cout << "========================================" << endl;
            cout << "  Buscar por Apellido" << endl;
            cout << "========================================" << endl;
            string apellido;
            cout << "Ingrese el apellido: ";
            apellido = validaciones.ingresarString("Ingrese el apellido: ");
            listaPropietarios.BusquedaAvanzadaPropietario("apellido", apellido, "");
            break;
        }
        case 4:
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

void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios)
{
    Placa<Coche> validador;

    vector<string> opciones = {
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Busqueda de Coche Por Placa",
        "Busqueda Avanzada",
        "Menu de Gestion de Propietarios",
        "Liberar el parqueadero",
        "Ordenar lista de coches",
        "Ayuda",
        "Salir"};

    string archivo = "autos.txt";
    string archivoHistorial = "autos_historial.txt";

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Parqueadero");

        switch (seleccion)
        {
        case 0:
        {

            if (listaPropietarios.estaVacia())
            {
                cout << "No hay propietarios registrados. Por favor, registre un propietario antes de continuar." << endl;
                break;
            }

            Coche nuevoCoche = nuevoCoche.InsertarDatos(lista, listaHistorial, listaPropietarios);
            lista.insertar(nuevoCoche);
            lista.GuardarArchivo("autos.txt");
            listaHistorial.insertar(nuevoCoche);
            listaHistorial.GuardarArchivo("autos_historial.txt");
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
            menuGestionPropietarios(listaPropietarios);
            break;
        case 5:
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
        case 6:
        {
           /* menuOrdenar(lista, listaHistorial, listaPropietarios);*/
            break;
        }
        case 7:
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
        case 8:
        {
            cout << "Saliendo..." << endl;
            return;
        }
        default:
            cout << "Opcion invalida. Inténtelo de nuevo." << endl;
            break;
        }

        system("pause");
    }
}

void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial)
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
                lista.BusquedaAvanzada("modelo", modelo, "");
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

                lista.BusquedaAvanzada("color", color, "");
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
                lista.BusquedaAvanzada("fecha", fecha, "");
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

                lista.BusquedaAvanzada("marca", marca, "");
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
                listaHistorial.BusquedaAvanzada("modelo", modelo, "");
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
                listaHistorial.BusquedaAvanzada("color", color, "");
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
                listaHistorial.BusquedaAvanzada("fecha", fecha, "");
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
                listaHistorial.BusquedaAvanzada("marca", marca, "");
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

 /*void menuOrdenar(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios)
{
    bool salirSubmenu = false;

    while (!salirSubmenu)
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "           Menu de Ordenamiento         " << endl;
        cout << "========================================" << endl;

        vector<string> opcionesLista = {
            "Ordenar en Lista del Parqueadero",
            "Ordenar en el Historial",
            "Ordenar Propietarios",
            "Volver al Menu Principal"};

        int seleccionLista = menuInteractivo(opcionesLista, "Seleccione la lista a ordenar:");

        if (seleccionLista == 3)
        {
            salirSubmenu = true;
            continue;
        }

        vector<string> opcionesOrdenar;
        int seleccionOrdenar = 0;

        if (seleccionLista == 0 || seleccionLista == 1) 
        {
            opcionesOrdenar = {
                "Ordenar por Placa",
                "Ordenar por Modelo",
                "Ordenar por Marca",
                "Volver al Menu Principal"};

            seleccionOrdenar = menuInteractivo(opcionesOrdenar, "Seleccione el criterio de ordenamiento:");
        }
        else if (seleccionLista == 2)
        {
            opcionesOrdenar = {
                "Ordenar por Nombre del Propietario",
                "Ordenar por Apellido del Propietario",
                "Ordenar por Cédula del Propietario",
                "Ordenar por Correo del Propietario",
                "Volver al Menu Principal"};

            seleccionOrdenar = menuInteractivo(opcionesOrdenar, "Seleccione el criterio de ordenamiento:");
        }

        if (seleccionOrdenar == opcionesOrdenar.size() - 1)
        {
            continue; // Volver al menú si se selecciona la opción "Volver al Menu Principal"
        }

        // Ordenar la lista del parqueadero
        if (seleccionLista == 0) 
        {
            switch (seleccionOrdenar)
            {
            case 0: 
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                                     { return a.getPlaca() < b.getPlaca(); });
                cout << "Lista del Parqueadero ordenada por placa usando QuickSort." << endl;
                break;
            case 1: 
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                                     { return a.getModelo() < b.getModelo(); });
                cout << "Lista del Parqueadero ordenada por modelo usando QuickSort." << endl;
                break;
            case 2: 
                ordenarLista(lista, [](const Coche &a, const Coche &b)
                                     { return a.getMarca() < b.getMarca(); });
                cout << "Lista del Parqueadero ordenada por marca usando QuickSort." << endl;
                break;
            }
        }

      
        else if (seleccionLista == 1) 
        {
            switch (seleccionOrdenar)
            {
            case 0: 
                ordenarLista(listaHistorial, [](const Coche &a, const Coche &b)
                                     { return a.getPlaca() < b.getPlaca(); });
                cout << "Historial ordenado por placa usando QuickSort." << endl;
                break;
            case 1: 
                ordenarLista(listaHistorial, [](const Coche &a, const Coche &b)
                                     { return a.getModelo() < b.getModelo(); });
                cout << "Historial ordenado por modelo usando QuickSort." << endl;
                break;
            case 2: 
                ordenarLista(listaHistorial, [](const Coche &a, const Coche &b)
                                     { return a.getMarca() < b.getMarca(); });
                cout << "Historial ordenado por marca usando QuickSort." << endl;
                break;
            }
        }

        }
    }
*/