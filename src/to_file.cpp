#include<fstream>
#include"util.h"
using namespace std;

int main()
{
	auto v = deserialize("boot.ser");
	ifstream ifs("count.txt");
	ofstream ofs("boot2.txt");
	int n, k = 0;
	vector<int> vi;
	while(ifs >> n) vi.push_back(n);
	for(int i=0; i<vi.size(); i++) {
		string s;
		ofs << v[k++] << ' ';
		for(int j=1; j<vi[i]-1; j++) s += v[k++] + ' ';
		ofs << v[k++] << endl << s << endl;
	}
}

