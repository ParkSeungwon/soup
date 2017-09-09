#pragma once
#include"xmlparser.h"

using sNsNi = std::map<std::string, std::map<std::string, int>>; 

class XMLMine : public Parser
{
public:
	void mine(std::string site, int depth=3);
	
protected:
	static sNsNi tag2_, attr2_;//tag->tag, tag->attr
	static std::map<std::string, sNsNi> tag3_, attr3_;//tag, attr = property, count | tag->tag->  tag, count
	static std::vector<std::string> visited_sites_;

private:
	void mine();
	void save();
	bool did_visit(std::string site);
};

