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
    chrono::system_clock::time_point horaSalida;
    int año;
     

public:

    
    Coche() : placa(""), color(""), modelo(""), marca(""), año(0), horaIngreso(chrono::system_clock::now()), horaSalida(chrono::system_clock::time_point()) {}

   
    Coche(string placa, string modelo, string color, string marca, int año)
        : placa(placa), modelo(modelo), color(color), marca(marca), año(año), horaIngreso(chrono::system_clock::now()), horaSalida(chrono::system_clock::time_point()) {}

   
    Coche(string placa, string modelo, string color, string marca, chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida)
        : placa(placa), modelo(modelo), color(color), marca(marca), horaIngreso(horaIngreso), horaSalida(horaSalida), año(0) {}

    

    string getPlaca() const { return placa; }
    string getMarca() const { return marca; }
    string getModelo() const { return modelo; }
    string getColor() const { return color; }
    
    chrono::system_clock::time_point getHora() const { return horaIngreso; }
    chrono::system_clock::time_point getHoraSalida() const { return horaSalida; }

   

    void setPlaca(const string &placa) { this->placa = placa; }
    void setModelo(const string &modelo) { this->modelo = modelo; }
    void setMarca(const string &marca) { this->marca = marca; }
    void setColor(const string &color) { this->color = color; }
    void setHoraSalida(chrono::system_clock::time_point hora) { this->horaSalida = hora; }

   

    void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);
    void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);

    


    friend ostream& operator<<(ostream &os, const Coche &coche)
    {
        os << "Placa: " << coche.placa << "\nMarca: " << coche.marca 
           << " \nModelo: " << coche.modelo << " \nColor: " << coche.color
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
};

