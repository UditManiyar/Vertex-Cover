#include "maxmatching.h"
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <utility>
#include <iostream>
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> my_graph;

std::vector<std::pair<int,int>> maxmatching::solve(graph G)
{
      my_graph g;
      for(int i = 0 ;i<=G.n;i++)
      {
            for(auto j : G.adj[i])
            {
                  if(i>j)
                  {
                        boost::add_edge(i,j,g);
                  }
                  else
                  {
                        break;
                  }
            }
      }
      std::vector<boost::graph_traits<my_graph>::vertex_descriptor> mate(G.n+1);

      boost::checked_edmonds_maximum_cardinality_matching(g, &mate[0]);

      // std::cout<< matching_size(g, &mate[0]) << std::endl;

      std::vector<std::pair<int,int>> matching;

      boost::graph_traits<my_graph>::vertex_iterator vi, vi_end;

      for(boost::tie(vi,vi_end) = boost::vertices(g); vi != vi_end; ++vi)
      {
            if (mate[*vi] != boost::graph_traits<my_graph>::null_vertex() && *vi < mate[*vi])
            {
                  matching.push_back(std::make_pair(*vi,mate[*vi]));
                  //std::cout << "{" << *vi << ", " << mate[*vi] << "}" << std::endl;
            }
      }

      return matching;
}
