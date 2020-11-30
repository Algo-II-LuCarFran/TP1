#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

void funcion(istream * iss);

int main()
{
    string arg ="algochain.txt";
    ifs.open(arg.c_str(), ios::in);
	iss = &ifs;
    string str;
    getline(*iss, str, '\n');
    cout << "es mi str " << str << endl;
    funcion(iss);
    getline(*iss, str, '\n');
    cout << "lo que queda en iss despues de iss" << str << endl;

}

void funcion(istream * iss)
{
    string str;
    getline(*iss, str, '\n');
    
    cout << "es mi str en funcion " << str << endl;
    
}