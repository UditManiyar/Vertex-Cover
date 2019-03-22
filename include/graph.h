#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <queue>
class graph
{
public:
      std::vector< std::vector<int> > adj;
      std::queue<int> degree_one,degree_two;
      std::vector<int> color,v_cover;
      int n = 0, m = 0;
      void get_input(char* file_name);
      void set_vertices(int no_vertices);
      bool is_bipartite();
      void remove_vertex(int idx);
      bool reduction_rule1();
}


#endif // GRAPH_H
