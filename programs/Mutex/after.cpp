#include <iostream>
#include "libs/stdafx.h"
#include "libs/pthread.h"
#include <windows.h>

#pragma comment(lib, "pthreadVCE2.lib")


#define THREADS 2

using namespace std;

pthread_mutex_t m;
pthread_mutexattr_t attr;

void* pthread(void* arg)
{
	pthread_mutex_lock(&m);
    int tpart = *(int*)arg;
	for (int i = 0; i < 100; i++)
		printf("%d", tpart);
	pthread_mutex_unlock(&m);
	return NULL;	
}

int _tmain(int argc, _TCHAR* argv[])
{   
	setlocale(LC_ALL, "Russian");
	pthread_t t[THREADS];
	int n[THREADS]; 
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m, &attr);
	pthread_mutexattr_destroy(&attr);
	for (int i = 0; i < THREADS; i++)
	{
		n[i] = i;
		pthread_create(&t[i], NULL, pthread, &n[i]);
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(t[i], NULL); 
    return 0;
}