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

class Cascade : public Gtk::Expander//, public XMLMine
{
public:
	Cascade();
	virtual ~Cascade();
	
protected:
	void on_add_click();
	void on_del_click(Gtk::HBox* ph);
	void on_twin_click(), on_mono_click(), on_text_click();
	Gtk::HBox hbox_;
	Gtk::VBox vbox_;
	Gtk::Label label_;
	Gtk::Button add_;
	Gtk::RadioButton rb_[3];
	Gtk::TextView text_area_;
	TagCombo firstcombo_;

private:
	bool first_show_ = true, text_box_show_ = true, add_show_ = true;
	void first_show(bool show), text_box_show(bool show), add_show(bool show);
	int added_item_count_ = 0;
};


