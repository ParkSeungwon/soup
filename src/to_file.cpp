#include<sstream>
#include<iostream>
#include<fstream>
#include<regex>
#include"util.h"
using namespace std;

vector<string> v;
string remove_comment(istream& is)
{
	char c; string s;
	while(is >> noskipws >> c) s += c;
	regex e{R"(/\*[\s\S]*?\*/)"};//? make non greedy match
	return regex_replace(s, e, "");
}
		
int main(int ac, char** av)
{
	ifstream f(ac < 2 ? "bootstrap.css" : av[1]);
	stringstream ss; ss << remove_comment(f);
	char c; string s;
	while(ss >> c) {
		if(s == "") continue;
		while(s.front() == ' ') s.erase(0, 1);
		cout << s << endl;
	}
}

