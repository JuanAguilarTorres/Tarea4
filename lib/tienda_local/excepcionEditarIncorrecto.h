#ifndef excepcionEditarIncorrecto_H
#define excepcionEditarIncorrecto_H

#include <exception>

class excepcionEditarIncorrecto  : public std::exception
{
    public:
    excepcionEditarIncorrecto () noexcept = default;
    ~excepcionEditarIncorrecto () = default;

    virtual const char* what() const noexcept {
        return "No se puede editar el id proporcionado";
    }

};

#endif
