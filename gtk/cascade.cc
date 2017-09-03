#include<iostream>
#include"cascade.h"
using namespace std;

ComTxt::ComTxt() : Gtk::ComboBoxText(true) 
{
}
void ComTxt::on_changed()
{
	cout << "hi" << endl;
	cout << get_entry_text() << endl;
}

Cascade::Cascade()
{
	Gtk::Expander::add(frame_);
	frame_.add(vbox_);
	vbox_.add(hbox_);
	hbox_.add(firstcombo_);
	firstcombo_.append("HeadTail");
	firstcombo_.append("Mono");
	firstcombo_.append("Text");

	show_all_children();
}

void Cascade::add(Gtk::Widget widget)
{
	vbox_.add(widget);
}

