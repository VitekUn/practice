#include <iostream>
#include <iomanip>
#include <omp.h>

#define N 500000000

double sum (double *data, int low, int high)
{
	if (low == high)
		return data[low];

	int mid = (low + high) / 2;

	return sum(data, low, mid) + sum(data, mid + 1, high);
}

int main (int argc, char* argv[]) 
{
	double ttotal = omp_get_wtime(), tinit = -omp_get_wtime(), tcompute = 0;
	double* data = (double*) std::malloc (N * sizeof(double));
	double result;

	for (int i = 0; i < N; i++)
		data[i] = i;

	tinit += omp_get_wtime();

	result = sum(data, 0, N-1);

	ttotal = omp_get_wtime() - ttotal;
	tcompute = ttotal - tinit;

	std::cout << "Result: " << result << std::endl;
	std::cout << std::setprecision(6) << std::fixed;
	std::cout << "#Elapsed time (sec): ttotal " << ttotal << ", tinit " << tinit << ", tcompute " << tcompute;
	std::cout << std::endl;

	std::free(data);

	return 0;
}