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
#include "Lista.h"

using namespace std;


// static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
// static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
// static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
// static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)


// agregar una variable global lista algochain static list<block> algochain;
// static block mempool();

// string cmdLoad(Array <string> args);
// bool setAlgochainFromFile( istream *iss);
// string cmdSave(Array <string> args);


// list <block> algochain;

// int main()
// {
// 	size_t a=9;
// 	a=9-8;
// 	Array <string> args(1);
// 	args[0]="algochain.txt";
// 	string str = cmdLoad(args);
// 	cout << str << endl;
	
// 	args[0]="algochainout.txt";
// 	cout<< cmdSave(args)<<endl;
// }

// string cmdSave(Array <string> args)
// {
// 	ofs.open(args[0].c_str(), ios::out);
// 	oss = &ofs;
// 	if (!oss->good()) 
// 	{
// 		cerr << "cannot open "
// 		     << args[0]
// 		     << "."
// 		     << endl;
// 		exit(1);		// EXIT: Terminación del programa en su totalidad
// 	}
// 	else if (oss->bad()) 
// 	{
// 		cerr << "cannot write to output stream."
// 		     << endl;
// 		exit(1);
// 	}
// 	*oss << algochain;
// 	return "Carga realizada con exito";
// }

// string cmdLoad(Array <string> args)
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
// 	if(setAlgochainFromFile(iss)==false)
// 	{
// 		cerr << "ERROR: no se pudo cargar el archivo "
// 		<< endl;
// 		exit(1);
// 	}
// 	block aux ;
// 	aux = algochain.getLastNode();
// 	return sha256(sha256(aux.getBlockAsString()));
// }


// bool setAlgochainFromFile( istream *iss)
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