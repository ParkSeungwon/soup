#include<iostream>
#include<regex>
#include"xmlparser.h"
using namespace std;

string parse_script(istream& is) 
{
	string s;
	char c;
	while(s.find("</script>") == string::npos) {
		is >> noskipws >> c;
		s += c;
	}
	for(int i=0; i<9; i++) s.pop_back();
	return s;
}

string Parser::get_bracket(istream& is)
{//return < ~ > or text_between brackets
	string s;
	char c;
	if(Graph::root == nullptr) is >> skipws;//until insert html
	else is >> noskipws;
	if(is_script) {
		s = parse_script(is);
		is_script = false;
	} else if(is >> c) {//if not eof
		if(c == '<') {
			int open = 1;
			while(open) {
				s += c;
				is >> noskipws >> c;
				if(c == '<') open++;
				else if(c == '>') open--;
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

map<string, string> Parser::parse_bracket(std::istream& is)
{//parse <tag></tag>, <tag />, Text
	string s = get_bracket(is);
	map<string, string> t;
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

void Parser::insert_edge(sh_map shp, std::istream& is)
{
	map<string, string> t = parse_bracket(is);
	if(t.empty()) return;
	auto sh = make_shared<map<string, string>>(t);
	insert_vertex(sh);
	if(shp) Graph::insert_edge(shp, sh);
	if(t.begin()->first == "HeadTail") {
		is_script = t.begin()->second == "script";
		insert_edge(sh, is);
	}
	insert_edge(shp, is);
}

void Parser::read_html(istream& is)
{
	insert_edge(nullptr, is);
}
	
string Parser::to_str(sh_map shp) const
{
	auto* v = Graph::find(Graph::root, shp);
	if(!v) return "";
	auto it = v->data->cbegin();
	string type = it->first, text = it->second;
	string s;
	if(type == "Text") return text;
	else {
		s = '<' + it->second;
		for(it++; it != v->data->cend(); it++)//options
			s += ' ' + it->first + "=\"" + it->second + "\"";
		if(type == "Mono") s += " /";
		s += '>';
	}
	//add inner brackets recursively
	for(Edge<sh_map>* e = v->edge; e; e = e->edge) s += to_str(e->vertex->data);
	if(type == "HeadTail") s += "</" + text + '>';//closing after inner
	return s;
}

string Parser::to_html() const
{
	//"Content-type:text/html\r\n\r\n" 
	return to_str(Graph::root->data);
}

vector<sh_map> Parser::find_all(std::string a, std::string b, bool like) const
{
	vector<sh_map> vec;
	for(Vertex<sh_map>* v = Graph::root; v; v = v->vertex) {
		for(const auto& sNs : *v->data) {
			if(!like && sNs.first == a && sNs.second == b) vec.push_back(v->data);
			if(like && sNs.first == a && sNs.second.find(b) != string::npos) 
				vec.push_back(v->data);
		}
	}	
	return vec;
}

sh_map Parser::find(sh_map sp, sh_map pr) const
{//find among child nodes
	auto* parent = Graph::find(Graph::root, pr);
	if(!parent) parent = Graph::root;
	static Vertex<sh_map>* r = nullptr;//recursive -> static
	for(Edge<sh_map>* e = parent->edge; e; e = e->edge) {
		if(e->vertex->data == sp) r = e->vertex;
		else find(sp, e->vertex->data);
	}
	return r ? r->data : nullptr;
}

sh_map Parser::find_parent(sh_map child) const
{//return parent node vertex address
	for(Vertex<sh_map>* v = Graph::root; v; v = v->vertex) 
		for(Edge<sh_map>* e = v->edge; e; e = e->edge) 
			if(e->vertex->data == child) return v->data;
	return nullptr;
}

sh_map Parser::find(string a, string b, sh_map pr) const
{
	auto* parent = Graph::find(Graph::root, pr);
	if(!parent) parent = Graph::root;
	static Vertex<sh_map>* r = nullptr;//recursive -> static
	for(Edge<sh_map>* e = parent->edge; e; e = e->edge) {
		if((*e->vertex->data)[a] == b) r = e->vertex;
		else find(a, b, e->vertex->data);
	}
	return r ? r->data : nullptr;
//	auto* parent = Graph::find(Graph::root, pr);
//	if(!parent) parent = Graph::root;
//	auto v = find_all(a, b);
//	for(auto& sh : v) if(auto r = find(sh, parent->data)) return r;
//	return nullptr;
}

