#pragma once
#include<gtkmm.h>

class TagCombo : public Gtk::ComboBoxText
{
public:
	TagCombo(Gtk::Label& label);

protected:
	virtual void on_changed();
	Gtk::Label& ref_label_;//a label to describe tag
	
private:
	static std::map<std::string, std::string> tagNdesc_;
};

class AttrCombo : public TagCombo
{
public:
	AttrCombo(std::string tag, Gtk::Label& label);

private:
	static std::map<std::string, std::vector<std::string>> tagNattrs_;
	static std::map<std::string, std::string> attrNdesc_;
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


