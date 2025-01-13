#pragma once
class Nodo {
public:
    int clave;
    int altura;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(int valor);
};