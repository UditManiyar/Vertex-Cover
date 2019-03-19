#include "adjlist.h"
#include <set>
#include <utility>
#include <iostream>
#include <limits.h>
void adjlist::removeVertex(int idx)
{
      for(auto i : adj[idx])
      {
            int pos = std::lower_bound(adj[i].begin(),adj[i].end(),idx)-adj[i].begin();
            if(adj[i][pos]==idx)
            {
                  //removed_edges++;
                  adj[i].erase(adj[i].begin()+pos);
                  degree[i] = adj[i].size();
            }
            if(adj[i].size()==1)
            {
                  degreeOne.push(i);
            }
            else if(adj[i].size()==2)
            {
                  degreeTwo.push(i);
            }
      }
      adj[idx].clear();
      degree[idx] = adj[idx].size();
}
void adjlist::removeDuplicates()
{
      std::set <std::pair<int,int>> unique;
      for(int i = 0 ;i <adj.size(); i++)
      {
            for(auto j: adj[i])
            {
                  if(i>j)
                  {
                        unique.insert(std::make_pair(j,i));
                  }
            }
      }
      for(int i = 0;i<adj.size();i++)
      {
            adj[i].clear();
      }
      int n = adj.size();
      adj.clear();
      for(auto edge: unique)
      {
            int x = edge.first;
            int y = edge.second;
            setVertices(n);
            addEdge(x,y);
      }
}

void adjlist::addEdge(int x,int y)
{
      adj[x].push_back(y);
      adj[y].push_back(x);
}
void adjlist::printlist()
{
      for(int i = 0;i<adj.size();i++)
      {
            std::cout<<i<<" ----->";
            for(auto j : adj[i])
            {
                  std::cout<<j<<" ";
            }
            std::cout<<"\n";
      }
}

void adjlist::setVertices(int n)
{
      adj.resize(n+1);
}


void adjlist::calcDegree()
{

      fill(degree.begin(),degree.end(),0);
      for(int i = 1;i<adj.size();i++)
      {
            degree[i] = adj[i].size();
            if(degree[i]==1)
            {
                  degreeOne.push(i);
            }
            else if(degree[i]==2)
            {
                  degreeTwo.push(i);
            }
      }
}


void adjlist::degeneracy()
{
      calcDegree();
      int maxn = INT_MIN;
      int idx = 1;
      int n = adj.size();
      for(int j = 1;j<n;j++)
      {
            int minx = INT_MAX;
            for(int i = 1;i<n;i++)
            {
                  if(degree[i]>0&&minx>degree[i])
                  {
                        idx = i;
                        minx = std::min(minx,degree[i]);
                  }
            }
            degree[idx] = 0;
            if(minx==INT_MAX)
            {
                  break;
            }
            maxn = std::max(minx,maxn);
            for(auto i :adj[idx])
            {
                  degree[i]--;
            }
      }
      maxn = std::max(maxn,0);
      std::cout<<maxn<<"\n";
}
