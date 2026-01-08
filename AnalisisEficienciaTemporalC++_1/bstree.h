//
//  bstree.h
//

#ifndef bstree_h
#define bstree_h

#include <iostream>

// Nodos del arbol:
template <typename T>
class bstnode
{
public:
    // Esta clase es usada por otras clases. Para mayor eficiencia, los atributos se hacen publicos.
    T key;
    bstnode<T> *p, *left, *right;
    
    // Constructor por omision
    bstnode() {
    };
    
    // Inicializacion de datos miembro
    bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr, bstnode<T> *z = nullptr):key(k), p(w), left(y), right(z) {};
    
    ~bstnode() {
    };
};

// Arbol de busqueda binario:
template <typename T>
class bstree
{
public:
    bstnode<T> *root;    // raiz del arbol

    bstree() 
        : root(nullptr) {
        // Constructor (crea un arbol vacio)
    };
    
    ~bstree() {
        // Destructor (borra el arbol)
        removeTree(root);
    };
    
    void Insert(bstnode<T>* z) {
        // Inserta el nodo z en la posicion que le corresponde en el arbol.
        bstnode<T>* y = nullptr;
        bstnode<T>* x = this->root;
        while(x != nullptr) {
            y = x;
            if(z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->p = y;
        if(y == nullptr) {
            this->root = z;
        } else if(z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    };
    
    void InorderWalk(bstnode<T> *x) {
        // Recorre en orden el sub�arbol con raiz x, imprimiendo la llave de cada nodo en en una nueva linea de la salida estandar despues de recorrido el subarbol izquierdo y antes de recorrer el subarbol derecho.
        if(x != nullptr) {
            InorderWalk(x->left);
            std::cout << x->key << std::endl;
            InorderWalk(x->right);
        }
    };
    
    bstnode<T>* Search(bstnode<T> *x, const T& k) {
        // Busca la llave k recursivamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
        if(x == nullptr || k == x->key) {
            return x;
        }
        if(k < x->key) {
            return Search(x->left, k);
        } else {
            return Search(x->right, k);
        }
    };
    
    bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
        // Busca la llave k iterativamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
        while(x != nullptr && k != x->key) {
            if(k < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    };
    
    bstnode<T>* Minimum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave menor. Si el arbol esta� vacio, devuelve nullptr.
        if(x != nullptr) {
            while(x->left != nullptr) {
                x = x->left;
            }
        }
        return x;
    };
    
    bstnode<T>* Maximum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave mayor. Si el arbol esta vacio devuelve nullptr.
        if(x != nullptr) {
            while(x->right != nullptr) {
                x = x->right;
            }
        }
        return x;
    };
    
    bstnode<T>* Successor(bstnode<T> *x) {
        // Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no existe el nodo, devuelve nullptr.
        if(x->right != nullptr) {
            return Minimum(x->right);
        }
        bstnode<T> *y = x->p;
        while(y != nullptr && x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    };
    
    void Delete(bstnode<T>* z) {
        // Saca del arbol la llave contenida en el nodo apuntado por z.
        if(z->left == nullptr) {
            this->Transplant(z, z->right);
        } else if(z->right == nullptr) {
            this->Transplant(z, z->left);
        } else {
            bstnode<T>* y = Minimum(z->right);
            if(y->p != z) {
                this->Transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            this->Transplant(z, y);
            y->left = z->left;
            y->left->p = y;
        }
        delete z;
    };

    bstnode<T>* cheatInsert(bstnode<T>* z, bstnode<T>* y) {
        bstnode<T>* x = this->root;
        if(x == nullptr) {
            this->root = z;
        } else {
            z->p = y;
            y->right = z;
        }
        return z;
    }

private: 
    void Transplant(bstnode<T>* u, bstnode<T>* v) {
        if(u->p == nullptr) {
            this->root = v;
        } else if(u == u->p->left) {
            u->p->left = v;
        } else {
            u->p->right = v;
        }
        if(v != nullptr) {
            v->p = u->p;
        }
    }

    void removeTree(bstnode<T>* x) {
        if(x != nullptr) {
            if(x->left != nullptr) {
                removeTree(x->left);
            }
            if(x->right != nullptr) {
                removeTree(x->right);
            }
            delete x;
        }
    }
};

#endif /* bstree_h */

