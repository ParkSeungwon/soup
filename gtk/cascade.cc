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

TagCombo::TagCombo(Gtk::Label& label, Gtk::HBox& hbox) 
	: Gtk::ComboBoxText(true), ref_label_(label), ref_hbox_{hbox} { }

void TagCombo::combo_free(TagCombo* p)
{//destructor cannot be used
	if(!p) return;
	combo_free(p->next);
	delete p;
}

void TagCombo::on_changed()
{
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

Cascade::Cascade() : firstcombo_{label_, hbox_}, add_{"add"}
{
	set_expanded();
	text_area_.set_size_request(100);
	Gtk::Expander::add(vbox_);
	vbox_.add(hbox_);
	vbox_.pack_end(add_, Gtk::PACK_SHRINK);
	for(int i=0; i<3; i++) hbox_.pack_start(rb_[i], Gtk::PACK_SHRINK);
	rb_[1].join_group(rb_[0]);
	rb_[2].join_group(rb_[0]);
	hbox_.pack_start(firstcombo_, Gtk::PACK_SHRINK);
	vbox_.add(label_);
	for(const auto& p : TagCombo::tagNdesc_) firstcombo_.append(p.first);

	show_all_children();

	add_.signal_clicked().connect(bind(&Cascade::on_add_click, this));
	rb_[0].signal_clicked().connect(bind(&Cascade::on_twin_click, this));
	rb_[1].signal_clicked().connect(bind(&Cascade::on_mono_click, this));
	rb_[2].signal_clicked().connect(bind(&Cascade::on_text_click, this));
}

void Cascade::on_twin_click()
{
	text_box_show(false);
	first_show(true);
	add_show(true);
}

void Cascade::on_mono_click()
{
	text_box_show(false);
	first_show(true);
	add_show(false);
}

void Cascade::on_text_click() 
{
	first_show(false);
	add_show(false);
	text_box_show(true);
}

void Cascade::text_box_show(bool show)
{
	if(text_box_show_ && !show) {
		hbox_.remove(text_area_);
		text_box_show_ = false;
	} else if(!text_box_show_ && show) {
		hbox_.pack_end(text_area_);
		text_box_show_ = true;
		hbox_.show_all_children();
	}
}

void Cascade::first_show(bool show)
{
	if(first_show_ && !show) {
		firstcombo_.combo_free(firstcombo_.next);
		hbox_.remove(firstcombo_);
		first_show_ = false;
	} else if(!first_show_ && show) {
		hbox_.pack_start(firstcombo_, Gtk::PACK_SHRINK);
		first_show_ = true;
	}
}

void Cascade::add_show(bool show)
{
	if(add_show_ && !show) {
		vbox_.remove(add_);
		add_show_ = false;
	} else if(!add_show_ && show) {
		vbox_.pack_end(add_, Gtk::PACK_SHRINK);
		add_show_ = true;
	}
}

Cascade::~Cascade()
{
	firstcombo_.combo_free(firstcombo_.next);
}

void Cascade::on_add_click()
{
	auto* pc = Gtk::manage(new Cascade());
	auto* pb = Gtk::manage(new Gtk::Button("-"));
	auto* ph = Gtk::manage(new Gtk::HBox());
	ph->pack_start(*pb, Gtk::PACK_SHRINK);
	ph->pack_start(*pc, Gtk::PACK_SHRINK);
	vbox_.pack_start(*ph, Gtk::PACK_SHRINK);
	vbox_.show_all_children();

	rb_[1].set_sensitive(false);
	rb_[2].set_sensitive(false);
	pb->signal_clicked().connect(bind(&Cascade::on_del_click, this, ph));
	added_item_count_++;
}

void Cascade::on_del_click(Gtk::HBox* ph)
{
	delete ph;//all the widgets in the box will be deleted automatically
	if(!--added_item_count_) {
		rb_[1].set_sensitive(true);
		rb_[2].set_sensitive(true);
	}
}

