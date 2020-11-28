#include <iostream>
#include "Lista.h"
#include "Array.h"
using namespace std;

int main()
{
    list <int> L;
    L.append(1);
    L.append(2);
    L.append(3);
    cout << L;    
    list <string> L2;
    L2.append("HOla");
    L2.append("Carla");
    L2.append("Chau");
    cout << L2;
    return 0;
}