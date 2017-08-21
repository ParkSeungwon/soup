#pragma once
#include<string>
#include<map>
#include<vector>

struct Sub
{
	std::string site, title, contents;
	std::map<std::string, int> keyword;
};

class Scrap
{
public:
	Scrap(std::string site);
	std::vector<Sub> v;

private:
	std::map<std::string, int> keyword(std::string txt);
};
