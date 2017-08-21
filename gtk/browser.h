#pragma once
#include<gtkmm.h>
#include<webkit2/webkit2.h>

class Winmain : public Gtk::Window
{
public:
	Winmain(std::string contents, std::string site);

protected:
	WebKitWebView* webview;
	Gtk::Widget* widget_now;
};
