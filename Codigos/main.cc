#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

#include "cmdline.h"
#include "sha256.h"
#include "block.h"
#include "dictionary.h"
#include "main.h"
#include "global.h"

using namespace std;
// agregar una variable global lista algochain static list<block> algochain;
// static block mempool();

int main(int argc, char * const argv[])
{
	// string str = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

	if (iss->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}

	// block block0(str, difficulty, iss);

	// str = block0.getBlockAsString();
	
	// if (oss->bad()) {
	// 	cerr << "cannot write to output stream."
	// 	     << endl;
	// 	exit(1);
	// }
	// *oss << str;
	
	string aux, aux1, aux2;
	Array <string> arr;
	p_func cmd;
	int num_param=0;

	cout << "Empieza el codigo" << endl;
	getline(*iss, aux1, ' ');
	cmd = dictCmds(aux1, num_param);
	getline(*iss, aux2, '\n');
	arr = parseCmdArgs(aux2, 3);
	arr = parseCmdArgs(aux2, num_param);

	aux = cmd(arr);
	*oss << aux << endl;
}