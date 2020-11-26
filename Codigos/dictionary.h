#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <iostream>
#include <string.h>
#include <cstring>
#include "Array.h"
#include "tools.h"
#include "block.h"
#include "sha256.h"

#define STR_INIT "init"
#define STR_TRANSFER "transfer"
#define STR_MINE "mine"
#define STR_BALANCE "balance"
#define STR_BLOCK "block"
#define STR_TXN "txn"
#define STR_LOAD "load"
#define STR_SAVE "save"

#define NULL_HASH "0000000000000000000000000000000000000000000000000000000000000000"
#define MAXCMD 8

#define MSG_FAIL "FAIL"

#define CHOP_SIZE 5
using namespace std;

typedef string (* p_func)(Array <string>);

string cmdInit(Array <string> args);
string cmdTransfer( Array <string> args);
string cmdMine(Array <string> args);
string cmdBalance(Array <string> args);
string cmdBlock(Array <string> args);
string cmdTxn(Array <string> args);
string cmdLoad(Array <string> args);
string cmdSave(Array <string> args);


struct cmd_option_t
{
	string name;
	p_func comand;
	int num_param;
};

static cmd_option_t dictionary_cmd[] = {
	{STR_INIT, cmdInit, 3},
	{STR_TRANSFER, cmdTransfer, 0},
	{STR_MINE, cmdMine, 1},
	{STR_BALANCE, cmdBalance, 1},
	{STR_BLOCK, cmdBlock, 1},
	{STR_TXN, cmdTxn, 1},
	{STR_LOAD, cmdLoad, 1},
	{STR_SAVE, cmdSave, 1},
};

p_func dictCmds( string cmd, int &num_param)
{
	string aux;
	int i = 0;

	while(cmd != dictionary_cmd[i].name && i < MAXCMD) i++;
	
	if(i == MAXCMD)
	{
		cerr << "El comando no es valido" << endl;
		exit(1);
	}
	num_param = dictionary_cmd[i].num_param;
	return dictionary_cmd[i].comand;
}


string cmdInit(Array <string> args)
{

	string user;
	string STR_TXNing;
	double value;
	size_t bits;

	user =sha256(args[0]);

	if(isNumber<double>(args[1]) == false || args[1][0] == '-')
	{
		cerr << "El user no es valido" << endl;
		exit(1);
	}

	value = stod(args[1]);
	
	if(isNumber<int>(args[2]) == false || args[2][0] == '-')
	{
		cerr << "El bits no es valido" << endl;
		exit(1);
	}

	bits = stoi(args[2]);

	STR_TXNing.append("1");
	STR_TXNing.append("\n");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append(" ");
	STR_TXNing.append("0");
	STR_TXNing.append(" ");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append("\n");
	STR_TXNing.append("1");
	STR_TXNing.append("\n");
	STR_TXNing.append(args[1]);
	STR_TXNing.append(" ");
	STR_TXNing.append(user);
	
	istringstream iss(STR_TXNing);

	block genesis_block(NULL_HASH, bits, &iss);
	return sha256(genesis_block.getBlockAsString());
}

string cmdTransfer( Array <string> args)
{
	//Se debe buscar la ultima aparicion de ese usuario primero en la MEMPOOL y si no se encuentra nada, en la 
	//ALGOCHAIN; conseguir su value y verificar que dicho valor (su dinero disponible) no sea menor a la suma de
	//las cantidades a transferir.

	// string src=sha256(args[0]); //El primer elemento se condice con el usuario de origen.
	// string src_value,aux;
	// Array<string> dst(1); //Inicializacion por defecto en uno
	// Array<string> dst_value_str(1); //Inicializacion por defecto en uno
	// double scr_value=100; //Se inicializa en 100 para pruebas. Debe obtenerse de la mempool o algochain segun corresp.
	// Array <double> dst_value(1);
	// size_t i=0;

	//Se obtienen el hash del usuario origen y su dinero disponible indicados por linea de comandos en variables aux.
	//Se verifica en la mempool y/o algochain si las transacciones son validas (mediante variables aux). Si lo son,
	//se cargan. Si no ,se anulan.

	// txn txn_aux; //Me quede en generar las transacciones. Constructor de txn en base a string creado.


	//HAY QUE OBTENER scr_value PARA SEGUIR A PARTIR DE ESTE PUNTO
	//src_value= ;
	// while(getline(iss, aux, ' ').good() || iss.eof())
	// {
	// 	//Se consiguen los hash de los usuarios destino y los valores a transferir
	// 	if(dst.getSize()==(i+1))
	// 	{
	// 		dst.ArrayRedim( (i+1)+CHOP_SIZE);
	// 		dst_value.ArrayRedim( (i+1)+CHOP_SIZE);
	// 	}
	// 	if( !(getline(iss, dst[i], ' ').good()) || !(iss.eof()))
	// 		return MSG_FAIL;
	// 	if( !(getline(iss, dst_value[i], ' ').good()) || !(iss.eof()))
	// 		return MSG_FAIL;
	// 	if(dst_value[i]<0)
	// 		return MSG_FAIL;
	// 	dst_value[i]=stod(dst_value[i]);
	// 	scr_value-=dst_value[i];
	// 	i++;
	// }
	// if(src_value<0)
	// 	return MSG_FAIL;
	 return "hola";
}

string cmdMine(Array <string> args)
		//Ensambla y agrega a la Algochain un nuevo bloque a partir de todas las transacciones en la mempool. 
		//La dificultad del minado viene dada por args
{
	/*Valor de retorno.
	 	Hash del bloque en caso de exito;  FAIL en caso de falla por invalidez.
	*/
	size_t bits = stoi(args[0]);
	if(bits<0)
	{
		cerr << "ERROR: dificultad invalida"<< endl;
		exit(1);
	}
	block aux = algochain.getLastNode();
	hdr header_aux = aux.getHeader();
	string prev_block = header_aux.getTxnHash(); //de donde saco el prevbloc? de lalista de bloques
	mempool.setHeader(prev_block,bits);
	aux = mempool; //lo guargo para despues imprimirlo
	//guardar la mempool en la parte de la lista correspondientes
	algochain.append(mempool);
	//limpiar mempool
	block empty_block;
	mempool = empty_block;
	return mempool.getBlockAsString();
}


string cmdBalance(Array <string> args)
{
	return "hola";
}

string cmdBlock(Array <string> args)
{
	return "hola";
}

string cmdTxn(Array <string> args)
{
	return "hola";
}

string cmdLoad(Array <string> args)
{
	return "hola";
}

string cmdSave(Array <string> args)
{
	return "hola";
}


Array <string> parseCmdArgs(string str, size_t N)//funcion para verificar la correcta escritura de los argumentos, 
									  // devuelve un array dinamico con los argumentos.
									 //  Le paso N para saber cuantos argumentos debo mirar para que sea correcto
									//   Si es N=0 entonces es argumentos variables impares minimo 3
{
	istringstream iss(str);
	size_t i=0;
	string aux;

	Array <string> args(1); // Lo dimensiono con 3 porque es el valor minimo, despues lo resize
	while(getline(iss, aux, ' ').good() || iss.eof() )//averiguar que pasa con el ultimo
	{
		if(aux == "")
		{
			cerr << "Hay un espacio de mas" << endl; // poner error
			exit(1);
		}
		if (i>=args.getSize())
		{
			args.ArrayRedim(args.getSize()+1);
		}
		if(iss.eof()==true)
		{
			args[i]=aux;
			break;
		}
		args[i]=aux;
		i++;
	}
	if(N!=(i+1) && N!=0)
	{
		cerr << "Numero incorrecto de argumentos"<< endl;
		exit(1);
	}
	return args;
}

#endif //_DICTIONARY_H_