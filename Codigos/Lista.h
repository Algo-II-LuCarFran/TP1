// Implementacion de list doblemente enlazada no circular utilizando
// templates e iteradores.
#ifndef LISTA
#define LISTA
#include <iostream>
#include <math.h> //Necesaria para el uso de floor().
using namespace std;

template<typename T>
class list
{
    class node
    {
        // Debido al fuerte acople entre iteradores y la estructura a
		// la cual iteran (es decir, el iterador necesita conocer los
		// detalles de implementación del TDA para poder abstraer el
		// recorrido), permitimos que la clase iterador tenga acceso
		// directo a los detalles internos del TDA.

        // La list puede tener  acceso a los atributos privados del nodo para poder 
        //modificarlos, dado que la clase nodo es inherente a la clase list.

        T data;
        node* next;
        node* prev;

        friend class list;       
        //friend class iterador;

        public:
        node(T const &data_){data=data_ ; next= NULL; prev=NULL;}; //Constructor a partir de dato. 
        //Se asume que siempre que se quiera crear un nodo se tendrá la informacion que va a contener.
        ~node(){}; //Destructor.
    };

    node* first;
    node* last;
    // node* iterator;
    size_t max_size; //Tamaño de la lista.Si la lista no esta vacia max_size>=1
                    // Si la lista esta vacia max_size=0

    public:
    list(); //Constructor basico
    list(const list& L); //Constructor en base a otra list.
    ~list(); //Destructor
    void append(const T& t); //Agregar nodo al final de la list.
    void insert(const T& t); //Agregar nodo al principio de la list.
    bool placeElement(const T& t, size_t n=1); //Agregar nodo en la posicion 
                                            //n de la list. Si no lo pudo agregar
                                            //devuelve false. Por defecto lo agrega 
                                            // al principio.
    bool empty(); //Verifica si la list está vacia.
    T* find(const T& t); //Encuentra el nodo que contiene el dato T. Si 
                        // no lo encuentra, devuelve NULL
    bool removeElement(const, size_t n); //Elimina el nodo dado por la
                                         // posicion pos. Devuelve false
                                        //si no pudo eliminarlo. 
    bool removeElement(const T& t); //Elimina el nodo que contiene al dato t.
                                  // Devuelve false si no pudo eliminarlo.
    size_t size(); //Obtiene el tamaño de la list
    bool swap(size_t& n1=1,size_t& n2=2); //Intercambia los nodos dados
                                                       // por n1 y n2. Si no puede intercambiar
                                                       //devuelve false. Por defecto intercambia
                                                       //las dos primeras posiciones.
    list const &operator=(const list& other_list);
};

template<typename T>
list<T>::list(){first=NULL;last=NULL;max_size=0;}

// template<typename T>
// list<T>::list(const list& L)
// {}

template<typename T>
list<T>::~list() //Verficar que elimine TODOS los nodos de la lista.
{
    size_t i,j;
    node* aux_forwards;
    node* aux_backwards;
    //Para borrar la lista doblemente enlazada se procede a eliminar
    //los nodos desde el principio hasta la mitad y desde el final hacia 
    //la mitad:
    // - se inicializa un puntero auxiliar al final de la lista y otro al principio;
    // - se hace que los punteros auxiliares apunten a first y last de la lista original;
    // - se borran first y last de la lista original;
    // - se designan los punteros auxiliares como first y last de la "nueva lista" con menos nodos;
    // - si el numero de elementos en la lista era impar, se elimina el sobrante.
     
    for(i=1,j=max_size; i<=floor(max_size)/2 ; i++,j--) //La presencia de i y j son meramente representativas, para dar una analogia con arreglos.
    {
        aux_forwards=this->first->first;
        aux_backwards=this->last->last;

        delete this->first;
        delete this->last;

        this->first=aux_forwards;
        this->last=aux_backwards;
    }

    if(max_size%2)
    {
        delete this->first;
    }
}

template<typename T>
void list<T>::append(const T& t)
{

}

// template<typename T>
// void list<T>::insert(const T& t)
// {

// }

template <typename T>
bool list<T>::placeElement(const T& t, size_t n)
{
    if(n>max_size)
        return false;
}

// template<typename T>
// bool list<T>::empty()
// {

// }

// template<typename T>
// T* list<T>::find(const T& t)
// {

// }

// template<typename T>
// bool list<T>::removeElement(const size_t n)
// {

// }

// template<typename T>
// bool list<T>::removeElement(const T& t)
// {

// }

// template<typename T>
// size_t list<T>::size()
// {
    
// }

// template<typename T>
// bool list<T>::swap(const size_t& n1=1,const size_t& n2=2)
// {

// }

// list const &operator=(const list& other_list)
// {

// }

#endif