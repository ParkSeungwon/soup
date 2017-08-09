#include<chrono>
#include<ctime>
#include<iomanip>
#include<sstream>
using namespace std;
using namespace std::chrono;

string get_date(unsigned n)
{//2017-08-04
	time_t now = system_clock::to_time_t(system_clock::now() - 24h * n);
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	stringstream date; 
	date << "\\s*" << year << '.' << setw(2) << setfill('0') << month;
	date << '.' << setw(2) << setfill('0') << day << "\\s*";
	return date.str();
}
	
