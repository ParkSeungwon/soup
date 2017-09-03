#pragma once
#include<gtkmm.h>

class ComTxt : public Gtk::ComboBoxText
{
public:
	ComTxt();

protected:
	virtual void on_changed();
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
	ComTxt firstcombo_;
};


