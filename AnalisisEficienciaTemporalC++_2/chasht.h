//
//  chtable.h
//

#ifndef chtable_h
#define chtable_h

#include <list>
#include <vector>

template <typename T>

// Tabla de dispersi�n con encadenamiento
class chtable {
public:
    // Constructor que especifica el tama�o de la tabla
    chtable(int sz) 
        : size(sz) 
        , table(size,std::list<T>()) {
    };
        
    // Destructor (borra la tabla)
    ~chtable() {
    };
    
    // Inserta el elemento en la tabla
    void Insert(const T& k) {
        int index = k % size;
        table[index].push_back(k);
    };
    
    // Retorna un puntero a la llave o nullptr si no se encuentra
    T* Search(const T& k) {
        T* searchKey = nullptr;
        int index = k % size;
        for(auto i = table[index].begin(); i != table[index].end(); i++) {
            if(*i == k) {
                return &(*i);
            }
        }
        return searchKey;
    };
    
    
private:
    // N�mero de entradas en la tabla
    int size;
    
    // La tabla es un vector de listas de STL
    std::vector<std::list<T> > table;
};

#endif /* chtable_h */
