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
//	set_spacing(20);
	Gtk::Expander::add(frame_);
	frame_.set_shadow_type(Gtk::SHADOW_ETCHED_IN);
//	frame_.set_margin_left(20);
	frame_.add(vbox_);
	vbox_.add(hbox_);
	vbox_.pack_end(add_);
	for(int i=0; i<3; i++) hbox_.pack_start(rb_[i], Gtk::PACK_SHRINK);
	rb_[1].join_group(rb_[0]);
	rb_[2].join_group(rb_[0]);
	hbox_.add(firstcombo_);
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
//	vbox_.remove(add_);
	hbox_.remove(text_area_);
	hbox_.pack_start(firstcombo_);
	vbox_.pack_end(add_);
}

void Cascade::on_mono_click()
{
	hbox_.remove(text_area_);
	hbox_.pack_start(firstcombo_);
	vbox_.remove(add_);
}

void Cascade::on_text_click() 
{
	hbox_.remove(firstcombo_);
	vbox_.remove(add_);
	firstcombo_.combo_free(firstcombo_.next);
	hbox_.pack_start(text_area_);
	text_area_.show();
}

Cascade::~Cascade()
{
	firstcombo_.combo_free(firstcombo_.next);
	for(auto* p : p_inner_tags_) delete p;
	for(auto* p : p_hboxes_) delete p;
	for(auto* p : p_buttons_) delete p;
}

void Cascade::on_add_click()
{
	auto* pc = new Cascade();
	auto* pb = new Gtk::Button("-");
	auto* ph = new Gtk::HBox();
	p_inner_tags_.push_back(pc);
	p_hboxes_.push_back(ph);
	p_buttons_.push_back(pb);
	ph->pack_start(*pb, Gtk::PACK_SHRINK);
	ph->pack_start(*pc);
	vbox_.pack_start(*ph);
	vbox_.show_all_children();

	pb->signal_clicked().connect(bind(&Cascade::on_del_click, this, pc, ph, pb));
}

void Cascade::on_del_click(Cascade* pc, Gtk::HBox* ph, Gtk::Button* pb)
{
	delete pc; delete ph; delete pb;
	std::remove(p_inner_tags_.begin(), p_inner_tags_.end(), pc);
	std::remove(p_hboxes_.begin(), p_hboxes_.end(), ph);
	std::remove(p_buttons_.begin(), p_buttons_.end(), pb);
	p_inner_tags_.pop_back();
	p_hboxes_.pop_back();
	p_buttons_.pop_back();
}

