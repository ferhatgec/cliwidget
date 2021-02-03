/* MIT License
#
# Copyright (c) 2020 Ferhat Geçdoğan All Rights Reserved.
# Distributed under the terms of the MIT License.
#
# */

#ifndef CLI_WIDGET_HPP
#define CLI_WIDGET_HPP


#include <iostream>
#include <string> 
#include <ctime>
#include <cstdlib>


/* Fegeya CLIWidget library
   * Easy-to-use CLI widgets.
   
   * Supported widget(s):
      - Clock. 24h | 12h
      - Branch git | mercurial
*/

#define PUT(str) std::cout << str;

#define NEWLINE PUT('\n')

#define SUNSET_OVER_BUILDINGS "🌇"
#define INTERNET              "🌐"

/* add -DBRANCH=1 and lstdc++fs flag to use */
#if BRANCH
	#include <filesystem>
	#include <fstream>

	/* from timeplusplus library */
	typedef struct {
		unsigned days;
		unsigned hours;
		unsigned minutes;
	} timepp_t;

	/* branch detector supports mercurial & git */
	#define BRANCH_SIGN "⎇"

	#define MERCURIAL BRANCH_SIGN
	#define GIT       BRANCH_SIGN

	#define GET_GIT_BRANCH       "git branch | grep \"^\\*\" | sed 's/^..//'"
	#define GET_MERCURIAL_BRANCH "hg branch"
#endif

class Time {
public:
	std::string time();
	bool convert(int16_t minute, int16_t time);
};

std::string Time::time() {
	time_t     now = std::time(0);
    struct tm  tstruct;
    
    char       buf[80];
    tstruct  = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    
    return buf;
}

bool Time::convert(int16_t minute, int16_t time) {
	bool data;
	(minute == time || minute + 12 == time) ? data = true : data = false;
	return data;
}


namespace CLIWidget {
	void time_widget_main(int16_t &i_time, int16_t &minute, Time &time, bool half) {
		if(time.convert(1, i_time))       (half == true) ? std::cout << "🕜" : std::cout << "🕐";
		else if(time.convert(2, i_time))  (half == true) ? std::cout << "🕝" : std::cout << "🕑";
		else if(time.convert(3, i_time))  (half == true) ? std::cout << "🕞" : std::cout << "🕒";
		else if(time.convert(4, i_time))  (half == true) ? std::cout << "🕟" : std::cout << "🕓";
		else if(time.convert(5, i_time))  (half == true) ? std::cout << "🕠" : std::cout << "🕔";
		else if(time.convert(6, i_time))  (half == true) ? std::cout << "🕡" : std::cout << "🕕";
		else if(time.convert(7, i_time))  (half == true) ? std::cout << "🕢" : std::cout << "🕖";
		else if(time.convert(8, i_time))  (half == true) ? std::cout << "🕣" : std::cout << "🕗";
		else if(time.convert(9, i_time))  (half == true) ? std::cout << "🕤" : std::cout << "🕘";
		else if(time.convert(10, i_time)) (half == true) ? std::cout << "🕥" : std::cout << "🕙";
		else if(time.convert(11, i_time)) (half == true) ? std::cout << "🕦" : std::cout << "🕚";
		else if(time.convert(12, i_time)) (half == true) ? std::cout << "🕧" : std::cout << "🕛";
	}
	
	void time_widget() {
		Time time;
		
		int16_t i_time     = std::atoi(time.time().erase(0, 11).substr(0, 2).c_str());
		int16_t minute   = std::atoi(time.time().substr(14, 17).c_str());
	
		if(minute >= 30) {
			CLIWidget::time_widget_main(i_time, minute, time, true);
		} else {
			CLIWidget::time_widget_main(i_time, minute, time, false);
		}
	}
	
	#if BRANCH
		std::string convert(const char* data) {
    		return data;
		}
		
		std::string convert(int data) {
    		return std::to_string(data);
		}
		
		std::string command_output(const std::string& command) {
    		/* print output of command to file */
    		system((command + " > execute_temp.txt").c_str());
 
 			/* read file */
    		std::ifstream ifs("execute_temp.txt");
    		
    		std::string ret { 
    			std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() 
    		};
    		
    		ifs.close(); 
    		
    		if(std::remove("execute_temp.txt") != 0) {
        		ret = "cli_widget_error";	
    		}
    		
    		return ret;
		}
 
		void branch_widget() {
			if(std::filesystem::exists(".hg")) {
				PUT(CLIWidget::command_output(convert(GET_MERCURIAL_BRANCH)));
			} else if(std::filesystem::exists(".git")) {
				PUT(CLIWidget::command_output(convert(GET_GIT_BRANCH)));
			}
		}

		timepp_t time_init() {
			std::ifstream file("/proc/uptime");
			std::string line;
			timepp_t time;
		
    		int d, h, m, s;

    		if (!file.is_open()) return time;

			while(std::getline(file, line)) { s = atoi(line.c_str()); } 
		
    		d = s / 60 / 60 / 24;
    		h = s / 60 / 60 % 24;
    		m = s / 60 % 60;

    		if(d ^ 0) time.days    = d; 
    		if(h ^ 0) time.hours   = h;
    		if(m ^ 0) time.minutes = m;
    	
    		return time;
		}
		
		
		void uptime_widget() {
			timepp_t time = time_init();
			
			PUT(convert(time.hours) + "h " + convert(time.minutes) + "m")
		}
	#endif
	
	void internet_connection_widget() {
	    if(system("wget -q -t=1 -O /dev/null --no-cache http://www.google.com/") == 0) {
	        PUT(INTERNET)
	    }
	}
}

#endif // CLI_WIDGET_HPP
