#include<iostream>
#include<vector>
#include<fstream>
#include"cascade.h"
#include"util.h"
using namespace std;

static map<string, string> m, m1, bNd, tNb;
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
	ifstream f3{"boot.txt"};
	while(getline(f3, s1)) {
		getline(f3, s2);
		s1.erase(0, 1);
		stringstream ss; ss << s1;
		ss >> s1;
		bNd[s1] = s2;
		ss >> s2;
		for(char& c : s2) c = tolower(c);
		for(auto& a : m) if(s2.find(a.first) != string::npos) tNb[a.first] = s1;
	}
	return 0;
}
static int k = init();

map<string, string> TagCombo::tagNdesc_ = move(m);
map<string, string> TagCombo::attrNdesc_ = move(m1);
map<string, string> TagCombo::bootNdesc_ = move(bNd);
map<string, string> TagCombo::tagNboot_ = move(tNb);
map<string, vector<string>> TagCombo::tagNattrs_ = move(m2);

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

