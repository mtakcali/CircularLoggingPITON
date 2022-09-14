#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <Windows.h>
#include <queue>
#include <chrono>
#include <ctime>
#include <ratio>
#include <map>

using namespace std;
using namespace chrono;

class Logger
{
	private:
	clock_t t_initial=0,t_elapsed=0, t_last_log_time=0;
	

	public:
		uint32_t		frequency;
		uint16_t		max_file_count;
		string			active_file_name;
		queue<string>	active_file_names;
	


		void log(InputHandler inputh)
		{
			t_elapsed = (clock() - t_last_log_time)/1000;
			if(t_last_log_time==0 || t_elapsed>=frequency)
			{
				//code to take UTC time.
				time_t rawtime;
				struct tm* ptm;
				time(&rawtime);
				ptm = localtime(&rawtime);
				char buffer[80];
				strftime(buffer, 80, "%Y-%m-%dT%H-%M-%SZ.txt", ptm);
				//
				
				inputh.active_file_name=buffer;

				t_last_log_time=clock();
			}


		



		}
};
class InputHandler
{
	private:
	public:
	string active_file_name;

};
class JsonHandler
{
	private:
	public:
	uint16_t	frequency;
	uint16_t	max_file_count;
	string		log_type;
	map<string,uint16_t> log_type_to_int{	{"daily"	,	60*60*24},
											{"hourly"	,	60*60	},
											{"minutely"	,	60		},
											{"secondly"	,	1		}};

};

int main()
{
	Logger logger;
	InputHandler inputhandler;
	logger.log(inputhandler);
 	return 0;
}