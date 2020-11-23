#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <iostream>
#include <string.h>
#include <cstring>
#include "block/Array.h"
#include "block/tools.h"
#include "block/block.h"

#define INIT_STR "init"
#define TRANSFER_STR "transfer"
#define MINE_STR "mine"
#define BALANCE_STR "balance"
#define BLOCK_STR "block"
#define TXN_STR "txn"
#define LOAD_STR "load"
#define SAVE_STR "save"

#define MAXCMD 8

using namespace std;

string cmdInit(Array <string> args);
string cmdTranfer(Array <string> args);
string cmdMine(Array <string> args);
string cmdBalance(Array <string> args);
string cmdBlock(Array <string> args);
string cmdTxn(Array <string> args);
string cmdLaod(Array <string> args);
string cmdSave(Array <string> args);

static const string cmds[]={
	INIT_STR,
	TRANSFER_STR,
	MINE_STR,
	BALANCE_STR,
	BLOCK_STR,
	TXN_STR,
	LOAD_STR,
	SAVE_STR
};

static const string (*func_cmd[])(string) = {
	cmdInit,
	cmdTransfer,
	cmdMine,
	cmdBalance,
	cmdBlock,
	cmdTxn,
	cmdLoad,
	cmdSave
};

int dictCmds(const string cmd)
{
	string aux;
	int i = 0;

	while(cmd != cmds[i] || i == MAXCMD) i++;
	
	return func_cmd[i];
}


string cmdInit(Array <string> args)
{
	string user;
	string txn_string;
	double value;
	int bits;

	if(isHash(args[0]) == false)
	{
		cerr << "El user no es valido" << endl;
		exit(1);
	}
	user = args[0];

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
}

string cmdTranfer(Array <string> args)
{

}

string cmdMine(Array <string> args)
{

}

string cmdBalance(Array <string> args)
{

}

string cmdBlock(Array <string> args)
{

}

string cmdTxn(Array <string> args)
{

}

string cmdLoad(Array <string> args)
{

}

string cmdSave(Array <string> args)
{

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
        if(isspace(aux[0])==0)
        {
            cout << "Hay un espacio"; // poner error
            return 1;
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
        cout<< "Le pifiaste a la cantidad de parametros"<< endl;// poner error
    }
    return args;
}

#endif //_DICTIONARY_H_