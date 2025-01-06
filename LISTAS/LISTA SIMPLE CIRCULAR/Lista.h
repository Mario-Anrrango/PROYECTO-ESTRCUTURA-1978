#pragma once
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* primero;

public:
    Nodo<T>* getPrimero() {
        return primero;
    }
    ListaCircularDoble();
    void insertar(T dato);
    void buscarPorPlaca(string placa);
    void eliminarPorPlaca(string placa);
    void mostrar(Nodo<T> *aux);
    void CargarArchivo(string nombreArchivo);
    void GuardarArchivo(string nombreArchivo);
    bool estaVacia() const;
    void GuardarPropietarios(const std::string& nombreArchivo);
    void CargarPropietarios(const std::string& nombreArchivo);
    void BusquedaAvanzada(string criterio, string valorInicio, string valorFin);
    void BusquedaAvanzadaPropietario(string criterio, string valorInicio, string valorFin);
    std::string cifrarTexto(const std::string& texto);
    std::string descifrarTexto(const std::string& texto);
    void salirDelParqueadero(const std::string& placa);
};

#include "Lista.cpp"
