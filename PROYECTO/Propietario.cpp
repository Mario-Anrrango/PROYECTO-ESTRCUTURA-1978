#include "Propietario.h"
#include <iostream>
#include <string>
#include "Coche.h"  
#include "Validaciones.h"
#include "Menu.h"
#include "Cedula.h"
#include "Lista.h"
#include "Nodo.h"
#include <vector>


Propietario::Propietario(std::string nombre, std::string apellido, std::string cedula, std::string correo) 
    : nombre(nombre), apellido(apellido), cedula(cedula), correo(correo) {}


Propietario Propietario::insertarDatosPropietario(ListaCircularDoble<Propietario> &lista, const string &placa)
{
    Validaciones validaciones;
    Cedula validador;
    string nombre, apellido, cedula, correo;

    nombre = validaciones.ingresarString("Ingrese el nombre: ");
    apellido = validaciones.ingresarString("Ingrese el apellido: ");

    while (true)
    {
        cedula = validador.ingresarCedula(lista.getPrimero());

        Nodo<Propietario> *temp = lista.getPrimero();
        bool cedulaDuplicada = false;

        if (temp != nullptr)
        {
            do
            {
                Propietario propietarioActual = temp->getDato();

           
                if (propietarioActual.getCedula() == cedula)
                {
                    cout << "\nLa cédula " << cedula << " ya está registrada en el sistema. Ingrese una cédula nueva." << endl;
                    cedulaDuplicada = true;
                    break;
                }

                temp = temp->getSiguiente();
            } while (temp != lista.getPrimero());
        }

        if (!cedulaDuplicada)
        {
            break;
        }
    }


    Nodo<Propietario> *tempHistorial = lista.getPrimero();
    if (tempHistorial != nullptr)
    {
        do
        {
            Propietario propietarioHistorial = tempHistorial->getDato();

            if (propietarioHistorial.getCedula() == cedula)
            {
                cout << "\nLa cédula " << cedula << " fue encontrada en el historial. Recuperando datos..." << endl;
                nombre = propietarioHistorial.getNombre();
                apellido = propietarioHistorial.getApellido();
                correo = propietarioHistorial.getCorreo();

                cout << "Nombre: " << nombre << "\nApellido: " << apellido << "\nCorreo: " << correo << "\n";

                vector<string> opciones = {"Sí", "No"};
                int seleccion = menuInteractivo(opciones, "Propietario encontrado en el sistema. ¿Desea sobreescribir los datos del historial?");

                if (seleccion == 0) 
                {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "========================================" << endl;
                    cout << "        Datos Recuperados Exitosamente  " << endl;
                    cout << "========================================" << endl;
                    cout << "========================================" << endl;

                    cout << "\nNombre:    " << nombre << endl;
                    cout << "Apellido:  " << apellido << endl;
                    cout << "Correo:    " << correo << endl;
                    cout << "Cédula:    " << cedula << endl;

                    return Propietario(nombre, apellido, cedula, correo);
                }
                else 
                {
                    system("cls");
                    cout << "\nPor favor, ingrese los datos manualmente:" << endl;
                    break;
                }
            }

            tempHistorial = tempHistorial->getSiguiente();
        } while (tempHistorial != lista.getPrimero());
    }

    correo = validaciones.ingresarString("Ingrese el correo: ");

    return Propietario(nombre, apellido, cedula, correo);
}


std::string Propietario::getNombre() const {
    return nombre;
}

std::string Propietario::getApellido() const {
    return apellido;
}

std::string Propietario::getCedula() const {
    return cedula;
}

std::string Propietario::getCorreo() const {
    return correo;
}

void Propietario::setNombre(const std::string &nombre) {
    this->nombre = nombre;
}

void Propietario::setApellido(const std::string &apellido) {
    this->apellido = apellido;
}

void Propietario::setCedula(const std::string &cedula) {
    this->cedula = cedula;
}

void Propietario::setCorreo(const std::string &correo) {
    this->correo = correo;
}
