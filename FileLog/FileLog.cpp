// FileLog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>


using namespace std;

class Log {
public:
	void Daily() {

		time_t rawtime;
		struct tm* ptm;

		time(&rawtime);

		ptm = localtime(&rawtime);

		char buffer[80];
		char buffer2[80];
		strftime(buffer, 80, "%Y-%m-%dT%H-%M-%SZ.txt", ptm);

		ofstream myfile(buffer);
		strftime(buffer2, 80, "%c.", ptm);
		myfile << "Daily log : "<< buffer2;
		myfile.close();


	}
};



int main()
{
	Log log;
	log.Daily();
	
	return 0;
}

// Dosya adý UTC time formatta istendi ama dosya isminde ":" kullanamadýðým için - kullandým.


