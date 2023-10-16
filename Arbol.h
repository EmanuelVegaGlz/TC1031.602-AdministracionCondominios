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

Node::Node(Residente *resi) : residente(resi), left(0), right(0) {}

Node::Node(Residente *resi, Node *le, Node *ri)
    : residente(resi), left(le), right(ri) {}

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

void Node::add(Node*& root, Residente *resi) {
	 if (root == 0) {
        root = new Node(resi);
    } else if (resi->getNumCasa() < root->residente->getNumCasa()) {
        add(root->left, resi);
    } else {
        add(root->right, resi);
    }
}

bool Node::find(int numCasa) {
    if (numCasa == residente->getNumCasa()) {
        return true;
    } else if (numCasa < residente->getNumCasa()) {
        return (left != 0 && left->find(numCasa));
    } else if (numCasa > residente->getNumCasa()) {
        return (right != 0 && right->find(numCasa));
    }
}

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

Node* Node::sortedArrayToBST(vector<Residente*>& residentes) {
    Node* root = NULL;
    addVector(root, residentes, 0, residentes.size() - 1);
    return root;
}

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

BSTResidente::BSTResidente() : root(0) {}

BSTResidente::BSTResidente(vector<Residente*> residentes) {
	root = root->sortedArrayToBST(residentes);
}

BSTResidente::~BSTResidente() {
    removeAll();
}


bool BSTResidente::empty() const {
    return (root == 0);
}

void BSTResidente::add(Residente *nuevoResidente) {
    if (root != 0) {
		root->add(nuevoResidente);
	} else {
		root = new Node(nuevoResidente);
	}
}

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

void BSTResidente::removeAll() {
    if (root != 0) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

bool BSTResidente::find(int numCasa) const {
    if (root != 0) {
        return root->find(numCasa);
    } else {
        return false;
    }
}

string BSTResidente::inorder() const {
    stringstream aux;
    aux << "";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "";
    return aux.str();
}

string BSTResidente::preorder() const {
    stringstream aux;
    aux << "";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "";
    return aux.str();
}

float BSTResidente::deudasResidentes() {
	float aux = 0;
	return auxDeudas(root, aux);
}

float BSTResidente::auxDeudas(Node *r, float &aux) {
	if (r != 0) {
		auxDeudas(r->left, aux);
		aux += r->residente->getSaldoAPagar();
		auxDeudas(r->right, aux);
	}
	return aux;
}

Residente* BSTResidente::getResidente(int numCasa) {
	return buscarResidente(root, numCasa);
}

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