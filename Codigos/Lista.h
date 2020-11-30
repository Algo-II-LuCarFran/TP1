// Implementacion de list doblemente enlazada no circular utilizando
// templates e iteradores.

//Se aprovecha el hecho de que la lista tiene una referencia del principio y el final para reducir a la mitad
//el procesamiento de las altas,bajas y borrado de las listas.

//Los nodos son creados con memoria dinamica.

#ifndef _LIST_H_
#define _LIST_H_
#include <iostream>
#include <math.h> //Necesaria para el uso de floor().
#include "finders.h" //Necesaria para el uso de find().
#include <string.h>
#include <cstring>

#define FINDNT "FINDNT"

using namespace std;


template<class T>
class list
{
    class node  
    {
        // La list puede tener  acceso a los atributos privados del nodo para poder 
        //modificarlos, dado que la clase nodo es inherente a la clase list.

        T data;
        node* next;
        node* prev;
        friend class list;       

        public:
        node(T const &data_){data=data_ ; next= NULL; prev=NULL;}; //Constructor a partir de dato. 
        //Se asume que siempre que se quiera crear un nodo se tendrá la informacion que va a contener.
        node* getNext(){return this->next;}
        node* getPrev(){return this->prev;}
        T getData(){return this->data;}
        ~node(){}; //Destructor.
    };

    node* first;
    node* last;
    size_t max_size; //Tamaño de la lista.Si la lista no esta vacia max_size>=1
                    // Si la lista esta vacia max_size=0
    public:
    list(); //Constructor basico
    list(const list& L); //Constructor en base a otra list.
    ~list(); //Destructor
    void append(const T& t); //Agregar nodo al final de la list.
    void insert(const T& t); //Agregar nodo al principio de la list.
    bool placeElement(const T& t, size_t n=1);//Agregar nodo en la posicion n de la list. Si no lo pudo agregar
                                             //devuelve false. Por defecto lo agrega al principio.
    bool empty(); //Verifica si la list está vacia.
    T  find(const T& t); //Encuentra el ultimo nodo que contiene el dato T. Si  no lo encuentra, debe devolver NULL.
                              //DEBERIA devolver un puntero a un dato dentro de un nodo de la lista,DEBE devolver un puntero a un dato constante.
    string find(const string& ref,const string& d ); //Encuentra el dato "d" de  tipo "ref" en su última aparición en la lista.
                                                    //Ejemplo: ref=value d=Carla. Devuelve una string con el el ultimo output de Carla
                                                   // Ejemplo: ref= id   d=<valor del hash>. Devuelve el bloque como string.
                                                  // Si  no lo encuentra, devuelve una cadena vacia.                          
    bool removeElement(const T& t); //Elimina el primer nodo que contiene al dato t. Devuelve false si no pudo eliminarlo.
    size_t size(); //Obtiene el tamaño de la list
    // list const &operator=(const list& other_list);
    T  getFirstNode();
    T  getLastNode();
    template <class TT>  friend ostream & operator<<(ostream & os,  list<TT> &L)//Operador de impresion de salida
    {
        node *aux = L.first;
        while (aux)
        {
            os << aux->getData()<<endl;
            aux = aux->getNext();
        }
        return os;
    }
};
template<typename T>
T list<T>::getFirstNode(){return this->first->data;}
template<typename T>
T list<T>::getLastNode(){return this->last->data;}

template<typename T>
list<T>::list(){first=NULL;last=NULL;max_size=0;}

template<typename T>
list<T>::list(const list& L)
{
    node* prev_;
    node* next_;
    size_t i;

    if(L.empty())
    {
        this->max_size=0;
        this->first=NULL;
        this->last=NULL;
    }
    else
    {
        this->first=L->first;
        this->last=L->last;

        next_=L->first;
        prev_=L->last;
        for(size_t i=1; i<=floor(L->max_size)/2;i++)
        {    
            node* iter_1=new node(next_->data);
            iter_1=next_;
            next_=iter_1->next;
            next_->prev=iter_1;

            node* iter_2=new node(prev_->data);
            iter_2=prev_;
            prev_=iter_2->prev;
            prev_->next=iter_2;
        }
        if((L->max_size)%2) //En este punto next->next=prev_->prev
        {
            node* iter_1=new node(next_->next->data);
            iter_1=next_;
            next_=iter_1->next;
            next_->prev=iter_1;
        } 
        this->max_size=L->max_size;
    }
}

template<typename T>
bool list<T>::empty()
{
    //Forma complicada de preguntar si la lista esta vacia
    // if((this->first==this->last)&&(this->first==NULL)) 
    if(!max_size)
        return true;
    return false;

}


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
        aux_forwards=this->first->next;
        aux_backwards=this->last->prev;

        delete (this->first);
        delete (this->last);

        this->first=aux_forwards;
        this->last=aux_backwards;
    }

    if((this->max_size)%2)
    {
        delete this->first;
    }
}

template<typename T>
size_t list<T>::size(){return this->max_size;};

template<typename T>
void list<T>::append(const T& t)
{
    node *aux= new node(t);

    if( this->empty() )
    {
        aux->next=NULL;
        aux->prev=NULL;
        this->last=aux;
        this->first=aux;
    }
    else
    {
        aux->next=NULL;
        aux->prev=this->last;
        this->last->next=aux;
        this->last=aux;
    }
    this->max_size=this->max_size+1;

}

template<typename T>
void list<T>::insert(const T& t)
{
    node *aux= new node(t);

    if( this->empty() )
    {
        aux->next=NULL;
        aux->prev=NULL;
        this->last=aux;
        this->first=aux;
    }
    else
    {
        aux->prev=NULL;
        aux->next=this->first;
        this->first->prev=aux;
        this->first=aux;
    }
    this->max_size=this->max_size+1;

}

template <typename T>
bool list<T>::placeElement(const T& t, size_t n)
{
    if(n>max_size)
        return false;

    node*aux=new node(t);
    node* p_aux;

    if(n==1)
        this->insert(t);
    else if(n==this->max_size)
        this->append(t);
    else if(n<=floor(this->max_size)/2)
    {    
        aux=this->first;
        aux->prev=NULL;
        for(size_t i=1; i<n ;i++)
        {    
            p_aux=aux;
            aux=aux->next;
            aux->prev=p_aux;
        }
    }
    else if(n>floor(this->max_size)/2)
    {    
        aux=this->last;
        aux->next=NULL;
        for(size_t i=1; i<n ;i++)
        {    
            p_aux=aux;
            aux=aux->prev;
            aux->next=p_aux;
        }
    }
    else 
        return false; //Si por algún motivo no pudo realizarse ninguna de las acciones previas, devuelve error.
    return true;
}


template<typename T>
T list<T>::find(const T& t)
{
    node* prev_;
    node* aux;


    if(this->empty())
    {    
        // cout<<"La lista esta vacia"<<endl;
        return NULL;
    }
    else
    {
        aux=this->last;
        aux->next=this->last->next;
        aux->prev=this->last->prev;

        if(aux->data==t) //Si se encuentra en el ultimo, se devuelve el dato contenido en el ultimo.
        {   
            // cout<<"Encontre el dato, es "<<aux->data<<endl;
            // *data_pointer=aux->data; 
            // cout<<"El valor del contenido del puntero que se devuelve es: "<<*data_pointer<<endl;
            // cout<<"El valor del puntero es "<< data_pointer<<endl;
            return aux->data;
        }

        for(size_t i=this->max_size; i>=1;i--)
        {   
            // cout<<"Llego a la "<<this->max_size-i+1<<"esima iteracion del for"<<endl;
            //Se fija el nodo anterior correctamente
            prev_=aux->prev;
            //Se comprueba que no se haya llegado al ppio de la lista
            if(!prev_)
            {   
                // cout<<"Llegue al principio de la lista. No encontre el dato. Devuelvo NULL"<<endl; 
                return NULL;
            }

            prev_->next=aux;
            prev_->prev=aux->prev->prev; 

            // cout<<"El valor del dato actual es "<<aux->data<<endl;
            // cout<<"El valor del dato actual de prev_ es "<<prev_->data<<endl;

            // cout<<"El valor del dato previo es "<<aux->prev->data<<endl;
            // cout<<"El valor del dato previo de prev_ es "<<prev_->prev->data<<endl;
            //Se comprueba si el dato buscado está en nodo anterior
            if(prev_->data==t)
            {
                // cout<<"Encontre el dato, es "<<prev_->data<<endl;
                // cout<<"Data_pointer tiene cargado: "<<data_pointer<<endl;
                // cout<<"Data_pointer tiene adentro: "<<*data_pointer<<endl;
                // (*data_pointer)=prev_->data; 
                // cout<<"Pude asignarle algo a data_pointer: "<< *data_pointer <<endl;
                return prev_->data;
            }
            //Se retrocede en la lista
            aux=prev_;
            aux->next=prev_->next;
            aux->prev=prev_->prev;
        } 
    }
    // cout<<"No lo encontre, devuelvo NULL"<<endl;
    return NULL; //Si se hubo algun error se devuelve NULL.
}
template<typename T>
string list<T>::find(const string& ref,const string& d )
{
    // finder aux_finder;
    // aux_finder=finderParse(ref);

    string result;
    node* prev_;
    node* aux;


    if(this->empty())
    {    
        // cout<<"La lista esta vacia"<<endl;
        return FINDNT;
    }
    else
    {
        aux=this->last;
        aux->next=this->last->next;
        aux->prev=this->last->prev;

        if((result=findBalance(d)!=FINDNT) //Si se encuentra en el ultimo, se devuelve el dato contenido en el ultimo.
        {   
            // cout<<"Encontre el dato, es "<<aux->data<<endl;
            // *data_pointer=aux->data; 
            // cout<<"El valor del contenido del puntero que se devuelve es: "<<*data_pointer<<endl;
            // cout<<"El valor del puntero es "<< data_pointer<<endl;
            return result;
        }

        for(size_t i=this->max_size; i>=1;i--)
        {   
            // cout<<"Llego a la "<<this->max_size-i+1<<"esima iteracion del for"<<endl;
            //Se fija el nodo anterior correctamente
            prev_=aux->prev;
            //Se comprueba que no se haya llegado al ppio de la lista
            if(!prev_)
            {   
                // cout<<"Llegue al principio de la lista. No encontre el dato. Devuelvo NULL"<<endl; 
                return FINDNT;
            }

            prev_->next=aux;
            prev_->prev=aux->prev->prev; 

            // cout<<"El valor del dato actual es "<<aux->data<<endl;
            // cout<<"El valor del dato actual de prev_ es "<<prev_->data<<endl;

            // cout<<"El valor del dato previo es "<<aux->prev->data<<endl;
            // cout<<"El valor del dato previo de prev_ es "<<prev_->prev->data<<endl;
            //Se comprueba si el dato buscado está en nodo anterior
            if((result=aux_finder(d,prev_->data))!=FINDNT)
            {
                // cout<<"Encontre el dato, es "<<prev_->data<<endl;
                // cout<<"Data_pointer tiene cargado: "<<data_pointer<<endl;
                // cout<<"Data_pointer tiene adentro: "<<*data_pointer<<endl;
                // (*data_pointer)=prev_->data; 
                // cout<<"Pude asignarle algo a data_pointer: "<< *data_pointer <<endl;
                return result;
            }
            //Se retrocede en la lista
            aux=prev_;
            aux->next=prev_->next;
            aux->prev=prev_->prev;
        } 
    }
    return FINDNT;
}


template<typename T>
bool list<T>::removeElement(const T& t)
{
    if( this->empty() )
        return false;
    node* iter;
    node* next_;
    node* aux;
    next_=this->first;

    for(size_t i=1; i<= this->max_size; i++)
    {
        iter=next;
        if((next_->data)==t)
        {   
            aux=next_->prev;
            iter=next_->next;
            delete next_;
            aux->next=iter;
            iter->prev=aux;
            return true;
        }
        next_=iter->next;
        next_->prev=iter;       
    }
    return false; //Si no lo encontro en el for es porque no esta en la lista
}



#endif // _LIST_H_