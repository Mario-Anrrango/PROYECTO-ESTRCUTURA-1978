#include <iostream>
#include "Coche.h"
#include "Menu.h"
#include "Propietario.h"
#include "ValidacionPlaca.h"
#include "Validaciones.h"
#include <string> 
#include <vector>
#include <cstdlib>

using namespace std;

Coche::Coche()
{
    this->placa = "";
    this->marca = "";
    this->modelo = "";
    this->color = "";
}

Coche::Coche(string placa, string modelo, string color, string marca, int anio)
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(anio), horaIngreso(chrono::system_clock::now()) {}

Coche::Coche(string placa, string modelo, string color, string marca,
             chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida )
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(0), horaIngreso(horaIngreso), horaSalida(horaSalida) {}


void Coche::setHoraSalida(chrono::system_clock::time_point hora)
{
    horaSalida = hora;
}

void Coche::setPlaca(const string &placa)
{
    this->placa = placa;
}

void Coche::setModelo(const string &modelo)
{
    this->modelo = modelo;
}

void Coche::setMarca(const string &marca)
{
    this->marca = marca;
}

void Coche::setColor(const string &color)
{
    this->color = color;
}

chrono::system_clock::time_point Coche::getHoraSalida() const
{
    return horaSalida;
}

string Coche::getPlaca() const
{
    return placa;
}

string Coche::getMarca() const
{
    return marca;
}

string Coche::getModelo() const
{
    return modelo;
}

string Coche::getColor() const
{
    return color;
}

int Coche::getAnio() const
{
    return anio;
}

chrono::system_clock::time_point Coche::getHora() const
{
    return horaIngreso;
}



ostream &operator<<(ostream &os, const Coche &coche)
{
    os << "Placa: " << coche.placa << "\nMarca: " << coche.marca
       << "\nModelo: " << coche.modelo << "\nColor: " << coche.color
       << "\n----------------------------------------" << endl;

    time_t tiempoIngreso = chrono::system_clock::to_time_t(coche.horaIngreso);
    os << "\nHora de Ingreso: " << ctime(&tiempoIngreso)
       << "\n----------------------------------------" << endl;

    if (coche.horaSalida == chrono::system_clock::time_point())
    {
        os << "\nHora de Salida: N/A" << endl;
    }
    else
    {
        time_t tiempoSalida = chrono::system_clock::to_time_t(coche.horaSalida);
        os << "\nHora de Salida: " << ctime(&tiempoSalida)
           << "\n----------------------------------------" << endl;
    }

    return os;
}


Coche Coche::InsertarDatos(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial, ListaCircularDoble<Propietario> &listaPropietarios)
{
    Validaciones validaciones;
    Placa<Coche> validador;

    string placa, modelo, color, marca, cedula;
    int anio = 0;

    Nodo<Propietario> *propietarioNodo = nullptr;
    bool propietarioEncontrado = false;

    // Buscar propietario por cédula
    while (!propietarioEncontrado)
    {
        cedula = validaciones.ingresarCedula("Ingrese el numero de cedula del propietario: ");
        propietarioNodo = listaPropietarios.getPrimero();

        do {
            if (propietarioNodo->getDato().getCedula() == cedula) {
                propietarioEncontrado = true;
                break;
            }
            propietarioNodo = propietarioNodo->getSiguiente();
        } while (propietarioNodo != listaPropietarios.getPrimero());

        if (!propietarioEncontrado) {
            cout << "No se encontro un propietario con esa cedula. Por favor, intente de nuevo." << endl;
        }
    }

    // Mostrar placas del historial que no estén en el parqueadero
    vector<string> opcionesPlacas;
    Nodo<Coche> *tempHistorial = listaHistorial.getPrimero();
    if (tempHistorial != nullptr)
    {
        do
        {
            Coche cocheHistorial = tempHistorial->getDato();
            bool placaEnParqueadero = false;

            Nodo<Coche> *temp = lista.getPrimero();
            if (temp != nullptr)
            {
                do
                {
                    if (temp->getDato().getPlaca() == cocheHistorial.getPlaca() && temp->getDato().getHoraSalida() == chrono::system_clock::time_point())
                    {
                        placaEnParqueadero = true;
                        break;
                    }
                    temp = temp->getSiguiente();
                } while (temp != lista.getPrimero());
            }

            if (!placaEnParqueadero)
            {
                opcionesPlacas.push_back(cocheHistorial.getPlaca());
            }

            tempHistorial = tempHistorial->getSiguiente();
        } while (tempHistorial != listaHistorial.getPrimero());
    }

    opcionesPlacas.push_back("Agregar nueva placa");

    // Selección de placa
    int seleccionPlaca = menuInteractivo(opcionesPlacas, "Seleccione una placa existente o agregue una nueva:");

    if (seleccionPlaca != opcionesPlacas.size() - 1) {
        placa = opcionesPlacas[seleccionPlaca];

        // Recuperar datos del historial
        tempHistorial = listaHistorial.getPrimero();
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

                    return Coche(placa, modelo, color, marca, anio);
                }

                tempHistorial = tempHistorial->getSiguiente();
            } while (tempHistorial != listaHistorial.getPrimero());
        }
    } else {
        // Validar nueva placa
        while (true)
        {
            placa = validador.ingresarPlaca(listaHistorial.getPrimero());

            bool placaExistente = false;
            tempHistorial = listaHistorial.getPrimero();
            if (tempHistorial != nullptr)
            {
                do
                {
                    if (tempHistorial->getDato().getPlaca() == placa)
                    {
                        cout << "\nLa placa ingresada ya existe en el historial. Ingrese una placa nueva." << endl;
                        placaExistente = true;
                        break;
                    }
                    tempHistorial = tempHistorial->getSiguiente();
                } while (tempHistorial != listaHistorial.getPrimero());
            }

            if (!placaExistente)
            {
                break;
            }
        }

        // Ingresar datos manualmente
        marca = validaciones.ingresarString("Ingrese la marca: ");
        color = validaciones.ingresarString("Ingrese el color: ");
        modelo = validaciones.ingresarString("Ingrese el modelo: ");
    }

    return Coche(placa, modelo, color, marca, anio);
}
