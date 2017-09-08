#include"xmlmine.h"
#include"util.h"
using namespace std;

int main(int ac, char** av)
{
	XMLMine xm;
	xm.mine(get_url(ac < 2 ? "http://www.naver.com" : av[1]), ac < 3 ? 3 : atoi(av[2]));
//	xm.regex_find("href", 
}

