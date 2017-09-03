#include<iostream>
#include<vector>
#include"cascade.h"
#include"util.h"
using namespace std;

static vector<string> t, d;
static int init() {
	cout << "here" << endl;
	auto v = deserialize("tags.ser");
	for(int i=0; i<v.size(); i+=2) {
		t.push_back(v[i]);
		d.push_back(v[i+1]);
	}
	return 0;
}
static int k = init();

vector<string> ComTxt::tags_ = move(t);
vector<string> ComTxt::attrs_;// = deserialize("attr_tag.ser");
vector<string> ComTxt::desc_ = move(d);


ComTxt::ComTxt() : Gtk::ComboBoxText(true) 
{
	for(auto s : tags_) append(s);
}
void ComTxt::on_changed()
{
	cout << get_entry_text() << endl;
}

Cascade::Cascade()
{
	Gtk::Expander::add(frame_);
	frame_.add(vbox_);
	vbox_.add(hbox_);
	hbox_.add(firstcombo_);
	hbox_.add(label_);
//	firstcombo_.append("HeadTail");
//	firstcombo_.append("Mono");
//	firstcombo_.append("Text");

	show_all_children();
}

void Cascade::add(Gtk::Widget widget)
{
	vbox_.add(widget);
}

