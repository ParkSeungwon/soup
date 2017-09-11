#include<iostream>
#include"util.h"
#include"cascade.h"
using namespace std;

int main(int ac, char** av)
{
	int i = 0;
	auto app = Gtk::Application::create(i, av, "");
	Gtk::Window window;
	Cascade* mono = Gtk::manage(new Cascade());
	string s = "<html><body class='bd-home'><a href='fds'>adgg</a></body><button /><a href='add' class='fd'>fjasjd</a></html>";
	string t= get_url("http://localhost");
	mono->read_html(s);
	window.add(*mono);
	window.show_all_children();
	app->run(window);
}

//	notebook.append_page(scrolledWindow1, "Html view");
//	notebook.append_page(vBox5, "Text view");
//	notebook.signal_switch_page().connect(bind(&GtkMainForm::switch_page, this, _1, _2));
//
