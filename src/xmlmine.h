#pragma once
#include"xmlparser.h"

using sNsNi = std::map<std::string, std::map<std::string, int>>; 

//template <typename T1, typename T2> Json::Value map2json(std::map<T1, T2> m)
//{
//	Json::Value v;
//	for(const auto& a : m) v[a.first] = a.second;
//	return v;
//}

class XMLMine : public Parser
{
public:
	XMLMine();
	void read_html(std::istream& is);
	virtual ~XMLMine();
	
protected:
	sNsNi tag2_, attr2_;//tag->tag, tag->attr
	std::map<std::string, sNsNi> tag3_, attr3_;//tag, attr = property, count | tag->tag->  tag, count
};

