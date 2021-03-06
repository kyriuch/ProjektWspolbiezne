// ProjektProgramowanieRownolegle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <omp.h>
#include <chrono>

int main()
{
	double integral = 0;
	double step = 0.0001;
	int steps = 2;
	double roznica = 1;
	double previousPole = (exp((-step) * sqrt(10))) / (1 + (step * step));
	double pole;
	int counter = 0;
	int k;
	
	omp_set_nested(1);

	auto start = std::chrono::high_resolution_clock::now();

#pragma omp parallel for private(k, previousPole, pole) firstprivate(counter, steps, roznica, integral) shared(step)
	for (k = 1; k <= 100; k++) {
		previousPole = (exp((-step) * sqrt(k))) / (1 + (step * step));

		while (counter < 10)
		{
			pole = (exp(-(step * steps) * sqrt(k))) / (1 + ((step * steps) * (step * steps)));

			if (previousPole - pole == roznica)
			{
				counter++;
			}
			else
			{
				counter = 0;
			}

			roznica = previousPole - pole;
			previousPole = pole;
			steps++;
		}

		int i;

#pragma omp parallel for private(i) shared(steps, step, k) reduction(+:integral)
		for (i = 1; i <= steps; i++) {
			integral += (exp(-(i * step) * sqrt(k))) / (1 + ((i * step) * (i * step)));
		}

		integral *= step;

		printf("Calka dla %i: %f\n", k, integral);
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> firstElapsed = end - start;

    return 0;
}

