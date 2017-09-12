#include<random>
#include"cascade.h"
using namespace std;

FParser Cascade::parser_;
void Cascade::set(const std::map<string, string>& m)
{//add widgets with data in map
	if(m.empty()) return;
	auto it = m.cbegin();
	if(it->first == "Text") {
		rb_[2].set_active();
		text_area_.get_buffer()->set_text(it->second);
	} else {
		if(it->first == "HeadTail") rb_[0].set_active();
		else if(it->first == "Mono") rb_[1].set_active();

		firstcombo_.get_entry()->set_text(it->second);
		firstcombo_.on_changed();
		TagCombo* p = firstcombo_.next;
		for(it++; it != m.cend(); it++) {
			p->get_entry()->set_text(it->first);
			p->on_changed();//set_entry_text only show what's in the option
			p->next->get_entry()->set_text(it->second);
			p->next->on_changed();//while set_text above will show any text
			p = p->next->next;
		}
	}
}

static uniform_int_distribution<> di{0, 65535};
static random_device rd;

Cascade::Cascade() : firstcombo_{label_, hbox_}, add_{"add"}
{
	Gdk::RGBA color;
	color.set_rgba_u(di(rd), di(rd), di(rd));
	firstcombo_.override_background_color(Gdk::RGBA("blue"));
	vbox_.override_background_color(color);
	set_expanded();
	text_area_.set_size_request(100);
	Gtk::Expander::add(vbox_);
	vbox_.add(hbox_);
	vbox_.pack_end(add_, Gtk::PACK_SHRINK);
	for(int i=0; i<3; i++) hbox_.pack_start(rb_[i], Gtk::PACK_SHRINK);
	rb_[1].join_group(rb_[0]);
	rb_[2].join_group(rb_[0]);
	hbox_.pack_start(firstcombo_, Gtk::PACK_SHRINK);
	vbox_.add(label_);
	for(const auto& p : TagCombo::tagNdesc_) firstcombo_.append(p.first);
	show_all_children();

	Cascade* pc;
	add_.signal_clicked().connect(
			bind(&Cascade::on_add_click, this, std::map<string,string>{}, pc));
	rb_[0].signal_clicked().connect(bind(&Cascade::on_twin_click, this));
	rb_[1].signal_clicked().connect(bind(&Cascade::on_mono_click, this));
	rb_[2].signal_clicked().connect(bind(&Cascade::on_text_click, this));
}

void Cascade::on_twin_click()
{
	text_box_show(false);
	first_show(true);
	add_show(true);
}

void Cascade::on_mono_click()
{
	text_box_show(false);
	first_show(true);
	add_show(false);
}

void Cascade::on_text_click() 
{
	first_show(false);
	add_show(false);
	text_box_show(true);
}

void Cascade::text_box_show(bool show)
{
	if(text_box_show_ && !show) {
		hbox_.remove(text_area_);
		text_box_show_ = false;
	} else if(!text_box_show_ && show) {
		hbox_.pack_end(text_area_);
		text_box_show_ = true;
		hbox_.show_all_children();
	}
}

void Cascade::first_show(bool show)
{
	if(first_show_ && !show) {
		firstcombo_.combo_free(firstcombo_.next);
		hbox_.remove(firstcombo_);
		first_show_ = false;
	} else if(!first_show_ && show) {
		hbox_.pack_start(firstcombo_, Gtk::PACK_SHRINK);
		first_show_ = true;
	}
}

void Cascade::add_show(bool show)
{
	if(add_show_ && !show) {
		vbox_.remove(add_);
		add_show_ = false;
	} else if(!add_show_ && show) {
		vbox_.pack_end(add_, Gtk::PACK_SHRINK);
		add_show_ = true;
	}
}

Cascade::~Cascade()
{
	firstcombo_.combo_free(firstcombo_.next);
}

void Cascade::on_add_click(const std::map<std::string, std::string>& m, Cascade*& pc)
{//add inner cascade expander
	pc = Gtk::manage(new Cascade());
	auto* pb = Gtk::manage(new Gtk::Button("-"));
	auto* ph = Gtk::manage(new Gtk::HBox());
	pc->set(m);
	ph->pack_start(*pb, Gtk::PACK_SHRINK);
	ph->set_margin_left(10);
	ph->pack_start(*pc, Gtk::PACK_SHRINK);
	vbox_.pack_start(*ph, Gtk::PACK_SHRINK);
	vbox_.show_all_children();

	rb_[1].set_sensitive(false);
	rb_[2].set_sensitive(false);
	pb->signal_clicked().connect(bind(&Cascade::on_del_click, this, ph));
	added_item_count_++;
	show_all_children();
}

void Cascade::on_del_click(Gtk::HBox* ph)
{
	delete ph;//all the widgets in the box will be deleted automatically
	if(!--added_item_count_) {
		rb_[1].set_sensitive(true);
		rb_[2].set_sensitive(true);
	}
}

void Cascade::read_html(string s)
{
	parser_.gfree(parser_.root);
	parser_.read_html(s);
	set(*parser_.root->data);
	to_widget(parser_.root);
	parser_.view();
}

void Cascade::to_widget(Vertex<sh_map>* ver)
{
	for(auto* e = ver->edge; e; e = e->edge) {
		Cascade* p;
		on_add_click(*e->vertex->data, p);
		p->to_widget(e->vertex);
	}
}
