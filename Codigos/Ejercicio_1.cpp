#include <iostream>
#include "Lista.h"
#include "main.h" //ESTO NO VA
// #include "Array.h"
// #include "block.h"
#include <string.h>
#include <cstring>
using namespace std;

// void testMultipleInstantiationArray()
// {
//     Array<int> primero(2);
//     primero[0]=1;
//     primero[1]=2;
//     cout<<primero[0]<<endl<<primero[1]<<endl;
//     Array<string> segundo(2);
//     segundo[0]="Hola";
//     segundo[1]="Mundo";
//     cout<<segundo[0]<<endl<<segundo[1]<<endl;
// }

// void testInsertStringList()
// {
//     list <string> L;
//     L.insert("Hola");
//     L.insert("Mundo");
//     cout<<L<<endl:
// }

// void testAppendIntList()
// {
//     list <int> L;
//     L.append(1);
//     L.append(2);
//     L.append(3); 
//     cout<<L<<endl;
// }

// void testListFindInt()
// {
//     list <int> L;
//     int valor_1=9;
//     int valor_2=2;
//     int valor_3=19;
//     int valor_4=70;

//     int b;
//     int c;
//     int e;
//     int f;
    
//     L.append(1);
//     L.append(valor_1); //Agrego 9
//     L.append(valor_2); //Agrego 2
//     L.append(valor_3); //Agrego 19
//     L.append(valor_4); //Agrego 70
//     L.append(5); //Agrego 70
//     L.append(7); //Agrego 70
//     L.append(98); //Agrego 70
//     L.append(107); //Agrego 70
//     L.append(-100); //Agrego 70
//     L.append(900); //Agrego 70
//     L.append(1582); //Agrego 70

//     b=L.find(valor_1); //Busco 9
//     c=L.find(valor_2); //Busco 9
//     e=L.find(valor_3); //Busco 9
//     f=L.find(valor_4); //Busco 9
    
//     cout<<"El valor "<< b <<" esta en la lista"<<endl;
//     cout<<"El valor "<< c <<" esta en la lista"<<endl;
//     cout<<"El valor "<< e <<" esta en la lista"<<endl;
//     cout<<"El valor "<< f <<" esta en la lista"<<endl;
// }

// void testGetNode()
// {
//     list <string> L;
//     L.append("Carla");
//     L.append("Carlashiam");
//     L.append("Franashiam");
//     string a,b;
//     a=L.getFirstNode();
//     b=L.getLastNode();
//     cout<<L<<endl;
//     cout<<"El primer y ultimo dato son: "<<endl;
//     cout<<a<<"\n"<<b<<endl;
// }
    
// void testGetNode()
// {
//     list <block> L;
//     block bloque_1,bloque_2;

//     block bloque_3,bloque_4;
//     L.append(bloque_1);
//     L.append(bloque_2);

//     a=L.getFirstNode();
//     b=L.getLastNode();
//     cout<<L<<endl;
//     cout<<"El primer y ultimo dato son: "<<endl;
//     cout<<a<<"\n"<<b<<endl;
// }

// void testListFindwithin()
// {
    
// }

// void testGetSubArray()
// {
//     Array <int> arr(7);
//     arr[0]=1;
//     arr[1]=2;
//     arr[2]=3;
//     arr[3]=4;
//     arr[4]=5;
//     arr[5]=6;
//     arr[6]=7;

//     Array <int> sub_arr= arr.getSubArray(3,arr.getSize()+1);
//     cout<<"El arreglo original es \n"<<arr<<endl;
//     cout<<"El subarreglo queda \n"<<sub_arr<<endl;
// }
// void testDoubleConvertion()
// {
//     string str;
//     double num,result;

//     num= 253.48;
//     str=to_string(num);
//     result=stod(str);

//     cout<<"Este es el double original \n"<<num<<endl;
//     cout<<"Esta es la conversion a string \n"<<str<<endl;
//     cout<<"Este es el double convertido \n"<<result<<endl;

// }


void testFinder()
{
    string result;
    user aux;
    aux.balance=256.75;
    aux.name="Fran";
    users.append(aux);
    result=users.find("balance","Fran");
    cout<<"El resultado es: \n"<< result<< endl;

}

int main()
{
    return 0;
}