#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;
    BSNode<T>* root;

    // Métodos privados
    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr){
            throw std::runtime_error("Element not found");
	}
        if (e < n->elem){ 
		return search(n->left, e);
	}
        else if (e > n->elem){
	       	return search(n->right, e);
	}
        else{
	       	return n;
	}
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr){
	       	return new BSNode<T>(e);
	}
        if (e == n->elem){
	       	throw std::runtime_error("Duplicated element");
	}
        if (e < n->elem){
	       	n->left = insert(n->left, e);
	}
        else{
	       	n->right = insert(n->right, e);
	}
	return n;
    }

    void print_inorder(std::ostream &out, BSNode<T>* n) const {
        if (!n){
	       	return;
	}
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (!n){
	       	throw std::runtime_error("Element not found");
	}
        if (e < n->elem){
	       	n->left = remove(n->left, e);
	}
        else if (e > n->elem){
	       	n->right = remove(n->right, e);
	}
        else if	(n->left && n->right){ 
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } 
	else {
                BSNode<T>* temp = (n->left) ? n->left : n->right;
                delete n;
                return temp;
            }
        return n;
    }

    T max(BSNode<T>* n) const {
        if (n->right) {
		return max(n->right);
	}
        return n->elem;
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (!n->right) {
            BSNode<T>* leftChild = n->left;
            delete n;
            return leftChild;
        }
        n->right = remove_max(n->right);
        return n;
    }

    void delete_cascade(BSNode<T>* n) {
        if (!n){
	       	return;
	}
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }

public:
    BSTree(){
    	nelem = 0;
	root = nullptr;
    }
    ~BSTree() {
	    delete_cascade(root);
    }

    int size() const { 
	    return nelem;
    }

    T search(T e) const { 
	    return search(root, e)->elem;
    }

    T operator[](T e) const { 
	    return search(e);
    }

    void insert(T e) { 
	    root = insert(root, e); 
	    nelem++;
    }

    void remove(T e) { 
	    root = remove(root, e); 
	    nelem--;
    }

    friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif
