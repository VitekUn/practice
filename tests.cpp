#include <iostream>
#include "tests.h"

int check (int* data, int n) 
{
	double prev = data[0];

	for (int i = 0; i < n; i++)  {
		if (data[i] < prev)
			return -1;

		prev = data[i];
	}

	return 0;
}