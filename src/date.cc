#include<chrono>
#include<ctime>
#include<iomanip>
#include<sstream>
using namespace std;
using namespace std::chrono;

string get_yesterday()
{//2017-08-04
	time_t now = system_clock::to_time_t(system_clock::now() - 24h);
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	stringstream date; 
	date << year << '-' << setw(2) << setfill('0') << month;
	date << '-' << setw(2) << setfill('0') << day;
	return date.str();
}
	
string get_today()
{//2017-08-04
	time_t now = system_clock::to_time_t(system_clock::now());
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	stringstream date; 
	date << year << '-' << setw(2) << setfill('0') << month;
	date << '-' << setw(2) << setfill('0') << day;
	return date.str();
}

