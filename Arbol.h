/*
 * Proyecto final TC1032.TC1031 
 * Programación de estructuras de datos y algoritmos fundamentales
 * Profesor: Benjamín Valdés Aguirre.
 * Nombre: Emanuel Josué Vega González.
 * ID: A01710366.
 *
 * Clase AVLResidentes (Estructura de datos principal)  
 */

#ifndef AVLRESIDENTES_H_
#define AVLRESIDENTES_H_

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Residente.h"

using namespace std;

class Node {
private:
    Residente *residente;
    Node *left, *right;
    Node* succesor();

public:
    Node(Residente*);
    Node(Residente*, Node*, Node*);
    void add(Residente*);
	void add(Node*&, Residente*);
    bool find(int);
    void remove(Residente*);
    void removeChilds();
    void inorder(stringstream&) const;
    void inorderSaldo(stringstream&) const;
    void preorder(stringstream&) const;
	void addVector(Node*&, vector<Residente*>&, int, int);
	Node* sortedArrayToBST(vector<Residente*>&);
    friend class BSTResidente;
};

/**
 * Constructor por default
 * 
 * @param *resi Residente
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(1)
 * 
 */
Node::Node(Residente *resi) : residente(resi), left(0), right(0) {}

/**
 * Constructor con parámetros
 * 
 * @param *resi Residente
 * @param *le Nodo izquierdo
 * @param *ri Nodo derecho
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(1)
 * 
 */
Node::Node(Residente *resi, Node *le, Node *ri)
    : residente(resi), left(le), right(ri) {}

/**
 * Método para agregar un residente al árbol
 * 
 * @param *residenteNuevo Residente
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void Node::add(Residente *residenteNuevo) {
    if (residenteNuevo->getNumCasa() < residente->getNumCasa()) {
        if (left != 0) {
            left->add(residenteNuevo);
        } else {
            left = new Node(residenteNuevo);
        }
    } else {
        if (right != 0) {
            right->add(residenteNuevo);
        } else {
            right = new Node(residenteNuevo);
        }
    }
}

/**
 * Método para agregar un residente al árbol
 * 
 * @param *&root Nodo raíz
 * @param *resi Residente
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void Node::add(Node*& root, Residente *resi) {
	 if (root == 0) {
        root = new Node(resi);
    } else if (resi->getNumCasa() < root->residente->getNumCasa()) {
        add(root->left, resi);
    } else {
        add(root->right, resi);
    }
}

/**
 * Método para buscar un residente en el árbol
 * 
 * @param numCasa Número de casa
 * @return bool
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
bool Node::find(int numCasa) {
    if (numCasa == residente->getNumCasa()) {
        return true;
    } else if (numCasa < residente->getNumCasa()) {
        return (left != 0 && left->find(numCasa));
    } else if (numCasa > residente->getNumCasa()) {
        return (right != 0 && right->find(numCasa));
    }
}

/**
 * Método para encontrar el sucesor de un nodo
 * 
 * @param
 * @return Node
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
Node* Node::succesor() {
	Node *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	Node *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

/**
 * Método para eliminar un residente del árbol
 * 
 * @param *residenteBorrar Residente
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void Node::remove(Residente *residenteBorrar) {
	Node *succ, *old;
	if (residenteBorrar->getNumCasa() < residente->getNumCasa()) {
		if (left != 0) {
			if (left->residente->getNumCasa() == residenteBorrar->getNumCasa()) {
				old = left;
				succ = left->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(residenteBorrar);
			}
		}
	} else if (residenteBorrar->getNumCasa() > residente->getNumCasa()) {
		if (right != 0) {
			if (right->residente->getNumCasa() == residenteBorrar->getNumCasa()) {
				old = right;
				succ = right->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(residenteBorrar);
			}
		}
	}
}

/**
 * Método para eliminar los hijos de un nodo
 * 
 * @param
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void Node::removeChilds() {
    if (left != 0) {
        left->removeChilds();
        delete left;
        left = 0;
    }
    if (right != 0) {
        right->removeChilds();
        delete right;
        right = 0;
    }
}

/**
 * Método para recorrer el árbol en orden
 * 
 * @param aux stringstream
 * @return
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
void Node::inorder(stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }

	aux << residente->getNumCasa() << "\t" << residente->getNombre()
             << "\t" << "\t" << residente->getSaldoAPagar() << "\t" 
             << residente->getTamAmenidadesReservadas() << endl;

    if (right != 0) {
        right->inorder(aux);
    }
}

/**
 * Método para recorrer el árbol en orden
 * 
 * @param aux stringstream
 * @return
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
void Node::inorderSaldo(stringstream &aux) const {
    if (left != 0) {
        left->inorderSaldo(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }

    aux << residente->getNumCasa() << "\t" << residente->getNombre()
             << "\t" << "\t" << residente->getSaldoAPagar() << "\t" 
             << residente->getTamAmenidadesReservadas() << endl;

    if (right != 0) {
        right->inorderSaldo(aux);
    }
}

/**
 * Método para recorrer el árbol en preorden
 * 
 * @param aux stringstream
 * @return
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
void Node::preorder(stringstream &aux) const {
    aux << residente->getNumCasa();
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

/**
 * Método para convertir un vector en un árbol
 * 
 * @param residentes vector<Residente*>
 * @return Node
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
Node* Node::sortedArrayToBST(vector<Residente*>& residentes) {
    Node* root = NULL;
    addVector(root, residentes, 0, residentes.size() - 1);
    return root;
}

/**
 * Método para agregar un vector al árbol
 * 
 * @param *&root Nodo raíz
 * @param residentes vector<Residente*>
 * @param start int
 * @param end int
 * @return
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
void Node::addVector(Node*& root, vector<Residente*>& residentes, int start, int end) {
    if (start > end) {
        return;
    }
    int mid = (start + end) / 2;
    add(root, residentes[mid]);
    addVector(root, residentes, start, mid - 1);
    addVector(root, residentes, mid + 1, end);
}


class BSTResidente {
private:
    Node *root;

public:
    BSTResidente();
	BSTResidente(vector<Residente*>);
    ~BSTResidente();
    bool empty() const;
    void add(Residente*);
    bool find(int) const;
    void remove(Residente *);
    void removeAll();
    string inorder() const;
    string preorder() const;
	float deudasResidentes();
	float auxDeudas(Node*, float&);
	Residente* getResidente(int numCasa);
	Residente* buscarResidente(Node *, int);
};

/**
 * Constructor por default
 * 
 * @param
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(1)
 * 
 */
BSTResidente::BSTResidente() : root(0) {}

/**
 * Constructor con parámetros
 * 
 * @param residentes vector<Residente*>
 * @return
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
BSTResidente::BSTResidente(vector<Residente*> residentes) {
	root = root->sortedArrayToBST(residentes);
}

/**
 * Destructor
 * 
 * @param
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(1)
 * 
 */
BSTResidente::~BSTResidente() {
    removeAll();
}

/**
 * Método para verificar si el árbol está vacío
 * 
 * @param
 * @return bool
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(1)
 * 
 */
bool BSTResidente::empty() const {
    return (root == 0);
}

/**
 * Método para agregar un residente al árbol
 * 
 * @param *nuevoResidente Residente
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void BSTResidente::add(Residente *nuevoResidente) {
    if (root != 0) {
		root->add(nuevoResidente);
	} else {
		root = new Node(nuevoResidente);
	}
}

/**
 * Método para eliminar un residente del árbol
 * 
 * @param *residenteDelete Residente
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void BSTResidente::remove(Residente *residenteDelete) {
    if (root != 0) {
        if (residenteDelete->getNumCasa() == root->residente->getNumCasa()) {
            Node *succ = root->succesor();
            if (succ != 0) {
                succ->left = root->left;
                succ->right = root->right;
            }
            delete root;
            root = succ;
        } else {
            root->remove(residenteDelete);
        }
    }
}

/**
 * Método para eliminar todos los residentes del árbol
 * 
 * @param
 * @return
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
void BSTResidente::removeAll() {
    if (root != 0) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

/**
 * Método para buscar un residente en el árbol
 * 
 * @param numCasa Número de casa
 * @return bool
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
bool BSTResidente::find(int numCasa) const {
    if (root != 0) {
        return root->find(numCasa);
    } else {
        return false;
    }
}

/**
 * Método para recorrer el árbol en orden
 * 
 * @param
 * @return string
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
string BSTResidente::inorder() const {
    stringstream aux;
    aux << "";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "";
    return aux.str();
}

/**
 * Método para recorrer el árbol en preorden
 * 
 * @param
 * @return string
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
string BSTResidente::preorder() const {
    stringstream aux;
    aux << "";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "";
    return aux.str();
}

/**
 * Método para calcular la deuda de todos los residentes
 * 
 * @param
 * @return float
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
float BSTResidente::deudasResidentes() {
	float aux = 0;
	return auxDeudas(root, aux);
}

/**
 * Método auxiliar para calcular la deuda de todos los residentes
 * 
 * @param *r Nodo raíz
 * @param &aux float
 * @return float
 * 
 * Complejidad espacial: O(n)
 * Complejidad temporal: O(n)
 * 
 */
float BSTResidente::auxDeudas(Node *r, float &aux) {
	if (r != 0) {
		auxDeudas(r->left, aux);
		aux += r->residente->getSaldoAPagar();
		auxDeudas(r->right, aux);
	}
	return aux;
}

/**
 * Método para obtener un residente del árbol
 * 
 * @param numCasa Número de casa
 * @return Residente
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
Residente* BSTResidente::getResidente(int numCasa) {
	return buscarResidente(root, numCasa);
}

/**
 * Método para buscar un residente en el árbol
 * 
 * @param *r Nodo raíz
 * @param numCasa Número de casa
 * @return Residente
 * 
 * Complejidad espacial: O(1)
 * Complejidad temporal: O(n)
 * 
 */
Residente* BSTResidente::buscarResidente(Node *r, int numCasa) {
	if (r != 0) {
		if (r->residente->getNumCasa() == numCasa) {
			return r->residente;
		} else if (numCasa < r->residente->getNumCasa()) {
			return buscarResidente(r->left, numCasa);
		} else if (numCasa > r->residente->getNumCasa()) {
			return buscarResidente(r->right, numCasa);
		}
	}
}

#endif