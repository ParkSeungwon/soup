#include"browser.h"
using namespace std;

Winmain::Winmain(string contents, string site)
{
	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	widget_now = Glib::wrap(GTK_WIDGET(webview));
	webkit_web_view_load_html(webview, contents.data(), site.data());
	add(*widget_now);
	show_all_children();
}

