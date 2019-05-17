#include <iostream>
#include <omp.h>
#include <cmath>
#include <iomanip>

#define N 500000000

double sum (double* data, int low, int high)
{
	if (low == high)
		return data[low];

	double sum_left, sum_right;
	int mid = (low + high) / 2;

	if (omp_get_active_level() >= omp_get_max_active_levels())
		return sum(data, low, mid) + sum(data, mid + 1, high);

	#pragma omp parallel num_threads(2)
	{
		unsigned int tid = omp_get_thread_num();
		if (tid == 0) 
			sum_left = sum(data, low, mid);
		else if (tid == 1)
			sum_right = sum(data, mid+1, high);
	}

	return sum_left + sum_right;
}

int main (int argc, char** argv) 
{
	double ttotal = omp_get_wtime(), tinit = -omp_get_wtime(), tcompute = 0;
	double* data = (double*) std::malloc (N * sizeof(double));
	double result;

	omp_set_nested(1);
	omp_set_max_active_levels(log2(8));

	for (int i = 0; i < N; i++)
		data[i] = i;

	tinit += omp_get_wtime();

	result = sum(data, 0, N);

	ttotal = omp_get_wtime() - ttotal;
	tcompute = ttotal - tinit;

	std::cout << "Result: " << result << std::endl;
	std::cout << std::setprecision(6) << std::fixed;
	std::cout << "#Elapsed time (sec): ttotal " << ttotal << ", tinit " << tinit << ", tcompute " << tcompute;
	std::cout << std::endl;

	std::free(data);

	return 0;
}