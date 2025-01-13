#include "ArbolAVL.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

ArbolAVL::~ArbolAVL() {
    
}

int ArbolAVL::obtenerAltura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int ArbolAVL::obtenerBalance(Nodo* nodo) {
    return nodo ? obtenerAltura(nodo->izquierda) - obtenerAltura(nodo->derecha) : 0;
}

Nodo* ArbolAVL::rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;
    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;

    return x;
}

Nodo* ArbolAVL::rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(obtenerAltura(x->izquierda), obtenerAltura(x->derecha)) + 1;
    y->altura = max(obtenerAltura(y->izquierda), obtenerAltura(y->derecha)) + 1;

    return y;
}

Nodo* ArbolAVL::insertar(Nodo* nodo, int clave) {
    if (!nodo)
        return new Nodo(clave);

    if (clave < nodo->clave)
        nodo->izquierda = insertar(nodo->izquierda, clave);
    else if (clave > nodo->clave)
        nodo->derecha = insertar(nodo->derecha, clave);
    else
        return nodo; // No se permiten claves duplicadas.

    nodo->altura = 1 + max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && clave < nodo->izquierda->clave)
        return rotarDerecha(nodo);

    if (balance < -1 && clave > nodo->derecha->clave)
        return rotarIzquierda(nodo);

    if (balance > 1 && clave > nodo->izquierda->clave) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && clave < nodo->derecha->clave) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void ArbolAVL::insertar(int clave) {
    raiz = insertar(raiz, clave);
}

void ArbolAVL::recorridoEnOrden(Nodo* nodo) {
    if (nodo) {
        recorridoEnOrden(nodo->izquierda);
        cout << nodo->clave << " ";
        recorridoEnOrden(nodo->derecha);
    }
}

void ArbolAVL::imprimirEnOrden() {
    recorridoEnOrden(raiz);
    cout << endl;
}


Nodo* ArbolAVL::buscarAVL(Nodo* nodo, int clave) {
    if (!nodo || nodo->clave == clave) {
        return nodo;
    }

    if (clave < nodo->clave) {
        return buscarAVL(nodo->izquierda, clave);  
    } else {
        return buscarAVL(nodo->derecha, clave);  
    }
}

Nodo* ArbolAVL::buscar(int clave) {
    return buscarAVL(raiz, clave);  
}

Nodo* ArbolAVL::eliminar(Nodo* nodo, int clave) {
    if (!nodo) 
        return nodo;  // No se encontró el nodo

    if (clave < nodo->clave) {
        nodo->izquierda = eliminar(nodo->izquierda, clave);
    } else if (clave > nodo->clave) {
        nodo->derecha = eliminar(nodo->derecha, clave);
    } else {
        // Nodo encontrado
        if (!nodo->izquierda || !nodo->derecha) {
            Nodo* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            if (!temp) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }
            delete temp;
        } else {
            Nodo* temp = obtenerNodoMinimo(nodo->derecha);
            nodo->clave = temp->clave;
            nodo->derecha = eliminar(nodo->derecha, temp->clave);
        }
    }

    if (!nodo)
        return nodo;

    nodo->altura = max(obtenerAltura(nodo->izquierda), obtenerAltura(nodo->derecha)) + 1;

    int balance = obtenerBalance(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierda) >= 0)
        return rotarDerecha(nodo);

    if (balance > 1 && obtenerBalance(nodo->izquierda) < 0) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && obtenerBalance(nodo->derecha) <= 0)
        return rotarIzquierda(nodo);

    if (balance < -1 && obtenerBalance(nodo->derecha) > 0) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}


bool ArbolAVL::eliminar(int clave) {
    Nodo* nodoEliminado = eliminar(raiz, clave);
    if (nodoEliminado) {
        raiz = nodoEliminado;  
        return true;  
    }
    return false;  

}

Nodo* ArbolAVL::obtenerNodoMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izquierda) {
        actual = actual->izquierda;
    }
    return actual;
}

void ArbolAVL::imprimirArbol(Nodo* nodo, int espacio) {
    if (nodo == nullptr)
        return;

    const int ESPACIO_EXTRA = 5;

    // Imprimir el nodo raíz antes de continuar con la impresión del árbol
    if (nodo == raiz) {
        cout << "Raíz del árbol: " << nodo->clave << endl;  // Mostrar la raíz
    }

    // Aumentar el espacio para los hijos
    espacio += ESPACIO_EXTRA;

    // Imprimir el subárbol derecho
    imprimirArbol(nodo->derecha, espacio);

    // Imprimir el nodo actual con la indentación correcta
    cout << endl;
    for (int i = ESPACIO_EXTRA; i < espacio; i++)
        cout << " ";
    cout << nodo->clave << endl;

    // Imprimir el subárbol izquierdo
    imprimirArbol(nodo->izquierda, espacio);
}

void ArbolAVL::imprimirArbol() {
    imprimirArbol(raiz, 0);
}