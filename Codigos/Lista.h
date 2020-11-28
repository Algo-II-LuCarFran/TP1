// Implementacion de list doblemente enlazada no circular utilizando
// templates e iteradores.

//Se aprovecha el hecho de que la lista tiene una referencia del principio y el final para reducir a la mitad
//el procesamiento de las altas,bajas y borrado de las listas.

//Los nodos son creados con memoria dinamica.

#ifndef _LIST_H_
#define _LIST_H_
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
		friend class list;   

		T data;
		node* next;
		node* prev;    
		//friend class iterador;

		public:
		node(T const &data_);//Constructor a partir de dato. 
		//Se asume que siempre que se quiera crear un nodo se tendrá la informacion que va a contener.
		~node(); //Destructor.
	};

	node* first;
	node* last;
	// node* iterator;
	size_t max_size; //Tamaño de la lista.Si la lista no esta vacia max_size>=1
					// Si la lista esta vacia max_size=0

	public:

	typedef T t_dato;
	typedef node t_node;

	list(); //Constructor basico
	list(const list& L); //Constructor en base a otra list.
	~list(); //Destructor

	void append(const T& t); //Agregar nodo al final de la list.
	void insert(const T& t); //Agregar nodo al principio de la list.
	bool placeElement(const T& t, size_t n=1);//Agregar nodo en la posicion n de la list. Si no lo pudo agregar
											 //devuelve false. Por defecto lo agrega al principio.
	bool empty(); //Verifica si la list está vacia.
	T* find(const T& t); //Encuentra el nodo que contiene el dato T. Si  no lo encuentra, devuelve NULL.
	bool removeElement(const T& t); //Elimina el primer nodo que contiene al dato t. Devuelve false si no pudo eliminarlo.
	size_t size(); //Obtiene el tamaño de la list

	void show(ostream& o);
	friend ostream& operator<<(ostream& oss, list& l) 
	{
		l.show(oss);
		return oss;
	}
};

template<typename T>
list<T>::node::node(T const &data_)
{
	data=data_; 
	next= NULL; 
	prev=NULL;
} 

template<typename T>
list<T>::node::~node()
{
}

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
T* list<T>::find(const T& t)
{
	node* prev_;
	node* next_;
	node* iter;

	size_t i;

	if(this->empty())
		return NULL;
	else
	{
		next_=this->first;
		prev_=this->last;
		for(size_t i=1; i<=floor(this->max_size)/2;i++)
		{    
			if(next_->data==t)
				return next_;
			if(prev_->data==t)
				return prev_;

			iter=next_;
			next_=iter->next;
			next_->prev=iter;

			iter=prev_;
			prev_=iter->prev;
			prev_->next=iter;
		}
		return NULL;
	}
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


// list const &operator=(const list<T>& other_list)
// {

// }


template <typename T>
void list<T>::show(ostream& oss) {
	if(first == NULL){
		oss << "NULL";
	}
	node* now = first;
	while(now->next != NULL){
		oss << now->data << endl;
		now = now->next;
	}
	oss << now->data << endl;
}
#endif // _LIST_H_