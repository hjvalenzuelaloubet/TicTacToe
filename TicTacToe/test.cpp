//test.cpp

//Importing the inbuild libraries in CPP
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
using namespace std;

void main()
{
	for (int ii = 0; ii < 10; ii++)
	{
		cout << ii;
		sleep(2);
		system("cls");
	}
}