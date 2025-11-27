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

	int nEntries;
 	int nBuckets;

   	 int hash(std::string key) const {
        unsigned long h = 0;
        for (char c : key) h = h * 37 + c;
        return h % nBuckets;
   	}

    public:

        // Constructor
        HashTable(int size, int buckets=3)  : nEntries(0), nBuckets(buckets) {
            maxElems = size;
            nElems = 0;

            table = new ListLinked<TableEntry<V>>[maxElems];
        }

        // Destructor
        ~HashTable() {
            delete[] table;
        }

	 int capacity() const {
            return nBuckets;
        }

	int entries() const {
        return nEntries;
   	}

        // Inserción: Si existe la clave → sobrescribe valor
        void insert(std::string key, V value) override {
            int idx = h(key);
            TableEntry<V> temp(key);

	    int pos = table[idx].search(temp);

            // Si ya existe la clave, lanzamos excepción
   	 if (pos != -1) {
        	throw std::runtime_error("Key '" + key + "' already exists!");
   	 }

            // Si no existe, insertar al principio
            table[idx].prepend(TableEntry<V>(key, value));
            nEntries++;
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
            nEntries--;
            return val;
        }

	// Devuelve número de elementos en la tabla
        int entries() override {
            return nElems;
        }

        // Sobrecarga de operador []
        V operator[](std::string key) {
            return search(key);
        }

	// Para imprimir la tabla
        friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {

        out << "HashTable [entries: " << ht.nEntries
            << ", capacity: " << ht.nBuckets << "]\n";
        out << "==============\n\n";

        for (int i = 0; i < ht.nBuckets; i++) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => [";

            if (ht.table[i].size() == 0) {
                out << "]\n\n";
                continue;
            }

            out << "\n";

            for (int j = 0; j < ht.table[i].size(); j++) {
                auto e = ht.table[i].get(j);

                out << "  ('" << e.key << "' => " << e.value << ")";
                if (j + 1 < ht.table[i].size()) out << "\n";
                else out << "\n";
            }

            out << "]\n\n";
        }

        out << "==============\n\n";

        return out;
    }



};

#endif 
