#include "Propietario.h"
#include "Validaciones.h"
#include <algorithm>
#include "ValidacionPlaca.h"
#include "Lista.h"

using namespace std;

Propietario::Propietario()
    : nombre(""), apellido(""), cedula(""), correo("") {}

Propietario::Propietario(string nombre, string apellido, string cedula, string correo)
    : nombre(nombre), apellido(apellido), cedula(cedula), correo(correo) {}

void Propietario::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Propietario::setApellido(const string &apellido)
{
    this->apellido = apellido;
}

void Propietario::setCedula(const string &cedula)
{
    this->cedula = cedula;
}

void Propietario::setCorreo(const string &correo)
{
    this->correo = correo;
}

void Propietario::eliminarPlaca(const string &placa)
{
    auto it = find(placas.begin(), placas.end(), placa);
    if (it != placas.end())
    {
        placas.erase(it);
        cout << "Placa eliminada exitosamente." << endl;
    }
    else
    {
        cout << "Placa no encontrada." << endl;
    }
}

string Propietario::getNombre() const
{
    return nombre;
}

string Propietario::getApellido() const
{
    return apellido;
}

string Propietario::getCedula() const
{
    return cedula;
}

string Propietario::getCorreo() const
{
    return correo;
}

void Propietario::agregarPlaca(const string &placa)
{
    placas.push_back(placa);
}

vector<string> Propietario::getPlacas() const
{
    return placas;
}

ostream &operator<<(ostream &os, const Propietario &propietario)
{
    os << "Nombre: " << propietario.getNombre() << "\nApellido: " << propietario.getApellido()
       << "\nCedula: " << propietario.getCedula() << "\nCorreo: " << propietario.getCorreo()
       << "\n----------------------------------------" << endl;

    os << "Placas: ";
    if (propietario.getPlacas().empty())
    {
        os << "N/A";
    }
    else
    {
        for (const auto &placa : propietario.getPlacas())
        {
            os << placa << " ";
        }
    }
    os << "\n----------------------------------------" << endl;

    return os;
}


Propietario Propietario::agregarPropietario()
{
    Validaciones validaciones;
    string nombre = validaciones.ingresarString("Ingrese el nombre del propietario: ");
    string apellido = validaciones.ingresarString("Ingrese el apellido del propietario: ");
    string cedula;
    do {
        cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
        if (!validaciones.validarCedula(cedula)) {
            cout << "Cedula invalida. Intente de nuevo." << endl;
        }
    } while (!validaciones.validarCedula(cedula));
    
    string correo;
    do {
        correo = validaciones.ingresarCorreo("Ingrese el correo electronico del propietario: ");
        if (!validaciones.validarCorreo(correo)) {
            cout << "Correo invalido. Intente de nuevo." << endl;
        }
    } while (!validaciones.validarCorreo(correo));

    Propietario nuevoPropietario(nombre, apellido, cedula, correo);
    
    cout << "Propietario creado exitosamente." << endl;

    return nuevoPropietario;
}


