#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>

using namespace std;

class Producto {

    int id; // 4
    char nombre[20]; // 20
    int existencia; // 4
    

    public:
    Producto(int id, string nombre, int existencia);
    Producto();
    int obtenerId();
    string obtenerString();

    friend ostream& operator << (ostream &o, const Producto *empleado);
};

#endif