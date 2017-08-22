#include<iostream>
#include"browser.h"
using namespace std;

string get_url(string);
int main(int ac, char** av)
{
	int i = 0;
	auto app = Gtk::Application::create(i, av, "");
	WinMain window(scrap(av[1]));
	app->run(window);
}

