/*
The program has a failure; that is, while it's waiting for the inputs from the user, 
it stops and is still waiting for the inputs. It does not create any log file. Otherwise, 
if there is at least one input per the setted period, the code is working properly.
*/
/*
The libraries and the definition given below were used, but when I tried to run the code without them it also
worked. I wanted to let them in the comment line in any case.
#define _CRT_SECURE_NO_WARNINGS
#include <filesystem>
#include <string>
#include <cstring>
#include <time.h>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <ratio>
#include <map>
*/
#include <iostream>
#include <fstream>
#include <queue>
#include "json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
using namespace chrono;

class InputHandler											//Class for using to take inputs
{
	private:
	public:
		string 			active_file_name;
		string			text;
		void input()										// Input function
		{
			
			cout<<"Log: "<<endl;
			ofstream active_file;
			active_file.open(active_file_name,ios::app);
			cin.clear();									// Getline() function didn't work without clear()
			cin.sync();										//and sync() functions
			getline(cin,text);
			if(text=="\"Quit\"")							// Typing "Quit" for shut down the program
			{
				exit(0);
			}
			active_file<<text<<endl;
			active_file.close();
		}
};

class Logger												// Class for Logging operation
{
	
	private:
		clock_t t_initial=0,t_elapsed=0, t_last_log_time=0;
	public:
		int				frequency;
		int				max_file_count;
		string			active_file_name;
		queue<string>	active_file_names;
		time_t 			rawtime;
		struct tm* 		ptm;
		char 			buffer[80];

		void log(InputHandler& inputh)						// Actual logger function. It takes logs 
		{													//from the InputHandler class in main function
			t_elapsed = (clock() - t_last_log_time)/1000;
			if(t_last_log_time==0 || t_elapsed>=frequency)
			{
				// Code to take UTC time as .txt file name
				time(&rawtime);
				ptm = localtime(&rawtime);
				strftime(buffer, 80, "%Y-%m-%dT%H-%M-%SZ.txt", ptm);
				ofstream myfile;
				myfile.open(buffer);
				myfile.close();
				// Push and pop
				active_file_names.push(buffer);
				inputh.active_file_name=buffer;
				t_last_log_time=clock();
				if(active_file_names.size()>=max_file_count)
				{
					filesystem::remove(active_file_names.front());
					active_file_names.pop();
				}
			}
		}
};

class JsonHandler											// Class for reading data from configuration file
{
	private:
	public:
		int 			i=0;
		int				frequency;
		int				max_file_count;
		string			log_type;
		map<string,int> log_type_to_int{	{"daily"	,	60 * 60 * 24},		// I used map to change strings
											{"hourly"	,	60 * 60		},		//to the integers
											{"minutely"	,	60			},
											{"secondly"	,	1			}	};
							
		void GetData()															// GetData function reads the
		{																		//data from the "config.json"
			std::ifstream f("config.json");										//file
			json data = json::parse(f);
			for (json::iterator it = data.begin(); it != data.end(); ++it) 
			{
				if(i==0)
					frequency=*it;
				if(i==1)
					log_type=*it;
				else
					max_file_count=*it;
				i++;
			}
		}
		void ConvertData(Logger& _log)								// ConvertData function makes the 
		{															//calculation for the period of the
			_log.frequency=log_type_to_int[log_type] * frequency;	//logging
			_log.max_file_count=max_file_count + 1;					
		}

};

int main()													// Main function
{	
	JsonHandler jsonhandler;
	Logger logger;
	InputHandler inputhandler;

	jsonhandler.GetData();
	jsonhandler.ConvertData(logger);
	while(1)
	{
		logger.log(inputhandler);
		inputhandler.input();
	}
 	return 0;
}