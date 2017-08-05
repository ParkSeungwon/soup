#include<iostream>
#include<sstream>
#include"xmlparser.h"
using namespace std;

const char* links[] = {//' is needed, be careful : & -> run background
	"'https://www.dongguk.edu/mbs/kr/jsp/board/"
	"list.jsp?boardId=3638&id=kr_010801000000'",//학사공지
	"'https://www.dongguk.edu/mbs/kr/jsp/board/"
	"list.jsp?boardId=3646&id=kr_010802000000'",//일반공지
	"'https://www.dongguk.edu/mbs/kr/jsp/board/"
	"list.jsp?boardId=9457435&id=kr_010807000000'",//국제공지
	"'http://lincplus.dongguk.edu/index.php"
	"?menu_code1=2&menu_code2=274&menu_code3=275'",//Linc 공지
//	"'https://cse.dongguk.edu'",//컴퓨터공학부
	"'https://bs.dongguk.edu/bbs/board.php?bo_table=bs5_1'" //불교학부
};

string psstm(string command);
string get_url(string url) {
	return psstm(string("python get_url.py ") + url);
}
string get_yesterday();
string get_today();

int main()
{//crawl today's new post
	cout << "Content-type:text/html\r\n\r\n";//for browser recognition
	cout << "<html><head><meta charset='utf-8' />";
	cout << "<title>" << get_yesterday() << "</title></head><body>";
	for(auto& link : links) {
		stringstream ss;
		ss << get_url(link);
		Parser p;
		p.read_html(ss);
		for(string date : {get_yesterday(), get_today()}) {
			for(auto& a : p.find("Text", date, nullptr, true)) {
				auto sh1 = p.find_parent(p.find_parent(a));
				for(auto& k : p.find("HeadTail", "a", sh1)) {
					if(k->find("href") != k->end()) {
						(*k)["href"].insert(0, 
								"https://www.dongguk.edu/mbs/kr/jsp/board/");
						cout << p.to_str(k) + "<br />" << endl;
					}
				}
			}
		}
	}
	cout << "</body></html>";
}

