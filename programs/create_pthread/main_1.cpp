#include "libs/stdafx.h"
#include "libs/pthread.h"
#include <windows.h>

#pragma comment(lib, "pthreadVCE2.lib")

#define THREADS 10

void* pthread(void* arg)
{
    int tpart = *(int*)arg, check;
	printf("pthread_%d ", tpart);
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{   
	pthread_t t[THREADS];
	int n[THREADS]; 
	for (int i = 0; i < THREADS; i++)
	{
		n[i] = i;
		pthread_create(&t[i], NULL, pthread, &n[i]);
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(t[i], NULL); 
	printf("\n");
    return 0;
}