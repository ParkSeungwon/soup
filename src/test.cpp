#include"xmlparser.h"
#include<iostream>
using namespace std;

int main()
{
	Parser p;
	p.read_html(cin);
	cout << p.to_html();
}

