#include "ArbolAVL.h"
#include <iostream>


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


void ArbolAVL::imprimirPrimerTermino(const std::string &salida) {
    bool detenido = false; 
    if (salida == "1") {
        recorridoInorden(raiz, detenido);  
    }
    std::cout << std::endl;  
}

void ArbolAVL::imprimirUltimoTermino(const std::string &salida) {
    bool detenido = false;  
    NodoAVL* ultimo = nullptr;
    recorridoInordenUltimo(raiz, ultimo);  // Recorrido para obtener el último nodo
    if (ultimo != nullptr) {
        std::cout << ultimo->distancia << std::endl;  // Imprime el último término
    }
}

void ArbolAVL::recorridoInordenUltimo(NodoAVL* nodo, NodoAVL* &ultimo) {
    if (nodo != nullptr) {
        // Recorre el subárbol izquierdo
        recorridoInordenUltimo(nodo->izquierdo, ultimo);

        // Actualiza el último nodo encontrado
        ultimo = nodo;

        // Recorre el subárbol derecho
        recorridoInordenUltimo(nodo->derecho, ultimo);
    }
}