#pragma once

#include "NodoAVL.h"
#include <string>
#include <SFML/Graphics.hpp>

class ArbolAVL {
private:
    NodoAVL* raiz;

  
    int obtenerAltura(NodoAVL* nodo);
    int obtenerFactorBalance(NodoAVL* nodo);
    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);
    NodoAVL* insertar(NodoAVL* nodo, int distancia);
    void dibujarNodo(NodoAVL* nodo, sf::RenderWindow &ventana, sf::Font &fuente, float x, float y, float offset);


public:
    ArbolAVL();
     NodoAVL* obtenerRaiz();
    void agregarDistancia(int distancia);
    void mostrarDistancias();  
    void mostrarArbol(sf::RenderWindow& ventana, sf::Font& fuente);  
    void vaciarArbol();
    void recorridoInorden(NodoAVL* nodo, bool& detenido);
     void imprimirPrimerTermino(const std::string &salida);
     void imprimirUltimoTermino(const std::string &salida);
     void recorridoInordenUltimo(NodoAVL* nodo, NodoAVL* &ultimo);
    


};
