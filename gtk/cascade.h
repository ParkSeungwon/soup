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
	static std::map<std::string, std::string> tagNdesc_;
	static std::map<std::string, std::vector<std::string>> tagNattrs_;
	static std::map<std::string, std::string> attrNdesc_;
	static std::map<std::string, std::string> bootNdesc_;
	static std::map<std::string, std::string> tagNboot_;
	void combo_free(TagCombo* p);
};

class Cascade : public Gtk::Expander//, public XMLMine
{
public:
	Cascade();
	virtual ~Cascade();
	
protected:
	void on_add_click();
	void on_del_click(Cascade* pc, Gtk::HBox* ph, Gtk::Button* pb);
	void on_twin_click(), on_mono_click(), on_text_click();
	std::vector<Cascade*> p_inner_tags_;
	std::vector<Gtk::HBox*> p_hboxes_;
	std::vector<Gtk::Button*> p_buttons_;
	Gtk::HBox hbox_;
	Gtk::VBox vbox_;
	Gtk::Frame frame_;
	Gtk::Label label_;
	Gtk::Button add_;
	Gtk::RadioButton rb_[3];
	Gtk::TextView text_area_;
	TagCombo firstcombo_;

private:
	bool first_show_ = true, text_box_show_ = true, add_show_ = true;
	void first_show(bool show), text_box_show(bool show), add_show(bool show);
};


