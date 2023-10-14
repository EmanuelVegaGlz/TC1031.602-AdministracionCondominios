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
#include "Residente.h"

using namespace std;

	class Node {
	private:
		Residente *value;
		Node *left, *right;
		int level, balance;
		Node* predecesor();

	public:
		Node(Residente *val):
			value(val), left(0), right(0), level(0), balance(0) {}

		Node* add(Residente *val);
		bool find(int);
		void remove(int);
		void removeChilds();
		void inorderImprimirPorCasa(stringstream&) const;
		void inorderImprimirPorSaldo(stringstream&) const;
		void preorder(stringstream&) const;
		int max_depth();
		Node* check_tree(Residente*, Node*, bool*);
		Node* balance_tree();
		Node* rot_left(Node* );
		Node* rot_right(Node* );
		Node* rot_left_right(Node* );
		Node* rot_right_left(Node* );
		friend class AVLResidente;
	};

Node* Node::add(Residente *val) {
    if (val->getNumCasa() < value->getNumCasa()) {
        if (left != 0) {
            left->add(val);
        } else {
            left = new Node(val);
        }
    } else {
        if (right != 0) {
            right->add(val);
        } else {
            right = new Node(val);
        }
    }
}

bool Node::find(int numCasa) {
    if (numCasa == value->getNumCasa()) {
        return true;
    } else if (numCasa < value->getNumCasa()) {
        return (left != 0 && left->find(numCasa));
    } else if (numCasa > value->getNumCasa()) {
        return (right != 0 && right->find(numCasa));
    }
    return false;
}

Node* Node::predecesor() {
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

void Node::remove(int numCasa) {
	Node * succ, *old;

	if (numCasa < value->getNumCasa()) {
		if (left != 0) {
			if (left->value->getNumCasa() == numCasa) {
				old = left;
				succ = left->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(numCasa);
			}
		}
	} else if (numCasa > value->getNumCasa()) {
		if (right != 0) {
			if (right->value->getNumCasa() == numCasa) {
				old = right;
				succ = right->predecesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(numCasa);
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

void Node::inorderImprimirPorCasa(std::stringstream &aux) const {
    if (left != 0) {
        left->inorderImprimirPorCasa(aux);
    }
    if (aux.tellp() != 1) {
        aux << "\n";
    }
    aux << value->getNumCasa() << "\t" << value->getNombre()
             << "\t" << "\t" << value->getSaldoAPagar() << "\t" 
             << value->getTamAmenidadesReservadas() << endl;
    if (right != 0) {
        right->inorderImprimirPorCasa(aux);
    }
}

void Node::inorderImprimirPorSaldo(std::stringstream &aux) const {
    if (left != 0) {
        left->inorderImprimirPorSaldo(aux);
    }
    if (aux.tellp() != 1) {
        aux << "\n";
    }
    aux << value->getNumCasa() << "\t" << value->getNombre()
             << "\t" << "\t" << value->getSaldoAPagar() << "\t" 
             << value->getTamAmenidadesReservadas() << endl;
    if (right != 0) {
        right->inorderImprimirPorSaldo(aux);
    }
}

void Node::preorder(stringstream &aux) const {
	aux << "(" << value << " " << level << " " << balance << ")";
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

int Node::max_depth() {
	int le =0 , ri = 0;
	if (left != 0)
		le = left->max_depth() + 1;
	if (right != 0)
		ri = right->max_depth() + 1;
	if(le > ri)
		level = le;
	else
		level = ri;
	balance = le - ri;
	return level;
}

Node* Node::check_tree(Residente* check, Node* parent, bool* checked) {
    if (*checked) {
        return 0;
    }

    Node *a = 0;
    if (balance > 1) {
        a = balance_tree();
        *checked = true;

        if (parent != 0) {
            if (parent->left == this) {
                parent->left = a;
            } else if (parent->right == this) {
                parent->right = a;
            }
        }
    } else if (balance < -1) {
        a = balance_tree();
        *checked = true;

        if (parent != 0) {
            if (parent->left == this) {
                parent->left = a;
            } else if (parent->right == this) {
                parent->right = a;
            }
        }
    }

    if (*checked) {
        check = value;
    }

    return a;
}

Node* Node::balance_tree() {
	Node *a = this, *le =left, *ri =right;
	Residente* old_value = value;
	cout<< "Balancing node : " << a->value << " " << endl;
	if (balance > 0) {
		if (le->balance > 0){
			cout<< "rot_right  " << a->balance << " left: " << le->balance << endl;
			a = rot_right(a);
		}else{
			cout<< "rot_left_right " << a->balance << " left: " << le->balance << endl;
			a = rot_left_right(a);
		}
	}else{
		if (ri->balance < 0){
			cout<< "rot_left " << a->balance << " right: " << ri->balance << endl;
			a = rot_left(a);
		}else{
			cout<< "rot_right_left " << a->balance << " right: " << ri->balance << endl;
			a = rot_right_left(a);
		}
	}
	cout<< "New current node value is " << a->value << endl;
	return a;
}

Node* Node::rot_left(Node* a){
	Node *b, *temp = 0;
	if (a->right != 0){
		b = a->right;
		if (b->left != 0)
			temp = b->left;
		b->left = a;
		if(temp != 0){
			a->right = temp;
		}else{
			a->right = 0;
		}
	}
	return b;
}

Node* Node::rot_right(Node* a){
	Node *b, *temp = 0;
	if (a->left != 0){
		b = a->left;
		if (b->right != 0)
			temp = b->right;
		b->right = a;
		if(temp != 0){
			a->left = temp;
		}else{
			a->left = 0;
		}
	}
	return b;
}

Node* Node::rot_left_right(Node* a){
	a->left = rot_left(a->left);
	a = rot_right(a);
	return a;
}

Node*  Node::rot_right_left(Node* a){
	a->right = rot_right(a->right);
	a = rot_left(a);
	return a;
}

class AVLResidente {
private:
	Node *root;

public:
	AVLResidente();
    AVLResidente(vector<Residente*> vec);
	~AVLResidente();
	bool empty() const;
    void add(Residente*);
	bool find(int) const;
	void remove(int);
	void removeAll();
	string inorderPorCasa() const;
    string inorderPorSaldo() const;
	string preorder() const;
    void recorrerYSumarSaldos(Node* current, float &totalDeudas);
	float calcularDeuda();
	Residente* getResidente(int numCasa);
	void avlReservarAmenidad(int numCasa, string amenidad);
	friend class Residente;
    friend class Node;
};

AVLResidente::AVLResidente() : root(0) {}

AVLResidente::AVLResidente(vector<Residente*> vec) {
    root = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (root != 0) {
            root = root->add(vec[i]);
        } else {
            root = new Node(vec[i]);
        }
    }
}

 

AVLResidente::~AVLResidente() {
	removeAll();
}

bool AVLResidente::empty() const {
	return (root == 0);
}


void AVLResidente::add(Residente* val) {
    if (root != 0) {
        root = root->add(val);
    } else {
        root = new Node(val);
    }
}

void AVLResidente::remove(int numCasa) {
    if (root != 0) {
        if (root->find(numCasa)) {
            root->remove(numCasa);
        }
    }
}

void AVLResidente::removeAll() {
    if (root != 0) {
        root->removeChilds();
    }
    delete root;
    root = 0;
}

bool AVLResidente::find(int numCasa) const {
	if (root != 0) {
		return root->find(numCasa);
	} else {
		return false;
	}
}

string AVLResidente::inorderPorCasa() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorderImprimirPorCasa(aux);
	}
	aux << "]";
	return aux.str();
}

std::string AVLResidente::inorderPorSaldo() const {
    std::stringstream result;
    if (root != 0) {
        root->inorderImprimirPorSaldo(result);
    }
    return result.str();
}

string AVLResidente::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

void AVLResidente::recorrerYSumarSaldos(Node* current, float& totalDeudas) {
    if (current == nullptr) {
        return;
    }

    // Recorre primero el subárbol izquierdo
    recorrerYSumarSaldos(current->left, totalDeudas);

    // Luego, verifica si el saldo del residente es positivo y suma al total
    if (current->value->getSaldoAPagar() > 0) {
        totalDeudas += current->value->getSaldoAPagar();
    }

    // Finalmente, recorre el subárbol derecho
    recorrerYSumarSaldos(current->right, totalDeudas);
}

float AVLResidente::calcularDeuda() {
    float totalDeudas = 0;
    recorrerYSumarSaldos(root, totalDeudas);
    return totalDeudas;
}

Residente* AVLResidente::getResidente(int numCasa) {
	if (root != 0) {
		if (root->find(numCasa)) {
			return root->value;
		}
	}
	return 0;
}


#endif