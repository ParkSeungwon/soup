#pragma once
#include<gtkmm.h>

class TagCombo : public Gtk::ComboBoxText
{
public:
	TagCombo(Gtk::Label& label);

protected:
	virtual void on_changed();
	static std::map<std::string, std::string> tagNdesc_;
	
private:
	Gtk::Label& ref_label_;//a label to describe tag
};

class AttrCombo : public Gtk::ComboBoxText
{
public:
	AttrCombo();

protected:
};
class Cascade : public Gtk::Expander
{
public:
	Cascade();
	void add(Gtk::Widget widget); 
	
protected:
	Gtk::HBox hbox_;
	Gtk::VBox vbox_;
	Gtk::Frame frame_;
	Gtk::Label label_;
	TagCombo firstcombo_;
};


