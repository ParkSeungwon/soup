#include<iostream>
#include<sstream>
#include"xmlparser.h"
using namespace std;

const char* links[] = {//' is needed, be careful : & -> run background
"'https://www.dongguk.edu/mbs/kr/jsp/board/list.jsp?boardId=3638&id=kr_010801000000'"
//"'https://www.dongguk.edu/mbs/kr/jsp/board/list.jsp?boardId=3646&id=kr_010802000000'",
//"'https://www.dongguk.edu/mbs/kr/jsp/board/list.jsp?boardId=9457435&id=kr_010807000000'",
//"'http://lincplus.dongguk.edu/index.php?menu_code1=2&menu_code2=274&menu_code3=275'"
};

string psstm(string command);
string get_url(string url) {
	return psstm(string("python get_url.py ") + url);
}

int main(int ac, char** av)
{
	for(auto& link : links) {
		stringstream ss;
		ss << get_url(link);
		Parser p;
		p.read_html(ss);
	//	cout << p.to_html() << endl;
		for(auto& a : p.find_all("Text", "2017-08-03", true)) cout << p.to_str(p.find_parent(a)) << endl;
//		for(auto& a : p.find_all("Text", "2017-08-03")) {
//			auto v = p.find_parent(p.find_parent(a));
//			auto l = p.find("HeadTail", "a", v);
//			cout << (*l)["href"] << endl;
//		}
	}
}

