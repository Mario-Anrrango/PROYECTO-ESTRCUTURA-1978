#pragma once
#include "Nodo.h"

using namespace std;

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
    void buscarPorPlaca(string placa);
    void BusquedaAvanzada(string criterio , string valor);      
    void eliminarPorPlaca(string placa);    
    void mostrar(Nodo<T> *aux);  
    void CargarArchivo(string nombreArchivo);
    void GuardarArchivo(string nombreArchivo);
    string cifrarTexto(const std::string& texto);
    string descifrarTexto(const std::string& texto);
};

#include "Lista.cpp"

