#include<exception>
#include<json/json.h>
#include"xmlmine.h"
using namespace std;

XMLMine::XMLMine() 
{
	try {
		ifstream f1{"tag2.json"}, f2{"tag3.json"}, f3{"attr2.json"}, f4{"attr3.json"};
		Json::Value v;
		f1 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			tag2_[a][b] = v[a][b].asInt();
		f3 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			attr2_[a][b] = v[a][b].asInt();
		f2 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			for(auto& c : v[a][b].getMemberNames()) 
				tag3_[a][b][c] = v[a][b][c].asInt();
		f4 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			for(auto& c : v[a][b].getMemberNames()) 
				attr3_[a][b][c] = v[a][b][c].asInt();
	} catch(ifstream::failure& e) { 
		cerr << e.what() << endl; 
	} catch(exception& e) {
		cerr << e.what() << endl;
	}
}

XMLMine::~XMLMine()
{
	ofstream f1{"tag2.json"}, f2{"tag3.json"}, f3{"attr2.json"}, f4{"attr3.json"};
	Json::Value tag2, attr2, tag3, attr3;
	for(auto& a : tag2_) for(auto& b : a.second) tag2[a.first][b.first] = b.second;
	for(auto& a : attr2_) for(auto& b : a.second) attr2[a.first][b.first] = b.second;
	for(auto& a : tag3_) for(auto& b : a.second) for(auto& c : b.second) 
		tag3[a.first][b.first][c.first] = c.second;
	for(auto& a : attr3_) for(auto& b : a.second) for(auto& c : b.second) 
		attr3[a.first][b.first][c.first] = c.second;
	f1 << tag2; f2 << tag3; f3 << attr2; f4 << attr3;
}

void XMLMine::read_html(istream& is)
{
	Parser::read_html(is);
	for(auto* v = Graph::root->vertex; v != nullptr; v = v->vertex) {
		if(v->data->begin()->first == "Text") continue;
		string tag = v->data->begin()->second;
		sh_map parent = find_parent(v->data);
		tag2_[parent->begin()->second][tag]++;
		for(auto it = ++v->data->begin(); it != v->data->end(); it++) {
			attr2_[tag][it->first]++;
			attr3_[tag][it->first][it->second]++;
		}
		if(tag == "body" || tag == "head") continue;
		tag3_[find_parent(parent)->begin()->second][parent->begin()->second][tag]++;
	}
}

