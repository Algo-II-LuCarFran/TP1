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

block mempool;

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

	string src=sha256(args[0]); //El primer elemento se condice con el usuario de origen.
	
	string aux;
	
	//double scr_value=string2double(<variable global que representa los balances>.find(value,scr)); 
	//Se encuentra el dinero disponible por el usuario que aporta el dinero en la transaccion.
	//Precondicion: la lista global con los balances debe estar actualizada en todo momento.

	//size_t dim_array_aux=(args.getSize()-1)/2;
	//Array<string> dst(dim_array_aux); //Arreglo de usuarios destino.

	//Al saber la cantidad de argumentos que se reciben se puede calcular el tamaño de los arreglos auxiliares, pues
	// args.getSize()-1 es la cantidad de argumentos relacionados a los usuarios de destino. Como vienen de a pares
	//(una vez validados) el resultado de (args.getSize()-1)/2 sera siempre entero, el valor del tamaño del arreglo.

	// Array<string> dst_value_str(dim_array_aux); //Arreglo de valores(en strings) a transferir a usuarios destino.
	// Array <double> dst_value(dim_array_aux);   //Arreglo de valores(en doubles) a transferir a usuarios destino.

	//Se obtienen el hash del usuario origen y su dinero disponible indicados por linea de comandos en variables aux(arreglos).
	//Se verifica en la variable global de usuarios si las transacciones son validas (mediante variables aux). Si lo son,
	//se cargan. Si no ,se anulan.


	// for(size_t i=2,size_t j=0; i <=args.getSize() ;i+=2,j++)
	// {
	// 	//Se consiguen los hash de los usuarios destino y los valores a transferir
	//	dst[j]=sha256(args[i-1]);
	//  args[i-1]=dst[j]; //Necesario para evitar complicaciones a la hora de generar el arreglo de txn.
	//	dst_value_str[j]=args[i];
	// 	dst_value[j]=string2double(dst_value_str[j]);

	// 	if(dst_value[i]<0) //No se puede transferir una cantidad negativa
	// 		return MSG_FAIL;
	// 	scr_value-=dst_value[j];
	// if(src_value<0) //Si en algun momento los fondos del usuario fuente se terminan, se devuelve error.
	// 	return MSG_FAIL;
	// }
	//  //Al salir del for ya se tienen cargadas las estructuras con las addresses y los valores a transferrirles
	//	//por lo que se crea un arreglo con la informacion de la transaccion 
	
	//Queda generar un arreglo de 3 cosas para el input
	//Array <string> input_array(3); //Siempre se tendra un arreglo de 3 elementos, pues hay un solo input 
									// y cada input requiere 3 campos a especificar: tx_id, idx, addr.
	//1)Cargar el tx_id.
	//2)Cargar el idx. 
	//3)Cargar el addr.
	//4)Implementar el operador + para el array, asi se pueden concatenar dos arrays.
	//  Concatenar input_array con args.getSubArray(2,final). Debe quedar guardado en input_array.
	//5)Se crea la transaccion:
	//txn txn_aux(input_array); 
	//6)En algun lado se deben actualizar los users de la lista global con los valores de las 
	//  transferencias realizadas
	//7)Añadir a la mempool(variable global) la transaccion actual txn_aux:
	//	mempool.addTxn(txn_aux);

	//return sha256(txn_aux.getTxnAsString());
	 return "hola";
}

string cmdMine(Array <string> args)
{
	return "hola";
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