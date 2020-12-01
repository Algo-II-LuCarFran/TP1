#ifndef _LISTA_H_
#define _LISTA_H_

#include "math.h"
#include "prototypeLista.h"
#include "finders.h"

// Implementacion de list doblemente enlazada no circular utilizando
// templates e iteradores.

//Se aprovecha el hecho de que la lista tiene una referencia del principio y el final para reducir a la mitad
//el procesamiento de las altas,bajas y borrado de las listas.

//Los nodos son creados con memoria dinamica.


template<typename T>
list<T>::list(){first=NULL;last=NULL;max_size=0;}

template<typename T>
list<T>::list(list& L)
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
		this->first=L.first;
		this->last=L.last;

		next_=L.first;
		prev_=L.last;
		for(size_t i=1; i<=floor(L.max_size)/2;i++)
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
		if((L.max_size)%2) //En este punto next->next=prev_->prev
		{
			node* iter_1=new node(next_->next->data);
			iter_1=next_;
			next_=iter_1->next;
			next_->prev=iter_1;
		} 
		this->max_size=L.max_size;
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
size_t list<T>::size(){return this->max_size;}

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
string list<T>::findAttr(const string& ref,const string& d )
{
	finder aux_finder;
	aux_finder = finderParse(ref);
	string result;

	node* prev_;
	node* aux;

	if(this->empty())
	{    
		return FINDNT;
	}
	else
	{
		aux=this->last;
		aux->next=this->last->next;
		aux->prev=this->last->prev;

		if((result = aux_finder(d,(aux->data).toString())) != FINDNT) //Si se encuentra en el ultimo, se devuelve el dato contenido en el ultimo.
		{   
			return result;
		}

		for(size_t i=this->max_size; i>=1;i--)
		{   	
			prev_=aux->prev;
			if(!prev_)
			{   
				return NULL;
			}

			prev_->next=aux;
			prev_->prev=aux->prev->prev; 
			if((result = aux_finder(d,(prev_->data).toString())) != FINDNT)
			{
				return result;
			}
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

template <typename T>
void list<T>::show(ostream& oss) {
	if(this->empty())
	{
		oss << "Lista vacia" << endl;
		return;
	}
	if(first == NULL){
		oss << "NULL";
		return;
	}
	node* now = first;
	while(now->next != NULL){
		oss << now->data << endl;
		now = now->next;
	}
	oss << now->data << endl;
}
template<typename T>
T list<T>::getFirstNode()
{
	node *aux = first;
	T aux2 = aux->getData();
	return aux2;
}
template<typename T>
T list<T>::getLastNode()
{
	node *aux = last;
	T aux2 = aux->getData();
	return aux2;
}

#endif // _LIST_H_