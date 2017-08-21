#include"browser.h"
using namespace std;

string get_url(string);
int main(int ac, char** av)
{
	int i = 0;
	auto app = Gtk::Application::create(i, av, "");
	string s = av[1];
	string site = "http://www.naver.com";
	Winmain window(get_url(s), s);
	window.set_default_size(1600, 1080);
	Winmain win2(get_url(site), site);
	win2.set_default_size(1000, 1080);
	win2.show();
	app->run(window);
}

