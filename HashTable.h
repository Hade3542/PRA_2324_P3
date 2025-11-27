#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"


#include "../PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

    private:
        ListLinked<TableEntry<V>>* table;   // Array de listas
        int maxElems;                       // Tamaño máximo de la tabla
        int nElems;                         // Número de elementos almacenados

        // Función hash pedida por la práctica:
        // suma de códigos ASCII de los caracteres % maxElems
        int h(std::string key) {
            int sum = 0;
            for (char c : key) {
                sum += int(c);
            }
            return sum % maxElems;
        }

    public:

        // Constructor
        HashTable(int size) {
            maxElems = size;
            nElems = 0;

            table = new ListLinked<TableEntry<V>>[maxElems];
        }

        // Destructor
        ~HashTable() {
            delete[] table;
        }

        // Inserción: Si existe la clave → sobrescribe valor
        void insert(std::string key, V value) override {
            int idx = h(key);
            TableEntry<V> temp(key);

            // Si ya existe, se reemplaza el valor
            if (table[idx].search(temp) != -1) {
                int pos = table[idx].search(temp);
                table[idx].update(pos, TableEntry<V>(key, value));
                return;
            }

            // Si no existe, insertar al principio
            table[idx].prepend(TableEntry<V>(key, value));
            nElems++;
        }

        // Search debe lanzar runtime_error si no existe
        V search(std::string key) override {
            int idx = h(key);
            TableEntry<V> temp(key);

            int pos = table[idx].search(temp);
            if (pos == -1)
                throw std::runtime_error("Clave no encontrada: " + key);

            return table[idx].get(pos).value;
        }

        // Remove debe devolver el valor eliminado
        V remove(std::string key) override {
            int idx = h(key);
            TableEntry<V> temp(key);

            int pos = table[idx].search(temp);
            if (pos == -1)
                throw std::runtime_error("Clave no encontrada: " + key);

            V val = table[idx].get(pos).value;
            table[idx].remove(pos);
            nElems--;
            return val;
        }

        // Devuelve número de elementos en la tabla
        int entries() override {
            return nElems;
        }

        // Para imprimir la tabla (opcional pero útil)
        friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
            for (int i = 0; i < ht.maxElems; i++) {
                out << "Cubeta " << i << ": " << ht.table[i] << "\n";
            }
            return out;
        }

};

#endif

