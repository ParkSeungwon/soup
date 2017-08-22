#pragma once
#include<string>
#include<map>
#include<vector>

struct Sub
{
	std::string site, title, contents;
	std::map<std::string, int> keyword;
	int score = 0;
};

std::vector<Sub> scrap(std::string site);
