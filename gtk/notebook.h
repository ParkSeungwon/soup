#include<gtkmm.h>
#include<gtksourceviewmm.h>
#include<webkit2/webkit2.h>
#include"cascade.h"

class HtmlBook : public Gtk::Notebook
{
public:
	HtmlBook(std::string url);

protected:
//	virtual void on_switch_page(Widget* page, guint page_number);
	Gsv::View view;
	Cascade cas;
	WebKitWebView* webview;
	Gtk::Widget* widget_now;
	Gtk::ScrolledWindow scwin[3];
};



