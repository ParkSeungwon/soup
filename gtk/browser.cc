#include<algorithm>
#include<fstream>
#include"browser.h"
using namespace std;

WinWeb::WinWeb(string contents, string site)
{
	webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
	widget_now = Glib::wrap(GTK_WIDGET(webview));
	webkit_web_view_load_html(webview, contents.data(), site.data());
	add(*widget_now);
	set_title(site);
	set_default_size(1200, 1080);
	show_all_children();
}

WinMain::WinMain(vector<Sub>&& vsub)
{
	read_like();
	sub = std::move(vsub);
	for(auto& a : sub) for(auto& b : a.keyword) a.score += b.second * like[b.first];
	auto it = remove_if(sub.begin(), sub.end(), [](const Sub& s) { return s.score < 0;});
	sub.erase(it, sub.end());

	set_default_size(500, 1080);
	add(sc);
	sc.add(vb);
	bts = new Gtk::Button[sub.size()];
	int n = 0;
	for(const auto& a : sub) {
		vb.pack_start(bts[n], Gtk::PACK_SHRINK);
		bts[n].set_label(a.title + ' ' + to_string(a.score));
		bts[n].signal_clicked().connect(bind(&WinMain::on_click, this, a.contents, a.site, n));
		n++;
	}
	show_all_children();
}

WinMain::~WinMain()
{
	delete [] bts;
	for(int i=0; i<sub.size(); i++) {
		int k = choice.find(i) == choice.end() ? -1 : 2;//if it is a chosen one
		for(auto& a : sub[i].keyword) like[a.first] += a.second * k;
	}
	ofstream f("like.txt");
	for(auto& a : like) f << a.first << ' ' << a.second << endl;
}

void WinMain::read_like()
{
	ifstream f("like.txt");
	string keyword;
	int score;
	while(f >> keyword >> score) like[keyword] = score;
}

void WinMain::on_click(string contents, string site, int n)
{
	auto sh = make_shared<WinWeb>(contents, site);
	sh->show();
	shv.push_back(sh);
	choice.insert(n);
}
