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

using namespace std;

// agregar una variable global lista algochain static list<block> algochain;
// static block mempool();






int main()
{
    // Array<int> primero(2);
    // primero[0]=1;
    // primero[1]=2;
    // cout<<primero[0]<<endl<<primero[1]<<endl;
    // Array<string> segundo(2);
    // segundo[0]="Hola";
    // segundo[1]="Mundo";
    // cout<<segundo[0]<<endl<<segundo[1]<<endl;

    // list <int> L1;
    // L1.insert(1);
    // L1.insert(2);
    // L1.insert(3); 
    // cout<<L1;
    // // list <int> L2;
    // // L2.append(1);
    // // L2.append(2);
    // // L2.append(3); 
    // // cout<<L2;
    // list <string> L3;
    // L3.insert("Hola");
    // L3.insert("Mundo");
    // cout<<L3;

    // list <string> L4;
    // L4.insert("Carla");
    // L4.insert("se");
    // L4.insert("la");
    // L4.insert("come");
    // cout<<L4;
    
	user fran("fran\n125.75\n\0");
	cout<<fran<<endl;
	users.append(fran);
	string result;
	result= users.findAttr("balance","fran");
	cout<<result<<endl;
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