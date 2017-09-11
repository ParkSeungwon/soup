#pragma once
#include<gtkmm.h>
#include"xmlmine.h"

class TagCombo : public Gtk::ComboBoxText, public XMLMine
{
public:
	TagCombo(Gtk::Label& label, Gtk::HBox& hbox);
	friend class Cascade;

protected:
	virtual void on_changed();
	Gtk::Label& ref_label_;//a label to describe tag
	Gtk::HBox& ref_hbox_;
	TagCombo *next = nullptr, *prev = nullptr;
	bool isAttr = false;
	
private:
	static std::map<std::string, std::string> tagNdesc_, attrNdesc_, bootNdesc_, tagNboot_;
	static std::map<std::string, std::vector<std::string>> tagNattrs_;
	void combo_free(TagCombo* p);
};

