#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

private:
    BSTree<TableEntry<V>>* tree;

public:

    // -----------------------------
    // Constructor
    // -----------------------------
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // -----------------------------
    // Destructor
    // -----------------------------
    ~BSTreeDict() {
        delete tree;
    }

    // -----------------------------
    // Devuelve nº de elementos
    // -----------------------------
    int entries() override {
        return tree->size();
    }

    // -----------------------------
    // Inserción en el diccionario
    // -----------------------------
    void insert(std::string key, V value) override {
        TableEntry<V> e(key, value);
        tree->insert(e);
    }

    // -----------------------------
    // Búsqueda por clave
    // -----------------------------
    V search(std::string key) override {
        TableEntry<V> temp(key);
        TableEntry<V> found = tree->search(temp);
        return found.value;
    }

    // -----------------------------
    // Eliminación por clave
    // Devuelve el valor eliminado
    // -----------------------------
    V remove(std::string key) override {
        TableEntry<V> temp(key);
        TableEntry<V> found = tree->search(temp);  // para obtener el value
        tree->remove(temp);
        return found.value;
    }

    // -----------------------------
    // Sobrecarga operador []
    // Equivalente a search()
    // -----------------------------
    V operator[](std::string key) {
        return search(key);
    }

    // -----------------------------
    // Operador << para imprimir
    // -----------------------------
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V>& bs) {
        out << *(bs.tree);
        return out;
    }
};

#endif
