#pragma once
#include"tagcombo.h"

class FParser : public Parser
{
	friend class Cascade;
};

class Cascade : public Gtk::Expander//, public XMLMine
{
public:
	Cascade();
	void set(const std::map<std::string, std::string>& m);
	virtual ~Cascade();
	void read_html(std::string s);
	
protected:
	void on_add_click(const std::map<std::string, std::string>& m, Cascade*& p);
	void on_del_click(Gtk::HBox* ph);
	void on_twin_click(), on_mono_click(), on_text_click();
	Gtk::HBox hbox_;
	Gtk::VBox vbox_;
	Gtk::Label label_;
	Gtk::Button add_;
	Gtk::RadioButton rb_[3];
	Gtk::TextView text_area_;
	TagCombo firstcombo_;
	static FParser parser_;

private:
	void to_widget(Vertex<sh_map>* v);
	bool first_show_ = true, text_box_show_ = true, add_show_ = true;
	void first_show(bool show), text_box_show(bool show), add_show(bool show);
	int added_item_count_ = 0;
};


