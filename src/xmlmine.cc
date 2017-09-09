#include<exception>
#include<json/json.h>
#include"xmlmine.h"
#include"util.h"
using namespace std;

static sNsNi t2, a2;
static map<string, sNsNi> t3, a3;
static vector<string> vs;

int init() 
{
	try {
		ifstream f1{"tag2.json"}, f2{"tag3.json"}, f3{"attr2.json"}, f4{"attr3.json"};
		Json::Value v;
		f1 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			t2[a][b] = v[a][b].asInt();
		f3 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			a2[a][b] = v[a][b].asInt();
		f2 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			for(auto& c : v[a][b].getMemberNames()) t3[a][b][c] = v[a][b][c].asInt();
		f4 >> v;
		for(auto& a : v.getMemberNames()) for(auto& b : v[a].getMemberNames()) 
			for(auto& c : v[a][b].getMemberNames()) a3[a][b][c] = v[a][b][c].asInt();
		ifstream f("visited.site");
		string s;
		while(getline(f, s)) vs.push_back(s);
	} catch(ifstream::failure& e) { 
		cerr << e.what() << endl; 
	} catch(exception& e) {
		cerr << e.what() << endl;
	}
	return 0;
}

static int k = init();
sNsNi XMLMine::tag2_ = move(t2);
sNsNi XMLMine::attr2_ = move(a2);
map<string, sNsNi> XMLMine::tag3_ = move(t3);
map<string, sNsNi> XMLMine::attr3_ = move(a3);
vector<string> XMLMine::visited_sites_ = move(vs);

void XMLMine::save()
{
	cout << "saving..." << endl;
	Json::Value tag2, attr2, tag3, attr3;
	for(auto& a : tag2_) for(auto& b : a.second) tag2[a.first][b.first] = b.second;
	for(auto& a : attr2_) for(auto& b : a.second) attr2[a.first][b.first] = b.second;
	for(auto& a : tag3_) for(auto& b : a.second) for(auto& c : b.second) 
		tag3[a.first][b.first][c.first] = c.second;
	for(auto& a : attr3_) for(auto& b : a.second) for(auto& c : b.second) 
		attr3[a.first][b.first][c.first] = c.second;
	ofstream f1{"tag2.json"}, f2{"tag3.json"}, f3{"attr2.json"}, f4{"attr3.json"};
	f1 << tag2; f2 << tag3; f3 << attr2; f4 << attr3;
	ofstream f{"visited.site"};
	for(string s : visited_sites_) f << s << endl;
}

void XMLMine::mine() 
{
	cout << "mining..." << endl;
	for(auto* v = Graph::root->vertex; v != nullptr; v = v->vertex) {
		if(v->data->begin()->first == "Text") continue;
		string tag = v->data->begin()->second;
		sh_map parent = find_parent(v->data);
		tag2_[parent->begin()->second][tag]++;
		for(auto it = ++v->data->begin(); it != v->data->end(); it++) {
			attr2_[tag][it->first]++;
			attr3_[tag][it->first][it->second]++;
		}
		for(char& c : tag) c = tolower(c);
		if(tag == "body" || tag == "head") continue;
		tag3_[find_parent(parent)->begin()->second][parent->begin()->second][tag]++;
	}
}

void XMLMine::mine(string site, int depth)
{
	if(!depth) return;
	Graph::gfree(Graph::root); Graph::root = nullptr;
	Parser::read_html(get_url(site));
	if(!did_visit(site)) {
		visited_sites_.push_back(site);
		mine();
		save();
	}
	for(auto& a : regex_find("HeadTail", "a")) mine((*a)["href"], depth-1);
}

bool XMLMine::did_visit(string site)
{
	for(string s : visited_sites_) if(s == site) return true;
	return false;
}

