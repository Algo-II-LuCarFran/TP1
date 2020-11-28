#include <iostream>
#include "Lista.h"
#include "Array.h"
using namespace std;
void testMultipleInstantiationArray()
{
    Array<int> primero(2);
    primero[0]=1;
    primero[1]=2;
    cout<<primero[0]<<endl<<primero[1]<<endl;
    Array<string> segundo(2);
    segundo[0]="Hola";
    segundo[1]="Mundo";
    cout<<segundo[0]<<endl<<segundo[1]<<endl;
}

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

void testListFindInt()
{
    list <int> L;
    int a=9;
    L.append(1);
    L.append(2);
    L.append(3); 
    L.append(a);
    cout<<L.find(a)<<endl;
}

int main()
{
    testListFindInt();
    
    return 0;
}