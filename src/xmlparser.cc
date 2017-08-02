#include<iostream>
#include<regex>
#include"xmlparser.h"
using namespace std;

static string get_bracket(istream& is)
{//return < ~ > or text_between brackets
	string s;
	char c;
	if(is >> skipws >> c) {//if not eof
		if(c == '<') {
			while(c != '>') {
				s += c;
				is >> noskipws >> c;
			}
			s += '>';
			if(s[1] == '!') return get_bracket(is);//pass comment
		} else {
			while(c != '<') {
				s += c;
				is >> noskipws >> c;
			}
			is.seekg(-1, is.cur);
		}
	}
	return s;
}

u_map Parser::parse_bracket(std::istream& is)
{//parse <tag></tag>, <tag />, Text
	string s = get_bracket(is);
	u_map t;
	if(s == "") return t;//eof
	if(s[0] == '<') {
		if(s[1] == '/') return t;//return empty on close
		regex tag_e{R"li(<(\S+)[>\s])li"};
		regex opt_e{R"li((\S+)=[\'\"](.*)[\"\'])li"};
		smatch m;
		regex_search(s, m, tag_e);
		t[(s[s.length() -2] == '/' || m[1] == "br") ? "Mono" : "HeadTail"] = m[1];

		while(regex_search(s, m, opt_e)) {
			t[m[1]] = m[2];
			s = m.suffix();
		}
	} else t["Text"] = s;
	return t;
}

void Parser::insert_edge(shared_ptr<u_map> shp, std::istream& is)
{
	u_map t = parse_bracket(is);
	if(t.empty()) return;
	auto sh = make_shared<u_map>(t);
	insert_vertex(sh);
	if(shp) Graph::insert_edge(shp, sh);
	if(t.begin()->first == "HeadTail") insert_edge(sh, is);
	insert_edge(shp, is);
}

void Parser::read_html(istream& is)
{
	insert_edge(nullptr, is);
}
	
string Parser::to_str(Vertex<shared_ptr<u_map>>* v)
{
	auto it = v->data->begin();
	string type = it->first, text = it->second;
	string s;
	if(type == "Text") return text;
	else {
		s = "<";
		s += it->second;
		for(it++; it != v->data->end(); it++) {
			s += ' ';
			s += it->first + "=\"" + it->second + "\"";
		}
		if(type == "Mono") s += " /";
		s += '>';
	}
	for(Edge<shared_ptr<u_map>>* e = v->edge; e; e = e->edge) s += to_str(e->vertex);
	if(type == "HeadTail") {
		s += "</";
		s += text + '>';
	}
	return s;
}

string Parser::to_html()
{
	return to_str(Graph::root);
}
