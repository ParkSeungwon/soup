#include"util.h"
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
	Gsv::init();//should include gtksourceviewmm.h
	view.get_source_buffer()->set_language(Gsv::LanguageManager::get_default()->get_language("html"));
//	view.get_source_buffer()->set_highlight_syntax();
//	string t = "<html><head><script>function f(){}</script></head><body class='bd-home'><a href='fds'>adgg</a></body><button /><a href='add' class='fd'>fjasjd</a></html>";
	string t = get_url("http://localhost");
	cas.read_html(t);
	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	widget_now = Glib::wrap(GTK_WIDGET(webview));
	string txt = cas.to_html();
	webkit_web_view_load_html(webview, txt.data(), "");
	view.get_source_buffer()->set_text(txt);
	scwin[0].add(cas);
	scwin[1].add(view);
	scwin[2].add(*widget_now);
	
	append_page(scwin[0], "gui editor");
	append_page(scwin[1], "text editor");
	append_page(scwin[2], "web page");
}

