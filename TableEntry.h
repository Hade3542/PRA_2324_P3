#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
        std::string key;
        V value;

        // Constructor (key, valor)
        TableEntry(std::string k, V v) : key(k), value(v) {}

        // Constructor solo con clave (valor por defecto)
        TableEntry(std::string k) : key(k), value() {}

        // Constructor por defecto (clave vacía)
        TableEntry() : key(""), value() {}

        // Igualdad basada SOLO en la clave
        friend bool operator==(const TableEntry<V>& a, const TableEntry<V>& b) {
            return a.key == b.key;
        }

        friend bool operator!=(const TableEntry<V>& a, const TableEntry<V>& b) {
            return !(a == b);
        }

        // Para imprimir la entrada
        friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& e) {
            out << "(" << e.key << ", " << e.value << ")";
            return out;
        }
};

#endif
