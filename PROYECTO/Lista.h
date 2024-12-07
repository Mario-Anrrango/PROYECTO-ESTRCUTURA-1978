#pragma once
#include "Nodo.h"

template <typename T>
class ListaCircularDoble {
private:
      
    Nodo<T>* ultimo;    
    Nodo<T>* primero;
public:
     
  Nodo<T>* getPrimero() {
        return primero;
    }
    ListaCircularDoble();     
    void insertar(T dato);    
    void buscarPorPlaca(T dato);
    void buscarPorHistorial(T dato);     
    void eliminar(T dato);    
    void mostrar(Nodo<T> *aux);           
};

#include "Lista.cpp"

