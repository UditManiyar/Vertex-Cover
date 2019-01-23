#include<iostream>
#include "graph.h"
#include "bipartite.h"
#include "edge.h"
int main(int argv,char* arg[])
{
      graph G;
      G.take_input(arg[1]);

      G.calc_degree();

      while(G.reduction_rule1()||G.reduction_rule2())
      {

      }


      std::cout<<"Edges in graph : "<<G.m<<"\n";
      std::cout<<"No of Edges Removed : "<<G.removed_edges<<"\n\n";

      // G.reduction_rule1();
      // G.reduction_rule2();
      // if(G.is_bipartite())
      // {
      //       bipartite S(G);
      //       S.Graph_Modify();
      //       int flow = S.solve_dinic();
      //       S.print_vertexcover();
      //       S.chk();
      // }


}
