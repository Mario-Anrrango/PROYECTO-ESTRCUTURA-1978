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

    void setPrimero(Nodo<T>* primero) {
        this->primero = primero;
    }
    ListaCircularDoble();     
    void insertar(T dato,const std::string& nombreArchivo);    
    void buscarPorPlaca(string placa);
    void BusquedaAvanzada(string criterio, string valorInicio, string valorFin);      
    void eliminarPorPlaca(string placa);    
    void mostrar(Nodo<T> *aux);  
    void CargarArchivo(string nombreArchivo);
    void GuardarArchivo(string nombreArchivo);
    string cifrarTexto(const std::string& texto);
    string descifrarTexto(const std::string& texto);
    void salirDelParqueadero(const std::string& placa);
    void GuardarArchivoPropietario(const string& nombreArchivo, ListaCircularDoble<T>& lista);
    void CargarArchivoPropietario(const std::string& nombreArchivo);
};

#include "Lista.cpp"


