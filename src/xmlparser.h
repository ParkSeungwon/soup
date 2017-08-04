#include<map>
#include<string>
#include<memory>
#include<tgraph.h>

typedef std::shared_ptr<std::map<std::string, std::string>> sh_map;
class Parser : public Graph<sh_map>
{//html -> graph structure
public:
	std::string to_html() const;
	void read_html(std::istream& is);
	std::vector<sh_map> find_all(std::string a, std::string b, bool like=false) const;
	sh_map find_parent(sh_map child) const;
	sh_map find(sh_map sp, sh_map parent = nullptr) const;
	std::string to_str(sh_map v) const;
	sh_map find(std::string a, std::string b, sh_map parent = nullptr) const;

private:
	void insert_edge(sh_map shp, std::istream& is);
	std::map<std::string, std::string> parse_bracket(std::istream& is);
	std::string get_bracket(std::istream& is);
	bool is_script = false;
};


