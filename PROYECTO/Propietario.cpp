#include "Propietario.h"
#include <iostream>
#include <string>
#include "Coche.h"  
#include "Validaciones.h"
#include <vector>
#include "ValidacionPlaca.h"
#include "Menu.h"
#include "Lista.h"

using namespace std;

string NombreArchivoPropietarios = "Propietarios.txt";
ListaCircularDoble<Propietario> listaPropietarios;
Validaciones validaciones;

Propietario Propietario::insertarDatosPropietario(ListaCircularDoble<Propietario> &lista)
{
    
    string nombre, apellido, cedula, correo;

   
    while (true) {
        cedula = validaciones.ingresarCedula("Ingrese la Cedula: ");

       
        if (buscarPorID(cedula).getCedula() != "") {
            cout << "La cédula ya está registrada. Por favor, ingrese una cédula diferente." << endl;
        } else {
            break; 
        }
    }

   
    nombre = validaciones.ingresarString("Ingrese el nombre: ");
    apellido = validaciones.ingresarString("Ingrese el apellido: ");
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
std::string Propietario::getPlacaAsociada() const {
    return placaAsociada;
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


Propietario Propietario::buscarPorID(const std::string &id)
{
    Nodo<Propietario>* temp = listaPropietarios.getPrimero();
    
    if (temp == nullptr) {
        cout << "La lista de propietarios está vacía." << endl;
        return Propietario(); 
    }

    do {
        if (temp->getDato().getCedula() == id) {
            cout << "Propietario encontrado: " << temp->getDato().getNombre() << " " << temp->getDato().getApellido() << endl;
            return temp->getDato(); 
        }
        temp = temp->getSiguiente();
    } while (temp != listaPropietarios.getPrimero()); 

    cout << "No se encontró ningún propietario con esa cédula." << endl;
    return Propietario(); 
}


void Propietario::menuPropietario(ListaCircularDoble<Propietario> &lista)
{
    vector<string> opciones = {
        "Insertar Propietario",
        "Buscar Propietario",
        "Eliminar Propietario",
        "Salir"};

    while (true)
    {
        int seleccion = menuInteractivo(opciones, "Menu de Propietarios");

        switch (seleccion)
        {
        case 0:
        {
            Propietario nuevoPropietario = insertarDatosPropietario(lista);
            lista.insertar(nuevoPropietario, NombreArchivoPropietarios);
            lista.GuardarArchivoPropietario(NombreArchivoPropietarios, lista);
            break;
        }
        case 1:
        {
            system("cls");
            cout << "=====================================" << endl;
            cout << "     Buscando Propietario           " << endl;
            cout << "=====================================" << endl;
            string id;
            cout << "Ingrese la cédula del propietario a buscar: ";
            cin >> id;
            Propietario propietario = buscarPorID(id);
            if (!propietario.getCedula().empty()) {
                cout << "Propietario encontrado: " << propietario.getNombre() << endl;
            } else {
                cout << "No se encontró ningún propietario con esa cédula." << endl;
            }
            break;
        }
        case 2:
        {
            system("cls");
            cout << "=====================================" << endl;
            cout << "     Eliminando Propietario          " << endl;
            cout << "=====================================" << endl;
            string id;

          
            while (true) {
                id = validaciones.ingresarCedula("Ingrese la cédula del propietario a eliminar: ");
                
                if (!id.empty()) {
                    break; 
                } else {
                    cout << "Cédula inválida. Inténtelo nuevamente." << endl;
                }
            }

            eliminarPorID(id);
            lista.GuardarArchivoPropietario( NombreArchivoPropietarios, lista);
            break;
        }
        case 3:
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

Propietario::Propietario() {
   
    this->nombre = "";
    this->apellido = "";
    this->cedula = "";
    this->correo = "";
}

Propietario::Propietario(std::string nombre, std::string apellido, std::string cedula, std::string correo)
{
        this->nombre = nombre;
    this->apellido = apellido;
    this->cedula = cedula;
    this->correo = correo;
}

void Propietario::eliminarPorID( const string &id)
{
    Nodo<Propietario>* temp = listaPropietarios.getPrimero();  

    
    if (temp == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    
    do {
        if (temp->getDato().getCedula() == id) {
           
            if (temp == listaPropietarios.getPrimero() && temp->getSiguiente() == listaPropietarios.getPrimero()) {
               
                listaPropietarios.setPrimero(nullptr);
            } else {
                
                temp->getAnterior()->setSiguiente(temp->getSiguiente());  
                temp->getSiguiente()->setAnterior(temp->getAnterior());  
                if (temp == listaPropietarios.getPrimero()) {
                    listaPropietarios.setPrimero(temp->getSiguiente());  
                }
            }
            delete temp;  
            cout << "Propietario con cédula " << id << " ha sido eliminado." << endl;
            return;
        }
        temp = temp->getSiguiente();  
    } while (temp != listaPropietarios.getPrimero());  

    
    cout << "Propietario con cédula " << id << " no encontrado." << endl;
}

