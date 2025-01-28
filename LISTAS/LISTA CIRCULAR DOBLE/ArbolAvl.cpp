#include "ArbolAVL.h"
#include <iostream>

ArbolAVL::ArbolAVL() : raiz(nullptr) {}


int ArbolAVL::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}


int ArbolAVL::obtenerFactorBalance(NodoAVL* nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
}


NodoAVL* ArbolAVL::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T2 = x->derecho;

 
    x->derecho = y;
    y->izquierdo = T2;

  
    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;
    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;

 
    return x;
}


NodoAVL* ArbolAVL::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T2 = y->izquierdo;

 
    y->izquierdo = x;
    x->derecho = T2;

    x->altura = std::max(obtenerAltura(x->izquierdo), obtenerAltura(x->derecho)) + 1;
    y->altura = std::max(obtenerAltura(y->izquierdo), obtenerAltura(y->derecho)) + 1;

 
    return y;
}


NodoAVL* ArbolAVL::insertar(NodoAVL* nodo, int distancia) {
 
    if (nodo == nullptr) return new NodoAVL(distancia);

    if (distancia < nodo->distancia)
        nodo->izquierdo = insertar(nodo->izquierdo, distancia);
    else if (distancia > nodo->distancia)
        nodo->derecho = insertar(nodo->derecho, distancia);
    else 
        return nodo;

 
    nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

   
    int balance = obtenerFactorBalance(nodo);

 

  
    if (balance > 1 && distancia < nodo->izquierdo->distancia)
        return rotarDerecha(nodo);

 
    if (balance < -1 && distancia > nodo->derecho->distancia)
        return rotarIzquierda(nodo);

    
    if (balance > 1 && distancia > nodo->izquierdo->distancia) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

   
    if (balance < -1 && distancia < nodo->derecho->distancia) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

  
    return nodo;
}


void ArbolAVL::agregarDistancia(int distancia) {
    raiz = insertar(raiz, distancia);
}


void ArbolAVL::mostrarDistancias() {
    recorridoInorden(raiz);
}


void ArbolAVL::recorridoInorden(NodoAVL* nodo) {
    if (nodo == nullptr) return;

    recorridoInorden(nodo->izquierdo);
    std::cout << nodo->distancia << " ";
    recorridoInorden(nodo->derecho);
}