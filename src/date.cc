#include<chrono>
#include<ctime>
#include<cstring>
#include<iomanip>
#include<sstream>
#include<fcntl.h>//O_CRATE
#include<unistd.h>//ftruccate
#include<sys/mman.h>
#include<iostream>
#include<sys/shm.h>
using namespace std;
using namespace std::chrono;

string get_date(unsigned n)
{//2017-08-04
	time_t now = system_clock::to_time_t(system_clock::now() - 24h * n);
	tm *ltm = localtime(&now);
	int year = 1900 + ltm->tm_year;
	int month = 1 + ltm->tm_mon;
	int day = ltm->tm_mday;
	stringstream date; 
	date << "\\s*" << year << '.' << setw(2) << setfill('0') << month;
	date << '.' << setw(2) << setfill('0') << day << "\\s*";
	return date.str();
}

string psstm(string command);
	
string get_url(string url) {//' is needed, be careful : & -> run background
	cout << "loading url : " << url << endl;
	string command = R"(python -c "
import sys, signal
from selenium import webdriver
drv = webdriver.PhantomJS()
drv.get(sys.argv[1])
print (drv.page_source).encode('utf-8')
drv.service.process.send_signal(signal.SIGTERM)
drv.quit()
" ')";
	return psstm(command + url + "'");
}

string analyse_document(string doc)
{
	int bytes = doc.size();
	int shm_fd = shm_open("sharedMEM", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, bytes);
	char* ptr = (char*)mmap(0, bytes, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	strcpy(ptr, doc.data());

	string command = R"(python -c "
from konlpy.tag import Twitter
from konlpy.utils import pprint
from posix_ipc import SharedMemory
import os, sys

f = SharedMemory('sharedMEM')
sz = int(sys.argv[1])
doc = os.read(f.fd, sz)
unidoc = unicode(doc, 'utf-8')
os.close(f.fd)
pos = Twitter().pos(unidoc)
for i in pos: 
	pprint(i[0])
	pprint(i[1])
" )";
	command += to_string(bytes);
	string r = psstm(command);
	shm_unlink("sharedMEM");
	return r;
}


