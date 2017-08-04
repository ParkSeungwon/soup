#include<iostream>
#include<regex>
#include"xmlparser.h"
using namespace std;

string Parser::get_bracket(istream& is)
{//return < ~ > or text_between brackets
	string s;
	char c;
	if(Graph::root == nullptr) is >> skipws;//until insert html
	else is >> noskipws;
	if(is >> c) {//if not eof
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
				if(is >> noskipws >> c);
				else break;//repair eof bug, deal with ending text
			}
			is.seekg(-1, is.cur);
			if(Graph::root == nullptr) return get_bracket(is);//for text before html
		}
	}
	return s;
}

static const char* void_element[] = {
	"area", "base", "br", "col", "command", "embed", "hr", "img", "input",
	"keygen", "link", "meta", "param", "source", "track", "wbr"
};

u_map Parser::parse_bracket(std::istream& is)
{//parse <tag></tag>, <tag />, Text
	string s = get_bracket(is);
	u_map t;
	if(s == "") return t;//eof
	if(s[0] == '<') {
		if(s[1] == '/') return t;//return empty on close
		regex tag_e{R"li(<(\S+)[>\s])li"};
		regex opt_e{R"li((\S+)=['"]([^'"]*)["'])li"};
		smatch m;
		regex_search(s, m, tag_e);
		bool mono = false;
		for(auto a : void_element) if(a == m[1]) mono = true;
		if(s[s.length() -2] == '/') mono = true;
		t[mono ? "Mono" : "HeadTail"] = m[1];

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
	
string Parser::to_str(Vertex<shared_ptr<u_map>>* v) const
{
	if(!v) return "";
	auto it = v->data->begin();
	string type = it->first, text = it->second;
	string s;
	if(type == "Text") return text;
	else {
		s = '<' + it->second;
		for(it++; it != v->data->end(); it++)//options
			s += ' ' + it->first + "=\"" + it->second + "\"";
		if(type == "Mono") s += " /";
		s += '>';
	}
	//add inner brackets recursively
	for(Edge<shared_ptr<u_map>>* e = v->edge; e; e = e->edge) s += to_str(e->vertex);
	if(type == "HeadTail") s += "</" + text + '>';//closing after inner
	return s;
}

string Parser::to_html() const
{
	//"Content-type:text/html\r\n\r\n" 
	return to_str(Graph::root);
}

vector<shared_ptr<u_map>> Parser::find_all(std::string a, std::string b) const
{
	vector<shared_ptr<u_map>> vec;
	for(Vertex<shared_ptr<u_map>>* v = Graph::root; v; v = v->vertex) 
		for(const auto& sNs : *v->data) 
			if(sNs.first == a && sNs.second == b) vec.push_back(v->data);
	return vec;
}

Vertex<shared_ptr<u_map>>* Parser::find(shared_ptr<u_map> sp, Vertex<shared_ptr<u_map>>* parent) const
{//find among child nodes
	if(!parent) parent = Graph::root;
	static Vertex<shared_ptr<u_map>>* r = nullptr;//recursive -> static
	for(Edge<shared_ptr<u_map>>* e = parent->edge; e; e = e->edge) {
		if(e->vertex->data == sp) r = e->vertex;
		else find(sp, e->vertex);
	}
	return r;
}

Vertex<shared_ptr<u_map>>* Parser::find_parent(Vertex<shared_ptr<u_map>>* child) const
{//return parent node vertex address
	for(Vertex<shared_ptr<u_map>>* v = Graph::root; v; v = v->vertex) 
		for(Edge<shared_ptr<u_map>>* e = v->edge; e; e = e->edge) 
			if(e->vertex == child) return v;
	return nullptr;
}

Vertex<shared_ptr<u_map>>* Parser::find(string a, string b, Vertex<shared_ptr<u_map>>* parent) const
{
	if(!parent) parent = Graph::root;
	auto v = find_all(a, b);
	for(auto& sh : v) if(auto* r = find(sh, parent)) return r;
	return nullptr;
}
