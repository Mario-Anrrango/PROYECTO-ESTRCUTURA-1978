#pragma once
#include <string>
#include "Lista.h"  

class Propietario {
private:
    std::string nombre;
    std::string apellido;
    std::string cedula;
    std::string correo;

public:
   
    Propietario(std::string nombre, std::string apellido, std::string cedula, std::string correo);

   
    
    Propietario insertarDatosPropietario(ListaCircularDoble<Propietario> &lista, string const &placa);
  
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getCedula() const;
    std::string getCorreo() const;
    void setNombre(const std::string &nombre);
    void setApellido(const std::string &apellido);
    void setCedula(const std::string &cedula);
    void setCorreo(const std::string &correo);
};

#include "Propietario.cpp" 
