#include<json/writer.h>
#include<json/reader.h>
#include<json/value.h>
#include"xmlmine.h"
using namespace std;

XMLMine::XMLMine(string initfile) 
{
	ifstream f1{"tag2.json"}, f2{"tag3.json"}, f3{"attr2.json"}, f4{"attr3.json"};
	Json::Reader r;
	Json::Value v;
	r.parse(f1, v);
	for(auto& a : v) for(auto& b : a) tag2_[a.first][v[a]] = v[a][b];
}

void XMLMine::save()
{
	ofstream f1{"tag2.json"}, f2{"tag3.json"}, f3{"attr2.json"}, f4{"attr3.json"};
	Json::Value tag2, attr2, tag3, attr3;
	for(auto& a : tag2_) for(auto& b : a.second) tag2[a.first][b.first] = b.second;
	for(auto& a : attr2_) for(auto& b : a.second) attr2[a.first][b.first] = b.second;
	for(auto& a : tag3_) for(auto& b : a.second) for(auto& c : b.second) 
		tag3[a.first][b.first][c.first] = c.second;
	for(auto& a : attr3_) for(auto& b : a.second) for(auto& c : b.second) 
		attr3[a.first][b.first][c.first] = c.second;
	Json::StyledStreamWriter w;
	w.write(f1, tag2); w.write(f2, tag3); w.write(f3, attr2); w.write(f4, attr3);
}
