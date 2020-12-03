#include <iostream>
#include "Array.h"
#include "sha256.h"
#include "sha256.cpp"
using namespace std;
Array<string> _merkle_hash(Array<string>& hashes, size_t n);
string merkle_hash(Array<string>& hashes, size_t n);
int main()
{
    Array<string> hashes(3);
    
    hashes[0] = "a225a1d1a31ea0d7eca83bcfe582f915539f926526634a4a8e234a072b2cec23";
    hashes[1] = "b2d04d58d202b5a4a7b74bc06dc86d663127518cfe9888ca0bb0e1a5d51e6f19";
    hashes[2] = "b96c4732b691beb72b3a8f28c59897bd58f618dbac1c3b0119bcea85ada0212f";

    cout << merkle_hash(hashes, 3) << endl;
    return 0;
}

string merkle_hash(Array<string>& hashes, size_t n)
{
	return _merkle_hash(hashes, n)[0];
}
Array<string> _merkle_hash(Array<string>& hashes, size_t n)
{
	if(n == 1)
		return hashes;
	
	if(n%2 == 1)
	{
		if (hashes.getSize() <= n)
		{
			hashes.ArrayRedim(n+1);
		}
		hashes[n] = hashes[n-1];
		n++;
	}
	Array<string> result(n/2);
	size_t j;
	for (size_t i = 0, j = 0; i < n/2, j < n; i++, j+=2)
	{
		result[i] = sha256(sha256(hashes[j] + hashes[j+1]));
	}
	return _merkle_hash(result, n/2);
}