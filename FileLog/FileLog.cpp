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

class InputHandler
{
	private:
	public:
		string active_file_name;
		void input()
		{
			string text;
			cout<<"Log: "<<endl;
			ofstream active_file;
			active_file.open(active_file_name,ios::app);
			cin.clear();
			cin.sync();
			getline(cin,text);
			if(text=="\"Quit\"")
			{
				exit(0);
			}
			active_file<<text<<endl;
			active_file.close();
		}
};

class Logger
{
	
	private:
		clock_t t_initial=0,t_elapsed=0, t_last_log_time=0;
	public:
		int		frequency;
		int		max_file_count;
		string			active_file_name;
		queue<string>	active_file_names;
	


		void log(InputHandler& inputh)
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
				ofstream myfile;
				myfile.open(buffer);
				myfile.close();
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

class JsonHandler
{
	private:
	public:
		int	frequency;
		int	max_file_count;
		string		log_type;
		map<string,int> log_type_to_int{	{"daily"	,	60 * 60 * 24},
											{"hourly"	,	60 * 60		},
											{"minutely"	,	60			},
											{"secondly"	,	1			}	};
	void GetData()
	{
		cout << "Enter the frequency: "<<endl;
        cin >> frequency;
		goto a;



		a:
        cout << "Enter the max file count: "<<endl;
        cin >> max_file_count;
        cout << "Enter the log type:"<<endl;
		cin.clear();
		cin.sync();
        getline(cin,log_type);

	}
	void ReadData(Logger& _log)
	{	
		_log.frequency=log_type_to_int[log_type] * frequency;
		
		_log.max_file_count=max_file_count + 1;
	}

};

int main()
{

	JsonHandler jsonhandler;
	Logger logger;
	InputHandler inputhandler;
	
	jsonhandler.GetData();
	jsonhandler.ReadData(logger);

	while(1)
	{
		logger.log(inputhandler);
		inputhandler.input();
	}

 	return 0;
}