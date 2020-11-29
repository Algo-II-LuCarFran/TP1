#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <bitset>
#include <ctype.h>
#include <iomanip>

#include "math.h"
#include "tools.h"
#include "Array.h"
#include "sha256.h"
#include "Lista.h"
#include "block.h"
#include "global.h"

using namespace std;
string cmdMine(Array <string> args, list <block> algochain);

int main()
{
    list <block> algochain;
    Array <string> arg(1);
    arg[0]= "algochain.txt";
    string aux = cmdMine (arg, algochain);
    cout << aux << endl;
    return 1;
}
string cmdMine(Array <string> args, list <block> algochain)
		//Ensambla y agrega a la Algochain un nuevo bloque a partir de todas las transacciones en la mempool. 
		//La dificultad del minado viene dada por args
{
	/*Valor de retorno.
	 	Hash del bloque en caso de exito;  FAIL en caso de falla por invalidez.
	*/
	size_t bits = stoi(args[0]);
	block aux_save;
	if(bits<0)
	{
		cerr << "ERROR: dificultad invalida"<< endl; // que otra falla?
		exit(1);
	}
	block aux = algochain.getLastNode();
	string prev_block = sha256(sha256(aux.getBlockAsString()));
	// hdr header_aux = aux.getHeader();
	// string prev_block = header_aux.getTxnHash(); //de donde saco el prevbloc? de lalista de bloques
	mempool.setHeader(prev_block,bits);
	aux_save = mempool; //lo guargo para despues imprimirlo
	//guardar la mempool en la parte de la lista correspondientes
	algochain.append(mempool);
	//limpiar mempool
	block empty_block;
	mempool = empty_block;
	return aux_save.getBlockAsString();
}
