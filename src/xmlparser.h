#include<map>
#include<string>
#include<memory>
#include"tgraph.h"

typedef std::shared_ptr<std::map<std::string, std::string>> sh_map;
//<meta href="http://~~" name="" />
//{{"Mono":"meta"}, {"href":"http://~~"}, {"name":""}}
//first can be Mono, Text, HeadTail

class Parser : public Graph<sh_map>
{//html -> graph structure
public:
	std::string to_str(sh_map sh = nullptr) const;//translate child nodes to string
	void read_html(std::istream& is);//construct graph by reading html stream
	sh_map find_parent(sh_map child) const;
	std::vector<sh_map> find(std::string a, std::string b, sh_map parent = nullptr, bool like = false);

private:
	std::vector<sh_map> vec;
	bool is_script = false;

	void find_all(std::string first, std::string second, sh_map parent, bool like);
	void insert_edge(sh_map shp, std::istream& is);
	std::map<std::string, std::string> parse_bracket(std::istream& is);
	std::string get_bracket(std::istream& is);
	void rfind(std::string a, std::string b, sh_map parent = nullptr) const;
};


