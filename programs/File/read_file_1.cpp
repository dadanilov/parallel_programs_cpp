#include <iostream>
#include <fstream>
#include "libs/stdafx.h"
#include "libs/pthread.h"
#include <windows.h>

#pragma comment(lib, "pthreadVCE2.lib")

#define THREADS 6

using namespace std;
fstream F;
string* line;
pthread_mutex_t m;
pthread_mutexattr_t attr;

void* pthread(void* arg)
{
	pthread_mutex_lock(&m);
	int tpart = *(int*)arg, check;
	F >> line[tpart];
	pthread_mutex_unlock(&m);
	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	pthread_t t[THREADS];
	int n[THREADS];
	line = new std::string[6];
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m, &attr);
	pthread_mutexattr_destroy(&attr);
	F.open("text.txt");
	while (!F.eof())
	{
		for (int i = 0; i < THREADS; i++)
		{
			n[i] = i;
			
			pthread_create(&t[i], NULL, pthread, &n[i]);
		}
	}
	for (int i = 0; i < THREADS; i++)
		pthread_join(t[i], NULL);
	for (int i = 0; i < 6; i++)
		cout << line[i];
	F.close();
	delete[] line;
	return 0;
}