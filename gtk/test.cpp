#include<iostream>
#include"cascade.h"
using namespace std;

int main(int ac, char** av)
{
	int i = 0;
	auto app = Gtk::Application::create(i, av, "");
	Gtk::Window window;
	Cascade* mono = Gtk::manage(new Cascade());
	window.add(*mono);
	window.show_all_children();
	app->run(window);
}


