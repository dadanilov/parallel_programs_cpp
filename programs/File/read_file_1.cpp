#include <iostream>
#include <fstream>
#include "libs/stdafx.h"
#include "libs/pthread.h"
#include <windows.h>

#pragma comment(lib, "pthreadVCE2.lib")

#define THREADS 4

using namespace std;
fstream F;

pthread_mutex_t m, m1;
pthread_mutexattr_t attr;

void* pthread(void* arg)
{
	pthread_mutex_lock(&m);
	int tpart = *(int*)arg, check;
	while (!F.eof())
	{
		string l;
		F >> l;
		pthread_mutex_unlock(&m);
		pthread_mutex_lock(&m1);
		cout << "Номер потока = " << tpart << " - " << l << endl;
		pthread_mutex_unlock(&m1);
		pthread_mutex_lock(&m);
	}
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	pthread_t t[THREADS];
	int n[THREADS];
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m, &attr);
	pthread_mutex_init(&m1, &attr);
	pthread_mutexattr_destroy(&attr);
	F.open("text.txt");
	for (int i = 0; i < THREADS; i++)
	{
		n[i] = i;	
		pthread_create(&t[i], NULL, pthread, &n[i]);
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(t[i], NULL);
	F.close();
	return 0;
}