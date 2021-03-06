#ifndef  TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <bitset>
#include "block.h"

using namespace std;

static const string ERROR="Error"; //Se usa a modo de macro.

string Hex2Bin(const string& s); // Transforma una cadena de caracteres que contiene un numero en Hexa a una en binario
bool isHash(const string& str); // Confirma si str cumple con los requisitos minimos de un HASH
bool isNumber(const string& s); // Revisa si s es un numero, implementado como template para distinguir si es int o double, etc...
bool isError(const string& addr); // Se fija si en addr esta lo guardado en la variable ERROR


bool isError(const string& addr)
{
	if(addr==ERROR)
		return false;
	else
		return true;
}

string Hex2Bin(const string& s)//transforma de hexa a binario una string, maximo 4 bytes, 8 char y 32 bits
{
	stringstream ss;
	ss << hex << s;
	unsigned n;
	ss >> n;
	bitset<4> b(n);//32 es el maximo por el unsigned

	return b.to_string();//.substr(32 - 4*(s.length()));
}
bool isHash(const string& str) //Devuelve false (0) si no es un hash, true (1) si lo es.
{
	int n;
	if(str.length()!=64)//El hash devuelve una string de 64 chars. Es siempre de largo fijo.
		return false;
	for (size_t i = 0; i < str.length(); i++)
	{

		n=(int)(tolower(str[i])-'0');
		if(n<0|| (n>9&&n<17)||(n>22 && n<49)||n>63) //se verifica si el char de la string es un numero hexa
			return false;
	}
	return true;
	
}
template<typename Numeric>
bool isNumber(const string& s) //Devuelve 1 si es true y 0 si es false
{
	Numeric n;
	return((istringstream(s) >> n >> ws).eof());
}
/*
bool setAlgochainFromFile( istream *iss)
{
	block block_aux, block_empty;
	string str,str_aux;
	getline(*iss, str, '\n');	
	size_t i = 0, aux = 0;
	hdr header_aux;
	size_t diff, nonce;
	bdy body_aux;
	while (str!="")
	{
		//seteo el header
		//validacion
		header_aux.setPrevBlock(str);
		getline(*iss, str, '\n');
		//validacion
		header_aux.setTxnsHash(str);
		getline(*iss, str, '\n');
		diff = stoi(str);
		header_aux.setBits(diff);
		getline(*iss, str, '\n');
		nonce = stoi(str);
		header_aux.setNonce(nonce);
		getline(*iss, str, '\n');

		block_aux.setHeader(header_aux);
		//seteo el body
		if(isHash(str_aux=block_aux.setBody(iss))==true)
		{
			str=str_aux;
			break;
		}
		else if (str_aux=="")
		{
			str=str_aux;
			break;
		}
		else
		{
			return false;
		}
		

	}
	return true;
	
}
*/
// string printAlgochain(list<block> chain)
// {

// }

#endif //TOOLS_H