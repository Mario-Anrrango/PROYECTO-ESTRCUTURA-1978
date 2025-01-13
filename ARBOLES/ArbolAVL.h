#pragma once
#include "Nodo.h"

class ArbolAVL {
private:
    Nodo* raiz;

    int obtenerAltura(Nodo* nodo);
    int obtenerBalance(Nodo* nodo);
    Nodo* rotarDerecha(Nodo* y);
    Nodo* rotarIzquierda(Nodo* x);
    Nodo* insertar(Nodo* nodo, int clave);
    void recorridoEnOrden(Nodo* nodo);
    Nodo* obtenerNodoMinimo(Nodo* nodo);
    Nodo* eliminar(Nodo* nodo, int clave);

public:
    ArbolAVL();
    ~ArbolAVL();

    void insertar(int clave);
    void imprimirEnOrden();
    bool eliminar(int clave);
    Nodo* buscarAVL(Nodo* nodo, int clave);
    Nodo* buscar(int clave);

};