#ifndef _FINDERS_H_
#define _FINDERS_H_
#include "sha256.h"
#include <string.h>
#include <cstring>
#include <iostream>

using namespace std;

//-----------------------------------------------------MACROS----------------------------------------------
//Para contar la cantidad de finders que se tiene. Se utiliza para encontrar el que se necesita en 
//cada situacion
#define MAXFINDER 1

//Para definir las referencias de busqueda
#define STR_BALANCE "balance" 
#define FINDNT "FINDNT"


//-----------------------------------------------------FINDERS---------------------------------------------
//Los finders buscan la informacion especifica pedida (como un id o un value de cierto
// user) y la devuelven en una string

// template <typename T>
typedef string (*finder)(string d);
// , <T> t); //Buscan en un bloque "b" el dato "d"


//Recordar modificar la macro MAXFINDER al agregar nuevas funciones aqui
string findBalance(string d);
// , <user> b);

string findBalance(string d)
// , user b)
{
    //Se recorren todos los outputs de todas las transacciones realizadas buscando
    //la utlima aparicion del usuario especificado para devolver el valor que quedo en output.

    //Es necesario implementar los getters en Block.h
    string result;

    if(d==users.name)
        return to_string(users.balance);
    // outpt aux_txn;
    // for(size_t j=b.transactions[i].getNTxOut();j>=0;j--)
    // {
    //     aux=b.transactions[i].getTxOut()[j];
    //     if(aux.addr==d_hash)
    //         return aux.getValueAsString();
    // }
    return FINDNT;
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
    {STR_BALANCE, findBalance}
};

finder finderParse( string ref)
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