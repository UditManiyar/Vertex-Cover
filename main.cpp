#include<iostream>
#include "graph.h"
#include "bipartite.h"
#include "edge.h"
int main(int argv,char* arg[])
{
      graph G;
      G.take_input(arg[1]);

      if(G.is_bipartite())
      {
                  G.add_SourceSink();
                  bipartite S(G);
                  int flow = S.solve_dinic();
                  S.print_vertexcover();
                  S.chk();
      }


}
