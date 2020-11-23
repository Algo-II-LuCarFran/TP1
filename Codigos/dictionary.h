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

using namespace std;

typedef string (* p_func)(Array <string>);

string cmdInit(Array <string> args);
string cmdTransfer(Array <string> args);
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
};

static cmd_option_t dictionary_cmd[] = {
	{STR_INIT, cmdInit},
	{STR_TRANSFER, cmdTransfer},
	{STR_MINE, cmdMine},
	{STR_BALANCE, cmdBalance},
	{STR_BLOCK, cmdBlock},
	{STR_TXN, cmdTxn},
	{STR_LOAD, cmdLoad},
	{STR_SAVE, cmdSave},
};

p_func dictCmds(const string cmd)
{
	string aux;
	int i = 0;

	while(cmd != dictionary_cmd[i].name && i < MAXCMD) i++;
	
	if(i == MAXCMD)
	{
		cerr << "El comando no es valido" << endl;
		exit(1);
	}
	return dictionary_cmd[i].comand;
}


string cmdInit(Array <string> args)
{

	string user;
	string STR_TXNing;
	double value;
	size_t bits;

	user = sha256(sha256(args[0]));

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

string cmdTransfer(Array <string> args)
{
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
		cerr << "Numero incorrecto de argumentos"<< endl;// poner error
		exit(1);
	}
	return args;
}

#endif //_DICTIONARY_H_