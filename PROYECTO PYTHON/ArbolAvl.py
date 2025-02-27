import pygame
from NodoAvl import NodoAvl

class ArbolAvl:
    def __init__(self):
        self.raiz = None

    def agregar_distancia(self, distancia):
        self.raiz = self.insertar(self.raiz, distancia)

    def insertar(self, nodo, distancia):
        if nodo is None:
            return NodoAvl(distancia)
        
        if distancia < nodo.distancia:
            nodo.izquierdo = self.insertar(nodo.izquierdo, distancia)
        elif distancia > nodo.distancia:
            nodo.derecho = self.insertar(nodo.derecho, distancia)
        else:
            return nodo

        nodo.altura = 1 + max(self.obtener_altura(nodo.izquierdo), self.obtener_altura(nodo.derecho))

        balance = self.obtener_factor_balance(nodo)
        
        if balance > 1 and distancia < nodo.izquierdo.distancia:
            return self.rotar_derecha(nodo)
        if balance < -1 and distancia > nodo.derecho.distancia:
            return self.rotar_izquierda(nodo)
        if balance > 1 and distancia > nodo.izquierdo.distancia:
            nodo.izquierdo = self.rotar_izquierda(nodo.izquierdo)
            return self.rotar_derecha(nodo)
        if balance < -1 and distancia < nodo.derecho.distancia:
            nodo.derecho = self.rotar_derecha(nodo.derecho)
            return self.rotar_izquierda(nodo)

        return nodo

    def obtener_altura(self, nodo):
        if nodo is None:
            return 0
        return nodo.altura

    def obtener_factor_balance(self, nodo):
        if nodo is None:
            return 0
        return self.obtener_altura(nodo.izquierdo) - self.obtener_altura(nodo.derecho)

    def rotar_derecha(self, y):
        x = y.izquierdo
        T2 = x.derecho
        x.derecho = y
        y.izquierdo = T2
        y.altura = 1 + max(self.obtener_altura(y.izquierdo), self.obtener_altura(y.derecho))
        x.altura = 1 + max(self.obtener_altura(x.izquierdo), self.obtener_altura(x.derecho))
        return x

    def rotar_izquierda(self, x):
        y = x.derecho
        T2 = y.izquierdo
        y.izquierdo = x
        x.derecho = T2
        x.altura = 1 + max(self.obtener_altura(x.izquierdo), self.obtener_altura(x.derecho))
        y.altura = 1 + max(self.obtener_altura(y.izquierdo), self.obtener_altura(y.derecho))
        return y

    def mostrar_arbol(self, pantalla, fuente):
        if self.raiz:
            self.dibujar_nodo(self.raiz, pantalla, fuente, 400, 50, 150)

    def dibujar_nodo(self, nodo, pantalla, fuente, x, y, offset):
        if nodo is None:
            return

        if nodo.izquierdo:
            pygame.draw.line(pantalla, (255, 255, 255), (x, y), (x - offset, y + 100), 2)

        if nodo.derecho:
            pygame.draw.line(pantalla, (255, 255, 255), (x, y), (x + offset, y + 100), 2)

        pygame.draw.circle(pantalla, (0, 0, 0), (x, y), 30)
        texto = fuente.render(str(nodo.distancia), True, (255, 255, 255))
        pantalla.blit(texto, (x - texto.get_width() // 2, y - texto.get_height() // 2))

        if nodo.izquierdo:
            self.dibujar_nodo(nodo.izquierdo, pantalla, fuente, x - offset, y + 100, offset / 2)

        if nodo.derecho:
            self.dibujar_nodo(nodo.derecho, pantalla, fuente, x + offset, y + 100, offset / 2)

    def vaciar_arbol(self):
        """
        Vacía el árbol, eliminando todos sus nodos.
        """
        self.raiz = None  # Establecer la raíz como None vacía el árbol
        print("Árbol AVL vaciado correctamente.")