#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ifstream f("index.html");
	char c;
	f >> skipws;
	while(f >> c) cout << c;
}

