#include <iostream>
#include "libs/stdafx.h"
#include "libs/pthread.h"
#include <windows.h>

#pragma comment(lib, "pthreadVCE2.lib")

#define MAX 10000
#define THREADS 2

using namespace std;

double *psum;
double a = 4, b = 8;
double h = (b - a) / MAX;

void* pthread(void* arg)
{
    int tpart = *(int*)arg, check;
	for (int i = tpart * (MAX / THREADS); i < (tpart + 1) * (MAX / THREADS); i++)
	{
		psum[tpart] += (a + i * h);
		check = i;
	}
	if ((tpart + 1  == THREADS) && ((MAX % THREADS) != 0))
		for (int i = (tpart + 1) * (MAX / THREADS); i < MAX; i++)
			psum[tpart] += (a + i * h);
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{   
	setlocale(LC_ALL, "Russian");
	pthread_t t[THREADS];
	int n[THREADS]; 
	double sum = 0;
	psum = new double[THREADS];
	printf("Метод левых прямоугольников");
	printf("\na = %.1f,  b = %.1f \nh = %.4f \n ", a, b, h);
	for (int i = 0; i < THREADS; i++)
	{
		n[i] = i;
		psum[i] = 0;
		pthread_create(&t[i], NULL, pthread, &n[i]);
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(t[i], NULL); 
	for (int i = 0; i < THREADS; i++)
		sum += psum[i];
	printf("\nСумма равняется: %.3f \n", h * sum);
	delete[] psum;
    return 0;
}