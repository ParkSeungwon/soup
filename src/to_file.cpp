#include<sstream>
#include<iostream>
#include<fstream>
#include"util.h"
using namespace std;


int main()
{
	ifstream f("class.txt");
	string s;
	while(getline(f, s)) {
		if(s == "") continue;
		while(s.front() == ' ') s.erase(0, 1);
		cout << s << endl;
	}
}

