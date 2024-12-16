#ifndef VALIDACION_CEDULA_H
#define VALIDACION_CEDULA_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <stdexcept>
#include "Nodo.h"
#include "Lista.h"

using namespace std;

class Cedula  
{
public:
    string ingresarCedula(Nodo<Propietario>* aux);  
     bool validarCodigoProvincia(const string &cedula);
    bool validarDigitoVerificador(const string &cedula);
private:
   
};


#endif