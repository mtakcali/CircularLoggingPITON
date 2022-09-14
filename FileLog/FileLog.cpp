// FileLog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <Windows.h>
#include <queue>

using namespace std;

class Log {
public:
	void logLoop(int frequency,int fileCount, string logType) {
		int cnt = 0;
		
		
		while (true) {
			if (cnt % frequency == 0) {
			
			}
			cnt++;
			

		}

	}
	string log() {


		time_t rawtime;
		struct tm* ptm;
		time(&rawtime);
		ptm = localtime(&rawtime);
		char buffer[80];
		strftime(buffer, 80, "%Y-%m-%dT%H-%M-%SZ.txt", ptm);

		ofstream myfile;
		myfile.open(buffer);
		myfile << "sa" << endl;
		myfile.close();

		return buffer;
	}
	
};

int main()
{
	char* filename;

	Log logger;
	queue<string> fileNames;
	string nameoffile=logger.log();
	cout << "Burasi_calisti "<< nameoffile<<endl;
	Sleep(5000);
	cout << "Uyandim " << endl;

	if (filesystem::remove(nameoffile)) {
		cout << "remove'landi " << endl;
	}
	else cout << "Basarisiz";
	return 0;
}




