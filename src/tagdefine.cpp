#include<iostream>
#include<sstream>
#include<fstream>
#include"xmlparser.h"
using namespace std;

string get_url(string url);
void serialize(map<string, string> m, string filename) 
{
	ofstream f(filename);
	f << m.size() * 2 << ' ';
	for(auto& a : m) f << a.first.size() << ' ' << a.second.size() << ' ';
	for(auto& a : m) f << noskipws << a.first << a.second;
}

map<string, string> deserialize(string filename)
{
	ifstream f(filename);
	int n;
	f >> n;
	int sz[n];
	string ss[n];
	for(int i=0; i<n; i++) f >> sz[i];
	char c;
	f >> noskipws >> c;//consume trailing ' '
	for(int i=0; i<n; i++) {
		string s;
		for(int j=0; j<sz[i]; j++) {
			f >> noskipws >> c;
			s += c;
		}
		ss[i] = s;
	}
	map<string, string> m;
	for(int i=0; i<n; i+=2) m[ss[i]] = ss[i+1];
	return m;
}		

int main()
{
	Parser p;
	stringstream ss;
	ss << get_url("https://www.w3schools.com/TAGs/default.asp");
	p.read_html(ss);
	map<string, string> tags;
	for(auto& a : p.regex_find("Text", "&lt;\\S+&gt;")) {
		auto sh = p.find_parent(p.find_parent(p.find_parent(a)));
		string s = (*a)["Text"];
		s.erase(0, 4); s.erase(s.size() - 4, 4);//remove < >
		for(auto& b : p.regex_find("Text", "[^&].+", sh)) tags[s] = (*b)["Text"];
	}
	serialize(tags, "tags.ser");
	for(auto& a : deserialize("tags.ser")) cout << a.first << " : " << a.second << endl;
}
