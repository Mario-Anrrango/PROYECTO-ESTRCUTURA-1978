#ifndef PROPIETARIO_H
#define PROPIETARIO_H
#include <iostream>
#include "Lista.h"

class Propietario
{
private:
    std::string nombre;
    std::string apellido;
    std::string cedula;
    std::string correo;
    std::string placaAsociada;

public:
  
   Propietario();
    void menuPropietario(ListaCircularDoble<Propietario> &lista);
    Propietario(std::string nombre, std::string apellido, std::string cedula, std::string correo);

    Propietario insertarDatosPropietario(ListaCircularDoble<Propietario> &lista);
    Propietario buscarPorID(const std::string &id);
    void eliminarPorID( const string &id);

    std::string getNombre() const;
    std::string getApellido() const;
    std::string getCedula() const;
    std::string getCorreo() const;
    std::string getPlacaAsociada() const;

    void setNombre(const std::string &nombre);
    void setApellido(const std::string &apellido);
    void setCedula(const std::string &cedula);
    void setCorreo(const std::string &correo);
   
};

#include "Propietario.cpp"

#endif