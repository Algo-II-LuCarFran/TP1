#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#include "Lista.h"
#include "cmdline.h"
#include "sha256.h"
#include "block.h"
#include "dictionary.h"
#include "main.h"


// agregar una variable global lista algochain static list<block> algochain;
// static block mempool();


int main()
{
	string STR_TXNing;
	STR_TXNing.append("Carla");
	STR_TXNing.append("\n");
	STR_TXNing.append("157.68");
	STR_TXNing.append("\n");
	STR_TXNing.append("2"); // txn in
	STR_TXNing.append("\n");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append(" ");
	STR_TXNing.append("0");
	STR_TXNing.append(" ");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append("\n");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append(" ");
	STR_TXNing.append("0");
	STR_TXNing.append(" ");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append("\n");
	STR_TXNing.append("2");
	STR_TXNing.append("\n");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append(" ");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append("\n");
	STR_TXNing.append(NULL_HASH);
	STR_TXNing.append(" ");
	STR_TXNing.append(NULL_HASH);


	user carla(STR_TXNing);
	users.append(carla);
	cout<<"El balance de Carla es \n"<<	users.find("balance","Carla")<<endl;
	cout<<"Las transacciones de Carla son \n"<<	users.find("transactions","Carla");
	return 0;
}












// int main(int argc, char * const argv[])
// {
// 	// string str = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
// 	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
// 	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

// 	if (iss->bad()) {
// 		cerr << "cannot read from input stream."
// 		     << endl;
// 		exit(1);
// 	}

// 	// block block0(str, difficulty, iss);

// 	// str = block0.getBlockAsString();
	
// 	// if (oss->bad()) {
// 	// 	cerr << "cannot write to output stream."
// 	// 	     << endl;
// 	// 	exit(1);
// 	// }
// 	// *oss << str;
	
// 	string aux, aux1, aux2;
// 	Array <string> arr;
// 	p_func cmd;
// 	int num_param=0;

// 	cout << "Empieza el codigo" << endl;
// 	getline(*iss, aux1, ' ');
// 	cmd = dictCmds(aux1, num_param);
// 	getline(*iss, aux2, '\n');
// 	arr = parseCmdArgs(aux2, num_param);

// 	aux = cmd(arr);
// 	*oss << aux << endl;
// }