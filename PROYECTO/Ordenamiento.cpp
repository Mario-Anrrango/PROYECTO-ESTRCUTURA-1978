#include <iostream>
#include <vector>
#include <algorithm>
#include "Coche.h"
#include <functional>

template <typename T, typename Comparator>
int partition(std::vector<T>& lista, int low, int high, Comparator comp) {
    T pivot = lista[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (comp(lista[j], pivot)) {
            i++;
            std::swap(lista[i], lista[j]);
        }
    }
    std::swap(lista[i + 1], lista[high]);
    return i + 1;
}

template <typename T, typename Comparator>
void quickSort(std::vector<T>& lista, int low, int high, Comparator comp) {
    if (low < high) {
        int pi = partition(lista, low, high, comp);
        quickSort(lista, low, pi - 1, comp);
        quickSort(lista, pi + 1, high, comp);
    }
}

template <typename T, typename Comparator>
void bubbleSortPass(std::vector<T>& lista, Comparator comp, int n) {

    if (n <= 1) return;

    for (int j = 0; j < n - 1; j++) {
        if (!comp(lista[j], lista[j + 1])) {
            std::swap(lista[j], lista[j + 1]);
        }
    }
}

template <typename T, typename Comparator>
void bubbleSortRecursive(std::vector<T>& lista, Comparator comp, int n) {

    if (n <= 1) return;
  
    bubbleSortPass(lista, comp, n);
    
    bubbleSortRecursive(lista, comp, n - 1);
}


template <typename T, typename Comparator>
void bubbleSort(std::vector<T>& lista, Comparator comp) {
    bubbleSortRecursive(lista, comp, lista.size());
}

template <typename T, typename Comparator>
void ordenarLista(ListaCircularDoble<T>& lista, Comparator comp) {
    std::vector<T> elementos;
    
    Nodo<T>* aux = lista.getPrimero();
    do {   
        elementos.push_back(aux->getDato());
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    quickSort(elementos, 0, elementos.size() - 1, comp);

    aux = lista.getPrimero();
    int index = 0;
    do {
        aux->setDato(elementos[index++]);
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    lista.mostrar(lista.getPrimero());
}

template <typename T, typename Comparator>
void ordenarListaBubbleSort(ListaCircularDoble<T>& lista,Comparator comp){
    std::vector<T> elementos;

    Nodo<T>* aux = lista.getPrimero();
    do{                    
        elementos.push_back(aux->getDato());
        aux= aux->getSiguiente();
    }while (aux != lista.getPrimero());

    bubbleSort(elementos,comp);

    aux=lista.getPrimero();
    int index=0;
    do{
        aux->setDato(elementos[index++]);
        aux=aux->getSiguiente();
    }while (aux != lista.getPrimero());

    lista.mostrar(lista.getPrimero());
}

template <typename T>
void ordenarListaBucket(ListaCircularDoble<T>& lista, std::function<std::string(const T&)> getKey) {
    std::vector<T> elementos;

    
    Nodo<T>* aux = lista.getPrimero();
    if (aux == nullptr) {
        std::cout << "La lista estÃ¡ vacÃ­a." << std::endl;
        return;
    }

    do {
        elementos.push_back(aux->getDato());
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

    
    const int bucketCount = 256; 
    std::vector<std::vector<T>> buckets(bucketCount);


    for (const auto& item : elementos) {
        std::string key = getKey(item);
        if (!key.empty()) {
            char firstChar = tolower(key[0]); 
            int bucketIndex = static_cast<int>(firstChar);
            buckets[bucketIndex].push_back(item);
        }
    }

    
    elementos.clear();


    for (auto& bucket : buckets) {
        std::sort(bucket.begin(), bucket.end(), [&getKey](const T& a, const T& b) {
            return getKey(a) < getKey(b); 
        });
        elementos.insert(elementos.end(), bucket.begin(), bucket.end());
    }

   
    aux = lista.getPrimero();
    int index = 0;
    do {
        aux->setDato(elementos[index++]);
        aux = aux->getSiguiente();
    } while (aux != lista.getPrimero());

   
    lista.mostrar(lista.getPrimero());
}

template <typename T, typename Comparator>
void ordenarListaShellSort(ListaCircularDoble<T>& lista, Comparator comp) {
   
    auto contarElementos = [&]() -> int {
        int n = 0;
        Nodo<T>* aux = lista.getPrimero();
        if (aux != nullptr) {
            do {
                ++n;
                aux = aux->getSiguiente();
            } while (aux != lista.getPrimero());
        }
        return n;
    };

  
    auto copiarListaAArreglo = [&](T* elementos, int n) {
        Nodo<T>* aux = lista.getPrimero();
        for (int i = 0; i < n; ++i) {
            elementos[i] = aux->getDato();
            aux = aux->getSiguiente();
        }
    };

   
    auto copiarArregloALista = [&](T* elementos, int n) {
        Nodo<T>* aux = lista.getPrimero();
        for (int i = 0; i < n; ++i) {
            aux->setDato(elementos[i]);
            aux = aux->getSiguiente();
        }
    };

  
    auto shellSort = [&](T* elementos, int n) {
        int gap = n / 2;
        while (gap > 0) {
            for (int i = gap; i < n; ++i) {
                T temp = elementos[i];
                int j = i;
                while (j >= gap && comp(temp, elementos[j - gap])) {
                    elementos[j] = elementos[j - gap];
                    j -= gap;
                }
                elementos[j] = temp;
            }
            gap /= 2;
        }
    };

    // Contar elementos
    int n = contarElementos();

    // Crear un arreglo dinÃ¡mico y copiar elementos
    T* elementos = new T[n];
    copiarListaAArreglo(elementos, n);

    // Ordenar usando ShellSort
    shellSort(elementos, n);

    // Copiar elementos ordenados de vuelta a la lista
    copiarArregloALista(elementos, n);

    // Liberar memoria dinÃ¡mica
    delete[] elementos;

    // Mostrar lista ordenada
    lista.mostrar(lista.getPrimero());
}
