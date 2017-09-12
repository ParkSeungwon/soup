#include<gtkmm.h>
#include<gtksourceviewmm/view.h>
#include<gtksourceviewmm/languagemanager.h>

class HtmlBook : public Gtk::Notebook
{
public:
	HtmlBook();
	Gsv::View view;
};

