#include<sstream>
#include"scrap.h"
#include"xmlparser.h"
using namespace std;

string get_url(string);
string analyse_document(string);

Scrap::Scrap(string site)
{
	Parser p;
	p.read_html(get_url(site));

	for(auto plink : p.regex_find("href", "http.+")) {
		string title;
		string link = (*plink)["href"];
		for(auto ptxt : p.regex_find("Text", ".+", plink))
			title += (*ptxt)["Text"] + ' ';
		map<string, int> m;
		stringstream ss;
		string txt = get_url(link);
		v.push_back({link, title, txt, keyword(txt+' '+title+' '+title+' '+title)});
	}
}

map<string, int> Scrap::keyword(string html_text)
{
	Parser p;
	p.read_html(html_text);
	string raw_text;
	for(auto a : p.regex_find("Text", ".+")) raw_text += (*a)["Text"] + ' ';

	stringstream ss;
	ss << analyse_document(raw_text);
	string s1, s2;
	map<string, int> m;
	while(ss >> s1 >> s2) if(s2 == "Noun") m[s1]++;
	return m;
}
