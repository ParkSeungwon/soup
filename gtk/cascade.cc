#include<iostream>
#include<vector>
#include<fstream>
#include"cascade.h"
#include"util.h"
using namespace std;

TagCombo::TagCombo(Gtk::Label& label) : Gtk::ComboBoxText(true), ref_label_(label) { }

Cascade::Cascade() : firstcombo_{label_}
{
	for(const auto& p : XMLMine::tag2_) firstcombo_.append(p.first);
}

void TagCombo::on_changed()
{
	ref_label_.set_text(tagNdesc_[get_active_text()]);
}

void Cascade::add(Gtk::Widget widget)
{
	vbox_.add(widget);
}

