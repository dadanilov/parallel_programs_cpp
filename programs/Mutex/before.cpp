#include <iostream>
#include "libs/stdafx.h"
#include "libs/pthread.h"
#include <windows.h>

#pragma comment(lib, "pthreadVCE2.lib")


#define THREADS 2

using namespace std;

void* pthread(void* arg)
{
    int tpart = *(int*)arg;
	for (int i = 0; i < 100; i++)
		printf("%d", tpart);
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{   
	setlocale(LC_ALL, "Russian");
	pthread_t t[THREADS];
	int n[THREADS]; 
	for (int i = 0; i < THREADS; i++)
	{
		n[i] = i;
		pthread_create(&t[i], NULL, pthread, &n[i]);
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(t[i], NULL); 
    return 0;
}