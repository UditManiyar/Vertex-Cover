#pragma once
#include "edge.h"
// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include<queue>


class graph
{
public:
      std::vector<Edge> edges_list;
      std::vector<std:: vector<int> > adj;
      int n,m = 0;
      int s = 0,t;
      std::vector <int> color;
      std::queue <int> q;

public:
      void add_edge(int v1,int v2);
      void set_vertices(int vertices);
      void take_input(char* argument);
      bool bipartite_dfs(int idx,int par);
      bool is_bipartite();
      void add_SourceSink();

};
