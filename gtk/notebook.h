#include<gtkmm.h>
#include<gtksourceviewmm/view.h>
#include<gtksourceviewmm/languagemanager.h>
#include<webkit2/webkit2.h>
#include"cascade.h"

class HtmlBook : public Gtk::Notebook
{
public:
	HtmlBook();

protected:
	Gsv::View view;
	Cascade cas;
	WebKitWebView* webview;
	Gtk::Widget* widget_now;
	Gtk::ScrolledWindow scwin[3];
};



