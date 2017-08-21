#include"browser.h"
using namespace std;

WinWeb::WinWeb(string contents, string site)
{
	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	widget_now = Glib::wrap(GTK_WIDGET(webview));
	webkit_web_view_load_html(webview, contents.data(), site.data());
	add(*widget_now);
	set_default_size(1200, 1080);
	show_all_children();
}

WinMain::WinMain(const vector<Sub>& sub)
{
	set_default_size(1000, 1080);
	add(vb);
	bts = new Gtk::Button[sub.size()];
	int n = 0;
	for(const auto& a : sub) {
		vb.pack_start(bts[n]);
		bts[n].set_label(a.title);
		bts[n++].signal_clicked().connect(bind(&WinMain::on_click, this, a.contents, a.site));
	}
	show_all_children();
}

WinMain::~WinMain()
{
	delete [] bts;
}

void WinMain::on_click(string contents, string site)
{
	auto sh = make_shared<WinWeb>(contents, site);
	sh->show();
	shv.push_back(sh);
}
