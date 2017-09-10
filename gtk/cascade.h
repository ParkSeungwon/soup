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
	void add(Cascade& widget);
	void add(TagCombo tag);
	
protected:
	void on_add_click();
	void on_del_click(Cascade* pc, Gtk::HBox* ph, Gtk::Button* pb);
	std::vector<Cascade*> p_inner_tags_;
	std::vector<Gtk::HBox*> p_hboxes_;
	std::vector<Gtk::Button*> p_buttons_;
	Gtk::HBox hbox_;
	Gtk::VBox vbox_;
	Gtk::Frame frame_;
	Gtk::Label label_;
	Gtk::Button add_;
	TagCombo firstcombo_;
};


