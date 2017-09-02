#include<iostream>
#include<sstream>
#include"xmlparser.h"
using namespace std;

string get_url(string url);
int main()
{
	Parser p;
	stringstream ss;
	ss << get_url("https://www.w3schools.com/TAGs/default.asp");
	p.read_html(ss);
	map<string, string> tags;
	for(auto& a : p.regex_find("Text", "&lt;\\S+&gt;")) {
		auto sh = p.find_parent(p.find_parent(a));
		for(auto& b : p.regex_find("Text", "[^&].+", sh)) 
			tags.insert((*a)["Text"], (*b)["Text"]);
	}
}
