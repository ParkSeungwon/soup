#pragma once
#include<gtkmm.h>
#include<webkit2/webkit2.h>
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
	WinMain(const std::vector<Sub>& v);
	virtual ~WinMain();

protected:
	Gtk::VBox vb;
	Gtk::Button* bts;
	std::vector<std::shared_ptr<WinWeb>> shv;
	void on_click(std::string contents, std::string site);
};
