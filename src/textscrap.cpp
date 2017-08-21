#include<map>
#include<sstream>
#include"xmlparser.h"
using namespace std;

string get_url(string);
string analyse_document(string);

int main(int ac, char** av)
{
	string raw_text;
	{
		stringstream ss;
		ss << get_url(av[1]);
		Parser p;
		p.read_html(ss);
		for(auto a : p.regex_find("Text", ".+")) raw_text += (*a)["Text"] + ' ';
	}
	
	map<string, int> m;
	{
		stringstream ss;
		ss << analyse_document(raw_text);
		string s1, s2;
		while(ss >> s1 >> s2) if(s2 == "Noun") m[s1]++;
	}

	multimap<int, string, greater<int>> reverse;
	{
		for(auto a : m) reverse.insert({a.second, a.first});
		int n = 0;
		for(auto a : reverse) {
			cout << a.first << ' ' << a.second << endl;
			if(++n == 20) break;
		}
	}
}
	

