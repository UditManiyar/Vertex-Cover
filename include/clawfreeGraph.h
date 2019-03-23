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
      std::vector< std::vector<int> > adj;

      std::unordered_map< std::pair<int,int>, int, boost::hash<std::pair<int,int>> > adj_mat;

      // std::unordered_map< std::pair<int,int>,int > adj_mat;
      int n = 0;
      clawfreeGraph(graph G);
      void solve(int idx);
      graph* getComplementSubgraph(int v);
      bool regularity_chk(int v,graph* complementSubgrph,graph* left_clique,graph* right_clique);
      void remove_clique(graph * clique);
      bool reducible_clique(graph* clique);
      void reduce_irregular(int idx,graph* complementSubgrph);
      void remove_vertex(int idx);
      bool SubtractioninducesCompleteGraph(int i,graph subgrph);
      std::vector<int> dist2points(int idx);


};
#endif //CLAWFREEGRAPH
