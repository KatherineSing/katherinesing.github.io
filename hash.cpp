#include "hash.h"
#include <iostream>
#include <math.h>
using namespace std;

unsigned long long calculateHash(string mystring)
{
  /* add your code here */
	//conv to ints

	unsigned long long total = 0;
	unsigned long long currentpow = 1;

	for (unsigned int i = 0; i < mystring.size(); i++)
	{	
		total +=  currentpow * ((int)mystring[mystring.size() - 1 -i]);
		currentpow = currentpow * 128;

	}
	
	unsigned int encrIn[4];

	for(int i = 3; i >= 0; i--)
	{
		if (total!=0)
		{
			encrIn[i] = total%65521;
			total = total/65521;
		}
		else encrIn[i] = 0;
	}

	unsigned long long encryptedResult = (45912 * encrIn[0] + 35511 
		* encrIn[1] + 65169 * encrIn[2] + 4625 * encrIn[3]) % 65521;

	return encryptedResult;
}

