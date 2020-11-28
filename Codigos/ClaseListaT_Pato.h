#ifndef CLASELISTAT_H_INCLUDED
#define CLASELISTAT_H_INCLUDED

#include "ClaseNodoT.h"
using namespace std;

template <class T> class lista
{
private:
nodo<T> *p;
public:
lista();
~lista();
void altafin(T);
void altaprin(T);
void altapos (int, int);
void baja(T);          //baja de la primera aparición
bool busca(T);
void emite()const;
};


template <class T> void lista<T>::altafin(T x)
{
nodo<T> *aux=p, *aux2;
while ((aux)&&(aux->getSig()))
aux=aux->getSig();
if (aux)
  { aux->setSig(new nodo<T>(x,aux->getSig()));}
else p=new nodo<T>(x,p);
}

template <class T> void lista<T>::altaprin(T x)
{ p=new nodo<T>(x,p); }

template <class T>  void lista<T>::baja(T x)
{
if (p)
{
if((p->getInfo()!=x) && (p->getSig()))
{
nodo<T> *aux1 =p, *aux2 =p->getSig();
while ((aux2->getInfo()!=x) && (aux2->getSig()!=NULL))
{
aux1=aux2 ;
aux2 =aux2->getSig();
}
if (aux2->getInfo()==x)
{
aux1->setSig(aux2->getSig());
delete aux2;
}
}
else if(p->getInfo()==x)
{
nodo<T> *aux =p;
p=p->getSig();
delete aux;
}
}
}
template <class T> lista<T>::lista()
{p=NULL;}

template <class T> lista<T>::~lista()
{  if (p)
  {
    nodo<T> *aux=p;
    while (aux)
    {   p=p->getSig();
        delete aux;
        aux=p;
      }
    }
  }

template <class T> bool lista<T>::busca(T x)
{  nodo<T> *aux=p;
    while(aux)
     {  if (aux->getInfo() == x)
                   {return true;}
         else
                   {aux=aux->getSig();}
      }
     return false;
  }

template <class T>
void lista<T>::emite()const
{
  nodo<T> *aux=p;
  while (aux)
    {
     cout<<aux->getInfo()<<endl;
     aux=aux->getSig();
    }
}
template <class T>
void lista<T>::altapos (int x, int pos)
{if (pos ==0)
 {  altaprin (x);}
 else   {
         nodo<T> *aux1=p;
         nodo<T> *aux2;
         int cont=0;
         while ( ((aux1)&&(aux1->getSig()) )  && (cont<pos-1))
                {
                 aux1=aux1->getSig();
                 cont++;
                }
        if (aux1)
            {
                aux2= new nodo<T>(x);
                aux2->setSig (aux1->getSig());
                aux1->setSig(aux2);
            }
        else
            {
                altafin(x);
            }
        }
}
#endif // CLASELISTAT_H_INCLUDED
