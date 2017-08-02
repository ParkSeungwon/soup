#include<iostream>
#include<regex>
using namespace std;

int main()
{
	regex e{R"li((\S+)="\S+")li"};
	smatch m;
	string s = R"(<form action="/cgi-bin/login.cgi" method="post">)";
	regex_search(s, m, e);
		for(auto a : m) cout << a << ' ';
		s = m.suffix();
	
}

