#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <queue>
class graph
{
public:
      std::vector< std::vector<int> > adj,rule;
      std::queue<int> degree_one,degree_two;
      std::vector<int> color,v_cover;
      int n = 0, m = 0;
      void get_input(char* file_name);
      void add_edge(int x,int y);
      int remaining_vertices();
      void remove_duplicates();
      void set_vertices(int no_vertices);
      bool bipartite_dfs(int idx,int par);
      void Bipartite_matching_to_vcover(std::vector<std::pair<int,int>> matching);
      bool is_bipartite();
      void remove_vertex(int idx);
      bool reduction_rule1();
      bool reduction_rule2();
      void adjacent(int current, int neighbour1,int neighbour2);
      void non_adjacent(int current, int neighbour1,int neighbour2);
      void kernalization_network_flow();
      void kernelized_output(std::vector<int> &cover);
      bool clawfree_chk();
      void print();

};
#endif // GRAPH_H
