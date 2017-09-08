#pragma once
#include"xmlparser.h"

using sNsNi = std::map<std::string, std::map<std::string, int>>; 

class XMLMine : public Parser
{
public:
	XMLMine(std::string initfile);
	void save();
	
protected:
	sNsNi tag2_, attr2_;//tag->tag, tag->attr
	std::map<std::string, sNsNi> tag3_, attr3_;//tag, attr = property, count | tag->tag->  tag, count
};

