#pragma once
#include<gtkmm.h>
#include<webkit2/webkit2.h>
#include<set>
#include<memory>
#include"scrap.h"

class WinWeb : public Gtk::Window
{
public:
	WinWeb(std::string contents, std::string site);

protected:
	WebKitWebView* webview;
	Gtk::Widget* widget_now;
};

class WinMain : public Gtk::Window
{
public:
	WinMain(std::vector<Sub>&& v);
	virtual ~WinMain();

protected:
	Gtk::ScrolledWindow sc;
	Gtk::VBox vb;
	Gtk::Button* bts;
	void on_click(std::string contents, std::string site, int n);

private:
	std::vector<std::shared_ptr<WinWeb>> shv;
	std::map<std::string, int> like;
	std::vector<Sub> sub;
	std::set<int> choice;
	void read_like();
};
