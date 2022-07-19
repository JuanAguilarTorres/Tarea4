#ifndef excepcionAgregarDuplicado_H
#define excepcionAgregarDuplicado_H

#include <exception>

class excepcionAgregarDuplicado : public std::exception
{
    public:
    excepcionAgregarDuplicado() noexcept = default;
    ~excepcionAgregarDuplicado() = default;

    virtual const char* what() const noexcept {
        return "No se puede añadir porque el id está duplicado";
    }

};

#endif
