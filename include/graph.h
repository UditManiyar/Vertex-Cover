#pragma once
#include "edge.h"
// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<utility>
#include <algorithm>
#include "adjlist.h"
class graph
{
public:
      std::vector<Edge> edges_list;
      adjlist adj;
      //std::vector<std:: vector<int> > adj;
      int n,m = 0;
      int s = 0,t;
      int removed_edges = 0;
      std::vector <int> color,degree,v_cover;
      std::vector<std::vector<int> > rule;
      std::queue <int> q;
      std::queue<int> degree_one,degree_two;
      int cnt = 0;


public:
      // void add_edge(int v1,int v2);
      void set_vertices(int vertices,int edges);
      void take_input(char* argument);
      bool bipartite_dfs(int idx,int par);
      bool is_bipartite();
      bool reduction_rule1();
      bool reduction_rule2();
      void adjacent(int current, int neighbour1,int neighbour2);
      void non_adjacent(int current, int neighbour1,int neighbour2);
      //void kernalization_network_flow();
      //void kernelized_output(std::vector<int> &cover);
      bool Claw_free();



};
