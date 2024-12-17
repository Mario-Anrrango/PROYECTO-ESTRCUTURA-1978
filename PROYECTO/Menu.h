#pragma once
#include <iostream>
#include <vector>
#include "Lista.h"


using namespace std;

void menu(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);
int menuInteractivo(const vector<string> &opciones, const string &titulo = "Menu Interactivo");
void menuBusquedaAvanzada(ListaCircularDoble<Coche> &lista, ListaCircularDoble<Coche> &listaHistorial);
