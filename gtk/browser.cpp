#include"browser.h"
using namespace std;

string get_url(string);
int main(int ac, char** av)
{
	int i = 0;
	auto app = Gtk::Application::create(i, av, "");
	Scrap scrap{av[1]};
	WinMain window(scrap.v);
	app->run(window);
}

