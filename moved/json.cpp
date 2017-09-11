#include<map>
#include<iostream>
#include<json/json.h>
using namespace std;

int main()
{
	Json::Value v;
	map<string, string> m;
	m["fd"] = "fdff";
	for(auto a : m) {v["a"].append(a.first);v["a"].append(a.second);}
	cout << v;
	for(int i=0; i < v["a"].size(); i++) {
		cout << (v["a"][i] == "fd");
	}
}

