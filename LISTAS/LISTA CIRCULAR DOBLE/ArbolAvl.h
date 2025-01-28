#pragma once

#include "NodoAVL.h"

class ArbolAVL {
private:
    NodoAVL* raiz;

    
    int obtenerAltura(NodoAVL* nodo);
    int obtenerFactorBalance(NodoAVL* nodo);
    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);
    NodoAVL* insertar(NodoAVL* nodo, int distancia);
    void recorridoInorden(NodoAVL* nodo);

public:
    ArbolAVL();
    void agregarDistancia(int distancia);
    void mostrarDistancias();
};