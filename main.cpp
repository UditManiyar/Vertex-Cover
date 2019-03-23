#include<iostream>
#include "graph.h"
#include "maxmatching.h"
#include "clawfreeGraph.h"
int main(int argv,char* arg[])
{
      graph G;
      G.get_input(arg[1]);

      int temp = 0;

     // do
     // {
     // //       temp = G.removed_edges;
     int n = G.remaining_vertices();
     while(G.reduction_rule1()||G.reduction_rule2())
     {

     }

//      std::cout<<n<<" ---- "<<G.v_cover.size()<<"\n";
     if(G.clawfree_chk()==true)
     {
           clawfreeGraph P(G);
           P.solve(0);

           std::cout<<P.ans<<"\n";
     }

           // std::cout<<"\n";
     // std::vector<std::pair<int,int> > sol = maxmatching::solve(G);
     //
     // std::cout<<sol.size();
     //


     //       G.reduction_edges();
     //       G.calc_degree();
     //
     //       G.kernalization_network_flow();
     //       bipartite S(G);
     //       std::vector<int> cover = S.kernelization();
     //       G.kernelized_output(cover);
     // }
     // while(G.removed_edges!=temp);

//      while(!G.Claw_free())
//      {

//      }
//      //std::cout<<"\n\n\n";

//      //G.Claw_free();


//      // std::cout<<G.m<<"\n";



}
