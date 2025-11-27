#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
    public:
        // Inserta un par (key, value)
        virtual void insert(std::string key, V value) = 0;

        // Busca el valor asociado a una clave.
        // Si no existe, debe lanzar std::runtime_error
        virtual V search(std::string key) = 0;

        // Elimina una entrada por clave y devuelve su valor.
        // Si no existe, debe lanzar std::runtime_error
        virtual V remove(std::string key) = 0;

        // Devuelve cuántos elementos contiene la tabla
        virtual int entries() = 0;

        // Destructor virtual
        virtual ~Dict() = default;
};

#endif

