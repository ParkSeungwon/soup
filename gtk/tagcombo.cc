#include<iostream>
#include<vector>
#include<fstream>
#include"tagcombo.h"
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

TagCombo::TagCombo(Gtk::Label& label, Gtk::HBox& hbox) 
	: Gtk::ComboBoxText(true), ref_label_(label), ref_hbox_{hbox} { }

void TagCombo::combo_free(TagCombo* p)
{//destructor cannot be used
	if(!p) return;
	combo_free(p->next);
	delete p;
}

void TagCombo::on_changed()
{//automatically add next widget when combotext is selected
	string text = get_active_text();
	TagCombo* p = this;
	while(p->prev) p = p->prev;
	string tag = p->get_active_text();//find the first tag
	string description;
	if(!prev) description = tagNdesc_[text];//if <Tag />
	else if(isAttr) description = attrNdesc_[text];
	else description = bootNdesc_[text];
	ref_label_.set_text(description);

	if(next) combo_free(next);//free below chain of TagCombo
	next = new TagCombo{ref_label_, ref_hbox_};
	next->prev = this;
	next->isAttr = !isAttr;
	if(next->isAttr) for(auto& a : attr2_[tag]) next->append(a.first);
	else for(auto& a : attr3_[tag][text]) next->append(a.first);
	ref_hbox_.pack_start(*next, Gtk::PACK_SHRINK);
	next->show();
}

