#include<iostream>
#include<vector>
#include<fstream>
#include"cascade.h"
#include"util.h"
using namespace std;

static vector<string> t, d, a;
static map<string, string> m;
static int init() 
{//modulized initialization
	auto v = deserialize("tags.ser");
	for(int i=0; i<v.size(); i+=2) m[v[i]] = v[i+1];
	ifstream f("count.txt");
	int n;
	vector<int> vi;
	while(f >> n) vi.push_back(n);
	auto v2 = deserialize("attr_tag.ser");

	return 0;
}
static int k = init();

map<string, string> TagCombo::tagNdesc_ = move(m);
//vector<string> TagCombo::attrs_;// = deserialize("attr_tag.ser");


TagCombo::TagCombo(Gtk::Label& label) : Gtk::ComboBoxText(true), ref_label_(label)
{
	for(const auto& p : tagNdesc_) append(p.first);
}
void TagCombo::on_changed()
{
	ref_label_.set_text(tagNdesc_[get_active_text()]);
}

Cascade::Cascade() : firstcombo_{label_}
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

