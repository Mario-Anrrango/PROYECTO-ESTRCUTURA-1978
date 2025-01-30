#include "ArbolAVL.h"
#include <iostream>
#include "Coche.h"


ArbolAVL::ArbolAVL() : raiz(nullptr) {}


void ArbolAVL::agregarDistancia(int distancia) {
    raiz = insertar(raiz, distancia);
}


NodoAVL* ArbolAVL::insertar(NodoAVL* nodo, int distancia) {
    if (nodo == nullptr) {
        return new NodoAVL(distancia);
    }

    if (distancia < nodo->distancia) {
        nodo->izquierdo = insertar(nodo->izquierdo, distancia);
    } else if (distancia > nodo->distancia) {
        nodo->derecho = insertar(nodo->derecho, distancia);
    } else {
        return nodo;  
    }

    nodo->altura = 1 + std::max(obtenerAltura(nodo->izquierdo), obtenerAltura(nodo->derecho));

    int balance = obtenerFactorBalance(nodo);

 
    if (balance > 1 && distancia < nodo->izquierdo->distancia) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && distancia > nodo->derecho->distancia) {
        return rotarIzquierda(nodo);
    }

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


int ArbolAVL::obtenerAltura(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}


int ArbolAVL::obtenerFactorBalance(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
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





void ArbolAVL::recorridoInorden(NodoAVL* nodo, bool &detenido) {
    if (nodo != nullptr && !detenido) {
        recorridoInorden(nodo->izquierdo, detenido);  

        if (!detenido) {
            std::cout << nodo->distancia << " ";  
            detenido = true;  
        }

        recorridoInorden(nodo->derecho, detenido); 
    }
}
void ArbolAVL::mostrarDistancias() {
    bool detenido = false; 
    recorridoInorden(raiz, detenido);
    std::cout << std::endl;
}



void ArbolAVL::mostrarArbol(sf::RenderWindow &ventana, sf::Font &fuente) {
    NodoAVL* raiz = obtenerRaiz();

    if (raiz != nullptr) {
        float desplazamientoY = 50;  
        dibujarNodo(raiz, ventana, fuente, 400, 50 + desplazamientoY, 150);  
    }
}

void ArbolAVL::dibujarNodo(NodoAVL* nodo, sf::RenderWindow &ventana, sf::Font &fuente, float x, float y, float offset) {
    if (nodo == nullptr) return;

  
    if (nodo->izquierdo != nullptr) {
        sf::VertexArray linea(sf::Lines, 2);
        linea[0].position = sf::Vector2f(x, y);  
        linea[1].position = sf::Vector2f(x - offset, y + 100);  
        linea[0].color = sf::Color::White;
        linea[1].color = sf::Color::White;
        ventana.draw(linea);
    }

    
    if (nodo->derecho != nullptr) {
        sf::VertexArray linea(sf::Lines, 2);
        linea[0].position = sf::Vector2f(x, y);  
        linea[1].position = sf::Vector2f(x + offset, y + 100);  
        linea[0].color = sf::Color::White;
        linea[1].color = sf::Color::White;
        ventana.draw(linea);
    }

   
    sf::CircleShape circulo(30);  
    circulo.setFillColor(sf::Color::Black);  
    circulo.setPosition(x - circulo.getRadius(), y - circulo.getRadius());  
    ventana.draw(circulo);

  
    sf::Text texto(std::to_string(nodo->distancia), fuente, 20);
    texto.setFillColor(sf::Color::White);  
    texto.setPosition(x - texto.getLocalBounds().width / 2, y - texto.getLocalBounds().height / 2);
    ventana.draw(texto);

   
    if (nodo->izquierdo != nullptr) {
        dibujarNodo(nodo->izquierdo, ventana, fuente, x - offset, y + 100, offset / 2);
    }

 
    if (nodo->derecho != nullptr) {
        dibujarNodo(nodo->derecho, ventana, fuente, x + offset, y + 100, offset / 2);
    }
}
NodoAVL* ArbolAVL::obtenerRaiz() {
    return raiz;  
}

void ArbolAVL::vaciarArbol() {
    raiz = nullptr;  
    std::cout << "Árbol AVL vaciado correctamente." << std::endl;
}




bool compararSalida1(int pos1, int pos2) {
    int decimal1 = pos1 / 10;  
    int unidad1 = pos1 % 10;   

    int decimal2 = pos2 / 10;  
    int unidad2 = pos2 % 10;   

    
    if (decimal1 != decimal2) {
        return decimal1 < decimal2;  
    } else {
        
        std::vector<int> orden = {4, 5, 3, 6, 2, 7, 1, 8, 0, 9};
        
        auto it1 = std::find(orden.begin(), orden.end(), unidad1);
        auto it2 = std::find(orden.begin(), orden.end(), unidad2);
        
        return it1 < it2;
    }
}

bool compararSalida2(int pos1, int pos2) {
    int unidad1 = pos1 % 10;
    int decimal1 = pos1 / 10;

    int unidad2 = pos2 % 10;
    int decimal2 = pos2 / 10;

    if (decimal1 != decimal2) {
        return decimal1 > decimal2;  
    } else {
        std::vector<int> orden = {4, 5, 3, 6, 2, 7, 1, 8, 0, 9};
        
        auto it1 = std::find(orden.begin(), orden.end(), unidad1);
        auto it2 = std::find(orden.begin(), orden.end(), unidad2);

       
        if (it1 != orden.end() && it2 != orden.end()) {
            return it1 > it2;  
        }
        return unidad1 > unidad2;  
    }
}
Nodo<Coche>* ArbolAVL::buscarCocheMasCercanoEnLista(ListaCircularDoble<Coche>& listaCoches, int salida) {
    Nodo<Coche>* nodoActual = listaCoches.getPrimero();
    
    if (nodoActual == nullptr) {
        std::cerr << "La lista de coches está vacía." << std::endl;
        return nullptr;
    }

    Nodo<Coche>* cocheMasCercano = nullptr;

    do {
        Coche coche = nodoActual->getDato();
        int posicion = coche.getposicion();

        if (cocheMasCercano == nullptr) {
           
            cocheMasCercano = nodoActual;
        } else {
            int posicionMasCercana = cocheMasCercano->getDato().getposicion();
            bool esMasCercano = (salida == 1) ? compararSalida1(posicion, posicionMasCercana) : compararSalida2(posicion, posicionMasCercana);

            if (esMasCercano) {
                cocheMasCercano = nodoActual;
            }
        }

        nodoActual = nodoActual->getSiguiente(); 
    } while (nodoActual != listaCoches.getPrimero()); 
    
    return cocheMasCercano;
}