#include<iostream>
#include<sstream>
#include"xmlparser.h"
using namespace std;

const char* links[][2] = {
	"https://cse.dongguk.edu",
	"",//컴퓨터공학부
	"https://www.dongguk.edu/mbs/kr/jsp/board/",
	"list.jsp?boardId=3638&id=kr_010801000000",//학사공지
	"https://www.dongguk.edu/mbs/kr/jsp/board/",
	"list.jsp?boardId=3646&id=kr_010802000000",//일반공지
	"https://www.dongguk.edu/mbs/kr/jsp/board/",
	"list.jsp?boardId=9457435&id=kr_010807000000",//국제공지
	"http://lincplus.dongguk.edu",
	"/index.php?menu_code1=2&menu_code2=274&menu_code3=275",//Linc 공지
	"https://bs.dongguk.edu",
	"/bbs/board.php?bo_table=bs5_1", //불교학부
	"http://lincplus.dongguk.edu",
	"/index.php?menu_code1=5&menu_code2=251"//linc공지
};

string psstm(string command);
string get_url(string url) {//' is needed, be careful : & -> run background
	return psstm("python get_url.py '" + url + "'");
}
string get_date(unsigned n);

int main()
{//crawl today&yesterday's new post
	cout << "Content-type:text/html\r\n\r\n";//for browser recognition
	cout << "<html><head><meta charset='utf-8' />";
	cout << "<title>New Post from " << get_date(1) << "</title></head><body>";
	for(auto& link : links) {
		stringstream ss;
		ss << get_url(string(link[0]) + link[1]);
		Parser p;
		p.read_html(ss);
		for(int i=0; i<2; i++) {//0=today, 1yesterday
			for(auto& a : p.regex_find(regex{"Text"}, regex{get_date(i)})) {
				auto sh1 = p.find_parent(p.find_parent(a));
				for(auto& k : p.find("HeadTail", "a", sh1)) {
					if(k->find("href") != k->end()) {
						while((*k)["href"].front() == '.')// ../bbs 
							(*k)["href"] = (*k)["href"].substr(1);
						(*k)["href"].insert(0, link[0]);//make relative url absolute
						cout << p.to_str(k) + "<br />" << endl;
					}
				}
			}
		}
	}
	cout << "</body></html>";
}

