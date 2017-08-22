#include<sstream>
#include"scrap.h"
#include"xmlparser.h"
using namespace std;

string get_url(string);
string analyse_document(string);

map<string, int> keyword(string title, string html_text)
{
	Parser p;
	p.read_html(html_text);
	string raw_text = title + ' ' + title + ' ' + title + ' ';// *3 score
	for(auto a : p.regex_find("Text", ".+")) raw_text += (*a)["Text"] + ' ';

	stringstream ss;
	ss << analyse_document(raw_text);
	string s1, s2;
	map<string, int> m;
	while(ss >> s1 >> s2) if(s2 == "Noun") m[s1]++;
	return m;
}

vector<Sub> scrap(string site)
{
	Parser p;
	p.read_html(get_url(site));

//	int n = 0;
	vector<Sub> v;
	for(auto plink : p.regex_find("href", "http.+")) {
		string title;
		string link = (*plink)["href"];
		for(auto ptxt : p.regex_find("Text", "\\S+", plink))
			title += (*ptxt)["Text"] + ' ';
		if(title != "") {
			string txt = get_url(link);
			v.push_back({link, title, txt, keyword(title, txt)});
		}
//		if(n++ == 30) break;
	}
	return v;
}
