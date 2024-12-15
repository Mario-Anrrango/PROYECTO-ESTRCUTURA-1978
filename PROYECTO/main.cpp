#include <iostream>
#include "Coche.h"
#include "Lista.h"

int main()
{
    

    ListaCircularDoble<Coche> listaCochesHistorial;
    std::string nombreArchivoHistorial = "autos_historial.txt";
    listaCochesHistorial.CargarArchivo("autos_historial.txt");

    ListaCircularDoble<Coche> listaCoches;
    std::string nombreArchivo = "autos.txt";

    listaCoches.CargarArchivo("autos.txt");
    Coche coche;

    coche.menu(listaCoches,listaCochesHistorial);

    return 0;
}