#include"xmlmine.h"
#include"util.h"
using namespace std;

int main(int ac, char** av)
{
	XMLMine xm;
	string site = ac < 2 ? "http://www.naver.com" : av[1];
	int depth = ac < 3 ? 3 : atoi(av[2]);
	xm.mine({site}, depth);
}

