#include <iostream>
#include <omp.h>
#include <iomanip>
#include "tests.h"

void partition(int* data, int& i, int& j, int low, int high) 
{
	i = low, j = high;
	int pivot = data[(low + high) / 2];
	
	do {
		while (data[i] < pivot) i++;
		while (data[j] > pivot) j--;
		
		if (i <= j) {
			std::swap(data[i], data[j]);
			i++;
			j--;
		}
	} while (i <= j);
}

void quicksort(int* data, int low, int high) 
{
	int i, j;
	
	partition(data, i, j, low, high);
	
	if (low < j)
		quicksort(data, low, j);
	if (i < high)
		quicksort(data, i, high);
}

int main (int argc, char** argv) 
{
	double ttotal = omp_get_wtime(), tinit = -omp_get_wtime(), tcompute = 0;
	
	int n = (argc > 1) ? atoi(argv[1]) : 1000000;
	int* data = (int*) std::malloc (n * sizeof(int));

	srand(time(NULL));

	for (int i = 0; i < n; i++) 
		data[i] = std::rand();

	tinit += omp_get_wtime();

	quicksort(data, 0, n - 1);

	ttotal = omp_get_wtime() - ttotal;
	tcompute = ttotal - tinit;

	if (argc > 2 && atoi(argv[2]) == 1) {
		std::cout << std::endl;
		if (check(data, n) == 0)
			std::cout << "--- Sorting was successful ---" << std::endl;
		else 
			std::cout << "--- Sorting failed --- " << std::endl;
		std::cout << std::endl;
	}

	std::cout << std::setprecision(6) << std::fixed;
	std::cout << "#Elapsed time (sec): ttotal " << ttotal << ", tinit " << tinit << ", tcompute " << tcompute;
	std::cout << std::endl;

	std::free(data);

	return 0;
}