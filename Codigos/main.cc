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

// string cmdLoad(Array <string> args, list <block> algochain);
// bool setAlgochainFromFile( istream *iss, list <block> &algochain);


int main(int argc, char * const argv[])
{
	int a=9;
	
	Array <string> args(1);
	args[0]="algochain.txt";
	list <block> algochain;
	string str = cmdLoad(args,algochain);
	cout << str << endl;
}



// string cmdLoad(Array <string> args, list <block> algochain)
// {
// 	ifs.open(args[0].c_str(), ios::in);
// 	iss = &ifs;
// 	if (!iss->good()) {
// 	cerr << "cannot open "
// 			<< args[0]
// 			<< "."
// 			<< endl;
// 	exit(1);
// 	}
// 	if(algochain.empty()==false)//la vacio si es necesario
// 	{
// 		list <block> empty_list;
// 		algochain = empty_list;//
// 	}
// 	if(setAlgochainFromFile(iss,algochain)==false)
// 	{
// 		cerr << "ERROR: no se pudo cargar el archivo "
// 		<< endl;
// 		exit(1);
// 	}
// 	block aux ;
// 	aux = algochain.getLastNode();
// 	cout << "getie el ultimo nodo " <<aux.getBlockAsString() << endl;
// 	return sha256(sha256(aux.getBlockAsString()));
// }


// bool setAlgochainFromFile( istream *iss, list <block> &algochain)
// {
// 	block block_aux, block_empty;
// 	string str,str_aux;
// 	getline(*iss, str, '\n');	
// 	size_t i = 0, aux = 0;
// 	hdr header_aux;
// 	size_t diff, nonce;
// 	bdy body_aux;
// 	while (str!="")
// 	{
// 		//seteo el header
// 		//validacion
// 		header_aux.setPrevBlock(str);
// 		getline(*iss, str, '\n');
// 		//validacion
// 		header_aux.setTxnsHash(str);
// 		getline(*iss, str, '\n');
// 		diff = stoi(str);
// 		header_aux.setBits(diff);
// 		getline(*iss, str, '\n');
// 		nonce = stoi(str);
// 		header_aux.setNonce(nonce);


// 		block_aux.setHeader(header_aux);
// 		//seteo el body
// 		str_aux=block_aux.setBody(iss);
		
// 		if(isHash(str_aux)==true)
// 		{
// 			str=str_aux;
// 			algochain.append(block_aux);
// 			break;
// 		}
// 		else if (str_aux=="")
// 		{	
// 			str=str_aux;
// 			algochain.append(block_aux);
// 			break;
// 		}
// 		else if (str_aux=="OK")
// 		{
// 			algochain.append(block_aux);
// 			getline(*iss, str, '\n');			
// 			continue;
// 		}
// 		else
// 		{
// 			return false;
// 		}
// 	}
// 	return true;
// }















	// // string str = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
	// cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver línea 51 main.cc
	// cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline

	// if (iss->bad()) {
	// 	cerr << "cannot read from input stream."
	// 	     << endl;
	// 	exit(1);
	// }

	// // block block0(str, difficulty, iss);

	// // str = block0.getBlockAsString();
	
	// // if (oss->bad()) {
	// // 	cerr << "cannot write to output stream."
	// // 	     << endl;
	// // 	exit(1);
	// // }
	// // *oss << str;
	
	// string aux, aux1, aux2;
	// Array <string> arr;
	// p_func cmd;
	// int num_param=0;

	// cout << "Empieza el codigo" << endl;
	// getline(*iss, aux1, ' ');
	// cmd = dictCmds(aux1, num_param);
	// getline(*iss, aux2, '\n');
	// arr = parseCmdArgs(aux2, num_param);

	// aux = cmd(arr);
	// *oss << aux << endl;
// }