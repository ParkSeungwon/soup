#include"xmlparser.h"
#include<iostream>
using namespace std;

int main()
{
	Parser p;
	p.read_html(cin);
	p.view();
	cout << p.to_html();
}

