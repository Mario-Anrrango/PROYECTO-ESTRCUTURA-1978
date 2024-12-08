#pragma once 
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "Lista.h"

using namespace std;

class Coche
{
private:

    string placa;
    string color;
    string modelo;
    string marca;
    chrono::system_clock::time_point horaIngreso;

    
public:
  Coche() {
    this->placa = "";
    this->marca = "";
    this->modelo = "";
    this->color = "";
}

    Coche(string placa , string modelo , string color , string marca):
     placa(placa), modelo(modelo) ,color (color),marca(marca),horaIngreso(chrono::system_clock::now()){}

string getPlaca() const
 {return placa;}

string getMarca() const
 {return marca;}

string getModelo() const 
{return modelo;}

string getColor () const
{return color;}

chrono::system_clock::time_point getHora() const
 {return horaIngreso;}

void setPlaca(const string& placa) 
{ this->modelo = placa; }

void setModelo(const string& modelo) 
{ this->modelo = modelo; }

void setMarca(const string& marca) 
{ this->marca = marca; }

void setColor(const string& color) 
{ this->color = color; }

void menu(ListaCircularDoble<Coche>& lista);

friend std::ostream& operator<<(std::ostream& os, const Coche& coche) {
        os << "Placa: " << coche.placa << "\n Marca: " << coche.marca << " \n Modelo: " << coche.modelo << " \n Color: " << coche.color << "\n----------------------------------------" << std::endl;

     
     time_t tiempo = chrono::system_clock::to_time_t(coche.horaIngreso);
    os << "\nHora de Ingreso: " << std::ctime(&tiempo); 


        return os;
    }

};


