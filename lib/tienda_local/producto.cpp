#include "producto.h"
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

Producto::Producto(int id, string nombre, int existencia)
{
    this->id = id;
    strcpy(this->nombre, nombre.c_str());
    this->existencia = existencia;
}

Producto::Producto()
{
    this->id = 0;
    strcpy(this->nombre, "");
    this->existencia = 0;
}

int Producto::obtenerId()
{
    return this->id;
}

string Producto::obtenerString()
{
    string consulta = "";
    std::stringstream consultaStream;
    consultaStream << this->id << " " << this->nombre << " " << this->existencia << " ";
    consulta = consultaStream.str();
    return consulta;
}

ostream& operator << (ostream &o, const Producto *empleado)
{
    o << "[" << empleado->id << "] - " << empleado->nombre << ", Cantidad: " << empleado->existencia;
    return o;
}
