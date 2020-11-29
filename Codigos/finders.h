#ifndef _FINDERS_H_
#include _FINDERS_H_
#include "sha256.h"
#include <string.h>
#include <cstring>

using namespace std;

//-----------------------------------------------------MACROS----------------------------------------------
//Para contar la cantidad de finders que se tiene. Se utiliza para encontrar el que se necesita en 
//cada situacion
#define MAXFINDER 1

//Para definir las referencias de busqueda
#define STR_VALUE "value" 


//-----------------------------------------------------FINDERS---------------------------------------------
//Los finders buscan la informacion especifica pedida (como un id o un value de cierto
// user) y la devuelven en una string
typedef string (*finder)(string d); //Buscan en un bloque dado el value del usuario d


//Recordar modificar la macro MAXFINDER al agregar nuevas funciones aqui
string finderUser(string d);


string finderUser(string d)
{
    //Se recorren todos los outputs de todas las transacciones realizadas buscando
    //la utlima aparicion del usuario especificado para devolver el valor que quedo en output.

    //Es necesario implementar los getters en Block.h
    //Seria bueno agregar unos metodos mas en la clase outpt que sean getValueAsString()
    //y getAddr()
    string result;

    string d_hash=sha256(d);
    outpt aux;
    for(size_t i=this->getBody().getTxnCount()-1;i>=0;;i--)
    {
        for(size_t j=this->getBody().getTxns()[i].getNTxOut();j>=0;j--)
        {
            aux=this->getBody().getTxns()[i].getTxOut()[j];
            if(aux.addr==d_hash)
                return aux.getValueAsString();
        }
    }
    return "";
}

//---------------------------------------------DICCIONARIOS-----------------------------------------------
//Definicion de las estructuras que relacionan las referencias (el tipo de dato que se
// quiere buscar) con los finders.


//Completar con las definiciones de todos los finders necesarios
struct finder_option_t
{
	string reference; //Identifica el tipo de dato que debe ser buscado (como value o tx_id)
	finder fndr;
};

static finder_option_t dictionary_finder[] = {
	{STR_ISTR_VALUE, finderUser},

};

p_func finderParse( string ref)
{
	string aux;
	int i = 0;

	while(ref != dictionary_finder[i].reference && i < MAXCMD) i++;
	
	if(i == MAXCMD)
	{
		cerr << "El finder no es valido" << endl;
		exit(1);
	}
	return dictionary_finder[i].fndr;
}
#endif // _FINDERS_H_