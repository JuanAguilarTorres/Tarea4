#ifndef excepcionEliminarIncorrecto_H
#define excepcionEliminarIncorrecto_H

#include <exception>

class excepcionEliminarIncorrecto : public std::exception
{
    public:
    excepcionEliminarIncorrecto() noexcept = default;
    ~excepcionEliminarIncorrecto() = default;

    virtual const char* what() const noexcept {
        return "No se puede eliminar el id proporcionado";
    }

};

#endif
