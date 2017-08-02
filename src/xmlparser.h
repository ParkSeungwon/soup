#include<map>
#include<string>
#include<memory>
#include"tgraph.h"

typedef std::map<std::string, std::string> u_map;
class Parser : public Graph<std::shared_ptr<u_map>>
{
public:
	std::string to_html();
	void read_html(std::istream& is);

private:
	void insert_edge(std::shared_ptr<u_map> shp, std::istream& is);
	u_map parse_bracket(std::istream& is);
	std::string to_str(Vertex<std::shared_ptr<u_map>>* v);
};


