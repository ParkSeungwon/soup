#include<iostream>
#include<sstream>
#include<fstream>
#include"xmlparser.h"
#include"util.h"
using namespace std;

int main()
{
	Parser p;
	stringstream ss;
	ss << get_url("https://www.w3schools.com/TAGs/ref_attributes.asp");
//	ss << get_url("https://www.w3schools.com/TAGs/default.asp");
	p.read_html(ss);
	vector<string> vs;
	ofstream f("count.txt");
	for(auto& a : p.regex_find("HeadTail", "tr")) {
		auto v = p.regex_find("Text", ".+", a);
		int n = v.size();
		if(n > 1) {
			f << n << ' ';
			for(int i=0; i<n; i++) vs.push_back((*v[i])["Text"]);
		}
	}
	serialize(vs, "attr_tag.ser");
}
