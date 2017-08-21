#include"scrap.h"
using namespace std;

Scrap::Scrap(string site)
{
	stringstream content;
	content << get_url(site);
	Parser p;
	p.read_html(content);

	for(auto plink : p.regex_find("href", "http.+")) {
		string title;
		for(auto txt : p.regex_find("Text", ".+", plink))
			title += (*txt)["Text"] + ' ';

