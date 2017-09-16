#include"util.h"
#include"notebook.h"
using namespace std;

HtmlBook::HtmlBook(string url)
{
	url_ = url;
	content_ = get_url(url);
	view.set_show_line_numbers();
	view.set_auto_indent();
	view.set_highlight_current_line();
	view.set_show_right_margin();
	view.set_right_margin_position(80);
	view.set_tab_width(4);
	view.get_source_buffer()->set_language(Gsv::LanguageManager::get_default()->get_language("html"));
//	view.get_source_buffer()->set_highlight_syntax();
//	string t = "<html><head><script>function f(){}</script></head><body class='bd-home'><a href='fds'>adgg</a></body><button /><a href='add' class='fd'>fjasjd</a></html>";
	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	widget_now = Glib::wrap(GTK_WIDGET(webview));
	scwin[0].add(cas);
	scwin[1].add(view);
	scwin[2].add(*widget_now);
	append_page(scwin[0], "gui editor");
	append_page(scwin[1], "text editor");
	append_page(scwin[2], "web page");
	set_current_page(0);
}

void HtmlBook::on_switch_page(Widget* page, guint page_number)
{
	if(page_ == page_number) return;
	cout << "switching to " << page_number << endl;
	switch(page_number) {
		case 0: 
	//		content_ = view.get_source_buffer()->get_text();
			cas.read_html(content_); page_ = 0; 
			break;
		case 1: 
	//		content_ = cas.to_html();
			view.get_source_buffer()->set_text(content_); page_ = 1; 
			break;
		case 2: 
	//		content_ = view.get_source_buffer()->get_text();
			webkit_web_view_load_html(webview, content_.data(), url_.data());
			page_ = 2;
	}
	show_all_children();
}
