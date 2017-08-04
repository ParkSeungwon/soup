#include<map>
#include<string>
#include<memory>
#include<tgraph.h>

typedef std::map<std::string, std::string> u_map;
class Parser : public Graph<std::shared_ptr<u_map>>
{//html -> graph structure
public:
	std::string to_html();
	void read_html(std::istream& is);
	std::vector<std::shared_ptr<u_map>> find_all(std::string a, std::string b);
	Vertex<std::shared_ptr<u_map>>* find_parent(Vertex<std::shared_ptr<u_map>>* child);
	Vertex<std::shared_ptr<u_map>>* find(std::shared_ptr<u_map> sp, Vertex<std::shared_ptr<u_map>>* v = nullptr);
	std::string to_str(Vertex<std::shared_ptr<u_map>>* v);
	Vertex<std::shared_ptr<u_map>>* find(std::string a, std::string b, Vertex<std::shared_ptr<u_map>>* parent = nullptr);

private:
	void insert_edge(std::shared_ptr<u_map> shp, std::istream& is);
	u_map parse_bracket(std::istream& is);
	std::string get_bracket(std::istream& is);
};


