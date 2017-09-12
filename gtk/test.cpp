#include<iostream>
#include"util.h"
#include"cascade.h"
#include"notebook.h"
using namespace std;

int main(int ac, char** av)
{
	int i = 0;
	auto app = Gtk::Application::create(i, av, "");
	Gtk::Window window;
	HtmlBook ht;
	window.add(ht);
	window.show_all_children();
	app->run(window);
}

//	notebook.append_page(scrolledWindow1, "Html view");
//	notebook.append_page(vBox5, "Text view");
//	notebook.signal_switch_page().connect(bind(&GtkMainForm::switch_page, this, _1, _2));
//
