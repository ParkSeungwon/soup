#include<iostream>
#include<sstream>
#include<ctime>
#include<iomanip>
#include"xmlparser.h"
using namespace std;

const char* links[] = {//' is needed, be careful : & -> run background
	"'https://www.dongguk.edu/mbs/kr/jsp/board/list.jsp?boardId=3638&id=kr_010801000000'",//학사공지
	"'https://www.dongguk.edu/mbs/kr/jsp/board/list.jsp?boardId=3646&id=kr_010802000000'",//일반공지
	"'https://www.dongguk.edu/mbs/kr/jsp/board/list.jsp?boardId=9457435&id=kr_010807000000'",//국제공지
	"'http://lincplus.dongguk.edu/index.php?menu_code1=2&menu_code2=274&menu_code3=275'"//Linc 공지
};

string psstm(string command);
string get_url(string url) {
	return psstm(string("python get_url.py ") + url);
}

string get_date()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	stringstream date; 
	date << year << '-' << setw(2) << setfill('0') << month;
	date << '-' << setw(2) << setfill('0') << day;
	return date.str();
}

int main()
{//crawl today's new post
	cout << R"(<html><meta charset="utf8" />)" << endl;
	for(auto& link : links) {
		stringstream ss;
		ss << get_url(link);
		Parser p;
		p.read_html(ss);
		for(auto& a : p.find("Text", get_date(), nullptr, true)) {
			auto sh1 = p.find_parent(p.find_parent(a));
			for(auto& k : p.find("HeadTail", "a", sh1)) {
				if(k->find("href") != k->end()) {
					(*k)["href"].insert(0, "https://www.dongguk.edu/mbs/kr/jsp/board/");
					cout << p.to_str(k) + "<br />" << endl;
				}
			}
		}
	}
	cout << "</html>";
}

