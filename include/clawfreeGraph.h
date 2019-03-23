#ifndef CLAWFREEGRAPH
#define CLAWFREEGRAPH
#include "graph.h"
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include<unordered_set>
#include <utility>
class clawfreeGraph
{
public:
      int ans= 0;
      std::vector< std::vector<int> > adj;
      std::vector<int> neighbour;
      std::unordered_set<int> neighbourOfSet;

      std::unordered_map< std::pair<int,int>, int, boost::hash<std::pair<int,int>> > adj_mat;

      // std::unordered_map< std::pair<int,int>,int > adj_mat;
      int n = 0;
      clawfreeGraph(graph G);
      void solve(int idx);
      graph* getComplementSubgraph(int v);
      bool regularity_chk(int v,graph** complementSubgrph,std::vector<int> &left_clique,std::vector<int> &right_clique);
      void remove_clique(std::vector<int> &clique);
      bool reducible_clique(std::vector<int> &clique);
      void reduce_irregular(int idx,graph* complementSubgrph);
      void remove_vertex(int idx);
      bool SubtractioninducesCompleteGraph(int i,graph subgrph);
      std::unordered_set<int>dist2points(int idx);
      void CliqueEdgesAdd(std::vector<int> &clique);
      void add_edge(int x,int y);
      void remove_duplicates();


};
#endif //CLAWFREEGRAPH
