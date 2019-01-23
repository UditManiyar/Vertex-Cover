#pragma once
#include "edge.h"
#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include<queue>

class bipartite
{
private:
      std::vector<Edge> edges_list;
      std::vector< std::vector<int> > adj;
      int n,m = 0;
      int s = 0,t;
      int total = 0;
      std::vector <int> level,start,alternating,matching,cover,color;
      std::queue <int> q;

public:
      bipartite(graph G);
      bool bfs();
      int dfs(int idx,int flow);
      int solve_dinic();
      void print_vertexcover();
      void chk();
      void travel_alternating(int i);

};
