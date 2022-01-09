#include "libs/stdafx.h"
#include <string>
#include <omp.h>

int _tmain(int argc, _TCHAR* ARGV[]) 
{
	int mynum;
	int tcount;
	int max = 1000;
	int t = 2;
	double a = 0, b = 10;
	double h = (b - a) / max;
	double s = 0;

#pragma omp parallel num_threads(t) private (mynum) reduction (+:s)
	{
		mynum = omp_get_thread_num();

#pragma omp for
		for (int i = 0; i < max; i++)
			s += (a + i * h) * (a + i * h);
	}
	printf("s = %.20f\n", s * h);
}