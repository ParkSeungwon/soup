#pragma once
#include"xmlparser.h"

using sNsNi = std::map<std::string, std::map<std::string, int>>; 

class XMLMine : public Parser
{
public:
	XMLMine();
	void read_html(std::istream& is);
	void read_html(std::string s);
	void mine(std::string site, int depth=3);
	virtual ~XMLMine();
	
protected:
	sNsNi tag2_, attr2_;//tag->tag, tag->attr
	std::map<std::string, sNsNi> tag3_, attr3_;//tag, attr = property, count | tag->tag->  tag, count

private:
	void mine();
};

