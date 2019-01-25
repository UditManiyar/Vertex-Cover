#include<iostream>
#include "graph.h"
#include "bipartite.h"
#include "edge.h"
int main(int argv,char* arg[])
{
      graph G;
      G.take_input(arg[1]);

int temp = 0;

      do
      {
            temp = G.removed_edges;
            // G.calc_degree();
            // while(G.reduction_rule1()||G.reduction_rule2())
            // {
            //
            // }
            // G.reduction_edges();
            // G.calc_degree();

            G.kernalization_network_flow();
            bipartite S(G);
            std::vector<int> cover = S.kernelization();
            G.kernelized_output(cover);
      }
      while(G.removed_edges!=temp);
      std::cout<<G.removed_edges<<"\n";
}
