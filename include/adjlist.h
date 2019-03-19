#include <vector>
#include <queue>
#pragma once

class adjlist
{
public:
      std::vector<std::vector<int>> adj;
      std::vector<int> degree;
      std::queue<int> degreeOne;
      std::queue<int> degreeTwo;



      void removeVertex(int idx);

      void removeDuplicates();

      void degeneracy();

      void calcDegree();

      void addEdge(int x,int y);

      void setVertices(int n);

      void printlist();

};
