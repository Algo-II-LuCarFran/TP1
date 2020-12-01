
#ifndef NODO
#define NODO
#include <iostream>
using namespace std;
 //Se implementa la clase nodo con posibilidad de utilizarlo en una lista 
// doblemente enlazada y con cursor/iterador.

template <class T>
class node
{
    T data;
    node* next;
    node* prev;

    // friend class list;        // Si hay una implementacion de lista, puede tener 
    //                          // acceso a los atributos privados del nodo.
    // friend class iterador;  // Si hay una implementacion de iterador, puede tener 
    //                        // tener acceso a los atributos privados del nodo.
    public:
    node(T const &data_){data=data_ ; next= NULL; prev=NULL;}; //Constructor a partir de dato.
    ~node(){}; //Destructor.
};

#endif
