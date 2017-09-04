#include<iostream>
#include<vector>
#include<fstream>
#include"cascade.h"
#include"util.h"
using namespace std;

static map<string, string> m, m1;
static map<string, vector<string>> m2;
static int init() 
{//modulized initialization
	string s1, s2;
	ifstream f1("tags.txt");
	while(getline(f1, s1)) {
		getline(f1, s2);
		m[s1] = s2;
	}
	ifstream f2("attr.txt");
	while(getline(f2, s1)) {
		getline(f2, s2);
		stringstream ss;
		ss << s1;
		ss >> s1;
		m1[s1] = s2;
		while(ss >> s2) m2[s1].push_back(s2);
	}

	return 0;
}
static int k = init();

map<string, string> TagCombo::tagNdesc_ = move(m);
map<string, string> AttrCombo::attrNdesc_ = move(m1);
map<string, vector<string>> AttrCombo::tagNattrs_ = move(m2);

TagCombo::TagCombo(Gtk::Label& label) : Gtk::ComboBoxText(true), ref_label_(label)
{
	for(const auto& p : tagNdesc_) append(p.first);
}
void TagCombo::on_changed()
{
	ref_label_.set_text(tagNdesc_[get_active_text()]);
}

AttrCombo::AttrCombo(string tag, Gtk::Label& label) : TagCombo{label}
{
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

