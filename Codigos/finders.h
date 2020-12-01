#ifndef _FINDERS_H_
#define _FINDERS_H_

#include <iostream>
#include "user.h"

using namespace std;
//-----------------------------------------------------MACROS----------------------------------------------
//Para contar la cantidad de finders que se tiene. Se utiliza para encontrar el que se necesita en 
//cada situacion
#define MAXFINDER 2


#define FINDNT "Findnt" 
//Para definir las referencias de busqueda
#define STR_BALANCE "balance" 
#define STR_TRANSACTIONS "transactions"

using namespace std;
//-----------------------------------------------------FINDERS---------------------------------------------
//Los finders buscan la informacion especifica pedida (como un id o un value de cierto
// user) y la devuelven en una string
typedef string (*finder)(string d,string str); //Buscan en un la string str dato d


//Recordar modificar la macro MAXFINDER al agregar nuevas funciones aqui

string findBalance(string d, string str);
string findTransactions(string d, string str);

string findTransactions(string d, string str)
{
    user aux_user(str);
	string result, aux;
	aux = aux_user.getName();
	if(d == aux)
		return "LCAS SE LA COME";
	else
		return FINDNT;

}
string findBalance(string d, string str)
{
	//Se recorren todos los outputs de todas las transacciones realizadas buscando
	//la utlima aparicion del usuario especificado para devolver el valor que quedo en output.

	//Es necesario implementar los getters en Block.h
	//Seria bueno agregar unos metodos mas en la clase outpt que sean getValueAsString()
	//y getAddr()

	user aux_user(str);
	string result, aux;
	aux = aux_user.getName();
	if(d == aux)
		return to_string(aux_user.getBalance());
	else
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
	{STR_BALANCE, findBalance},
    {STR_TRANSACTIONS, findTransactions}
};

finder finderParse( string ref)
{
	string aux;
	int i = 0;

	while(ref != dictionary_finder[i].reference && i < MAXFINDER) i++;
	
	if(i == MAXFINDER)
	{
		cerr << "El finder no es valido" << endl;
		exit(1);
	}
	return dictionary_finder[i].fndr;
}
#endif //_FINDERS_H_



		
	// string d_hash=sha256(d);
	// outpt aux;
	// for(size_t i=this->getBody().getTxnCount()-1;i>=0;;i--)
	// {
	//     for(size_t j=this->getBody().getTxns()[i].getNTxOut();j>=0;j--)
	//     {
	//         aux=this->getBody().getTxns()[i].getTxOut()[j];
	//         if(aux.addr==d_hash)
	//             return aux.getValueAsString();
	//     }
	// }
