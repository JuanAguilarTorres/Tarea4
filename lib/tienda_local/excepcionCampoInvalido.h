#ifndef excepcionCampoInvalido_H
#define excepcionCampoInvalido_H

#include <exception>

class excepcionCampoInvalido : public std::exception
{
    public:
    excepcionCampoInvalido() noexcept = default;
    ~excepcionCampoInvalido() = default;

    virtual const char* what() const noexcept {
        return "No se pueden usar los parámetros proporcionados";
    }

};

#endif
