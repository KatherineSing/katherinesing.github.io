#include "datetime.h"
#include <ctime>
#include <iomanip>
#include <sstream>


using namespace std;

/**
* Default constructor for current system time/date
*/
DateTime::DateTime()
{
	time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime(&rawtime);


	

	year = timeinfo -> tm_year + 1900;
	month = 1 + timeinfo -> tm_mon;
	day = timeinfo -> tm_mday;
	hour = timeinfo -> tm_hour;
	min = timeinfo -> tm_min;
	sec = timeinfo-> tm_sec;
}

/**
* Alternative constructor 
*/
DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
  hour = hh;
  min = mm;
  sec = ss;
  this->year = year;
  this->month = month;
  this->day = day;
}

/**
* Return true if the timestamp is less-than other's
*
* @return result of less-than comparison of timestamp
*/
bool DateTime::operator<(const DateTime& other) const
{
	if (year < other.year) return true;
	else if (year > other.year) return false;
	
	if(month < other.month) return true;
	else if (month > other.month) return false;

	if (day < other.day) return true;
	else if (day > other.day) return false;

	if (hour < other.hour) return true;
	else if (hour > other.hour) return false;
	
	if (min < other.min) return true;
	else if (min > other.min) return false;

	if (sec < other.sec) return true;
	else if (sec > other.sec) return false;

	return false;


	// if (year < other.year) return true;
	// else if (year == other.year)
	// {
	// 	if(month < other.month) return true;
	// 	else if (month == other.month)
	// 	{
	// 		if (day < other.day) return true;
	// 		else if (day == other.day) 
	// 		{
	// 			if (hour < other.hour) return true;
	// 			else if (hour == other.hour) 
	// 			{
	// 				if (min < other.min) return true;
	// 				else if (min == other.min)
	// 				{
	// 					if (sec < other.sec) return true;
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// return false;
}

/**
* Outputs the timestamp to the given ostream in format:
*   YYYY-MM-DD HH::MM::SS
*	
* @return the ostream passed in as an argument
*/
ostream& operator<<(std::ostream& os, const DateTime& other)
{
	//set fill and set w

	os << setfill('0') << setw(4) << other.year; 
	os << '-';
	os << setfill('0') << setw(2) << other.month;
	os << '-';
	os << setfill('0') << setw(2) << other.day;
	os << ' ';
	os << setfill('0') << setw(2) << other.hour;
	os << ':';
	os << setfill('0') << setw(2) << other.min;
	os << ':';
	os << setfill('0') << setw(2) << other.sec;
	return os;
}



/**
* Inputs the timestamp to the given istream expecting the format:
*   YYYY-MM-DD HH:MM:SS
*  Returns if an error in the format with the DateTime set to the
*   current system time/date
*   
*
* @return the istream passed in as an argument
*/
istream& operator>>(std::istream& is, DateTime& dt)
{	
	DateTime toReturn;
	if (is.fail()) 
	{
		dt = toReturn;
		is.setstate(std::ios::failbit);
		return is;
	}
	/****** YEAR ******/
	string stryear;
	getline(is, stryear, '-');
	unsigned int j = 0;
	while (isspace(stryear[j]) && j < stryear.size())
	{
		stryear = stryear.erase(0, 1);
	}
	istringstream ss(stryear);
    int year = 0;
    if(!(ss >> year && stryear.size()==4)) 
	{
    	dt = toReturn;
    	is.setstate(std::ios::failbit);
		return is;
	}

	/****** MONTH ******/
	string strmonth;
	getline(is, strmonth, '-');
	istringstream ss1(strmonth);
    int month = 0;
    if(!(ss1 >> month && strmonth.size()==2)) 
	{
    	dt = toReturn;
    	is.setstate(std::ios::failbit);
		return is;
	}

	/****** DAY ******/
	string strday;
	getline(is, strday, ' ');
	istringstream ss2(strday);
    int day = 0;
    if(!(ss2 >> day && strday.size()==2)) 
	{
    	dt = toReturn;
    	is.setstate(std::ios::failbit);
		return is;
	}

	/****** HOUR ******/
	string strhour;
	getline(is, strhour, ':');
	istringstream ss3(strhour);
    int hour = 0;
    if(!(ss3 >> hour && strhour.size()==2)) 
	{
    	dt = toReturn;
    	is.setstate(std::ios::failbit);
		return is;
	}

	/****** MIN ******/
	string strmin;
	getline(is, strmin, ':');
	istringstream ss4(strmin);
    int min = 0;
    if(!(ss4 >> min && strmin.size()==2)) 
	{
    	dt = toReturn;
    	is.setstate(std::ios::failbit);
		return is;
	}

	/****** SEC ******/
	string strsec;
	getline(is, strsec, ' ');
	istringstream ss5(strsec);
    int sec = 0;
    if(!(ss5 >> sec && strsec.size()==2)) 
	{
    	dt = toReturn;
    	is.setstate(std::ios::failbit);
		return is;
	}

	dt.year = year;
	dt.month = month;
	dt.day = day;
	dt.hour = hour;
	dt.min = min;
	dt.sec = sec;
	return is;
}