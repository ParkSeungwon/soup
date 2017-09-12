#include"notebook.h"
using namespace std;

HtmlBook::HtmlBook()
{
	view.set_show_line_numbers();
	view.set_auto_indent();
	view.set_highlight_current_line();
	view.set_show_right_margin();
	view.set_right_margin_position(80);
	view.set_tab_width(4);
	view.get_source_buffer()->set_language(Gsv::LanguageManager::create()->get_language("html"));
}

