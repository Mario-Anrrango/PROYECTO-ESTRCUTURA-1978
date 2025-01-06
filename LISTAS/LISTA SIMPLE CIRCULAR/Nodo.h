#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Nodo
{
private:
    T dato;
    Nodo *siguiente;

public:
    Nodo(T dato);

    T getDato();
    void setDato(T dato);

    void setSiguiente(Nodo *siguiente);
    Nodo *getSiguiente();
};

#include "Nodo.cpp"
