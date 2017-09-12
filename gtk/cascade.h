#pragma once
#include<list>
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
	std::map<std::string, std::string> get();//firstcombo_ chain -> map
	virtual ~Cascade();
	void read_html(std::string s);
	std::string to_html();
	
protected:
	void on_add_click(const std::map<std::string, std::string>& m, Cascade*& p);
	void on_del_click(Gtk::HBox* ph, Cascade* pc);
	void on_twin_click(), on_mono_click(), on_text_click();
	Gtk::HBox hbox_;
	Gtk::VBox vbox_;
	Gtk::Label label_;
	Gtk::Button add_;
	Gtk::RadioButton rb_[3];//head_tail, mono, text select
	Gtk::TextView text_area_;
	TagCombo firstcombo_;//combotext chain
	static FParser parser_;//friendly parser used by layers of cascades

private:
	void to_widget(Vertex<sh_map>* v);
	void construct_graph(sh_map shp);
	bool first_show_ = true, text_box_show_ = true, add_show_ = true;
	void first_show(bool show), text_box_show(bool show), add_show(bool show);
	std::list<Cascade*> added_item_;//inner cascades, list can easily remove elem
};


