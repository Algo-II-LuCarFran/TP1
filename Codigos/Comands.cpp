#include "block\Array.h"
#include <sstream>

using namespace std;
// VER CMDLINE. TIENE UNA IMPLEMENTACION DE PUNTEROS A FUNCION
Array <string> parseCmdArg(string str, size_t N)//funcion para verificar la correcta escritura de los argumentos, 
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


int main()
{
    string str="hola como  estas";

    Array <string> prt = parseCmdArg(str, 0);

    cout << prt;

}