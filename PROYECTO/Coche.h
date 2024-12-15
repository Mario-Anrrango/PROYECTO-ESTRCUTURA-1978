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
    std::chrono::system_clock::time_point horaSalida;
    int año;

public:
    Coche()
    {
        this->placa = "";
        this->marca = "";
        this->modelo = "";
        this->color = "";
    }

    Coche(string placa, string modelo, string color, string marca, int año) : placa(placa), modelo(modelo), color(color), marca(marca), horaIngreso(chrono::system_clock::now()) {}

    Coche(std::string placa, std::string modelo, std::string color, std::string marca,
          std::chrono::system_clock::time_point horaIngreso, std::chrono::system_clock::time_point horaSalida)
        : placa(placa), modelo(modelo), color(color), marca(marca), año(año),
          horaIngreso(horaIngreso), horaSalida(horaSalida) {}

    void setHoraSalida(std::chrono::system_clock::time_point hora)
    {
        horaSalida = hora;
    }

    chrono::system_clock::time_point getHoraSalida() const
    {
        return horaSalida;
    }

    string getPlaca() const
    {
        return placa;
    }

    string getMarca() const
    {
        return marca;
    }

    string getModelo() const
    {
        return modelo;
    }

    string getColor() const
    {
        return color;
    }

    int getAño() const
    {
        return año;
    }

    chrono::system_clock::time_point getHora() const
    {
        return horaIngreso;
    }

    void setPlaca(const string &placa)
    {
        this->modelo = placa;
    }

    void setModelo(const string &modelo)
    {
        this->modelo = modelo;
    }

    void setMarca(const string &marca)
    {
        this->marca = marca;
    }

    void setColor(const string &color)
    {
        this->color = color;
    }

    void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);

    void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);

    friend std::ostream &operator<<(std::ostream &os, const Coche &coche)
    {
        os << "Placa: " << coche.placa << "\nMarca: " << coche.marca << " \nModelo: " << coche.modelo << " \nColor: " << coche.color
           << "\n----------------------------------------" << std::endl;

        time_t tiempoIngreso = chrono::system_clock::to_time_t(coche.horaIngreso);
        os << "\nHora de Ingreso: " << std::ctime(&tiempoIngreso)
           << "\n----------------------------------------" << std::endl;

        if (coche.horaSalida == std::chrono::system_clock::time_point())
        {
            os << "\nHora de Salida: N/A" << std::endl;
        }
        else
        {
            time_t tiempoSalida = chrono::system_clock::to_time_t(coche.horaSalida);
            os << "\nHora de Salida: " << std::ctime(&tiempoSalida)
               << "\n----------------------------------------" << std::endl;
        }

        return os;
    }
};
