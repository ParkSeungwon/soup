#include"util.h"
#include"xmlmine.h"
using namespace std;

int main(int ac, char** av)
{
	XMLMine xm;
	stringstream ss; ss << get_url(ac < 2 ? "http://www.naver.com" : av[1]);
	xm.read_html(ss);
}

