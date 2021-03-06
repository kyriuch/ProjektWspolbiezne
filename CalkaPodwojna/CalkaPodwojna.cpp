// CalkaPodwojna.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>

int main()
{
	double integral = 0;
	double step = 0.00001;
	int i;

#pragma omp parallel for private(i) shared(step, integral)
	for (i = 1; i <= 100000; i++) {
		int j;

#pragma omp parallel for private(j) shared(i) reduction(+:integral)
		for (j = 1; j <= 100000; j++) {
			integral += log(1 + exp(-(((step * i) * (step * i)) + ((step * j) * (step * j)))));
		}

		printf("Skonczylem %i\n", i);
	}

	integral *= step * step;

	printf("Wynik %f", integral);

    return 0;
}

