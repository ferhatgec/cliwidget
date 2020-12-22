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
*/


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
}

#endif // CLI_WIDGET_HPP
