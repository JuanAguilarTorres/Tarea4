#ifndef TIENDA_H
#define TIENDA_H

#include "producto.h"
#include <vector>
#include <iostream>


using namespace std;

class Tienda {

    char nombre[15];         //15
    char sitioWeb[24];       //24
    char localizacion[24];   //24
    char telefono[8];        //8
    vector<Producto *> productos;

    public:
    Tienda(string nombre, string sitioWeb, string localizacion, string telefono);
    Tienda();
    ~Tienda();

    void agregarProducto(Producto *nuevoProducto);
    void agregarProducto(int id, string nombre, int existencias);

    void eliminarProducto(int id);

    void editarProducto(int id, string nombre, int existencias);

    string tiendaAString();

    vector<Producto *> consultarProductos();

    void GuardarEnStreamBinario(ostream *streamSalida);
    void CargarDesdeStreamBinario(istream *streamEntrada);

    friend ostream& operator << (ostream &o, const Tienda *Tienda);
};

#endif