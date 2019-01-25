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
      int removed_edges = 0;
      std::vector <int> color,degree,v_cover;
      std::queue <int> q;
      std::queue<int> degree_one,degree_two;


public:
      // void add_edge(int v1,int v2);
      void set_vertices(int vertices,int edges);
      void take_input(char* argument);
      bool bipartite_dfs(int idx,int par);
      bool is_bipartite();
      void calc_degree();
      bool reduction_rule1();
      bool reduction_rule2();
      void remove_vertex(int idx);
      void reduction_edges();
      void degeneracy();
      void kernalization_network_flow();
      void kernelized_output(std::vector<int> &cover);


};
