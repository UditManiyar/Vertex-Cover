#include"clawfreeGraph.h"
#include<iostream>
#include<stdlib.h>

clawfreeGraph::clawfreeGraph(graph G)
{
      adj = G.adj;
      n = G.n;
      for(int i = 0;i<=n;i++)
      {
            for(int j:adj[i])
            {
                  adj_mat[std::make_pair(i,j)] = 1;
            }
      }

}

void clawfreeGraph::solve(int idx)
{
      if(idx==n+1)
      {
            return;
      }

      if(adj[idx].size()>0)
      {

            graph *complementSubgrph = new(graph);
            std::vector<int> left_clique,right_clique ;

            bool regular = regularity_chk(idx,&complementSubgrph,left_clique,right_clique);

            //Vertex idx is irregular
            if(regular==false)
            {
                  //Reduce Irregular Point
                  std::cout<<idx<<"--->ir------";
                  reduce_irregular(idx,complementSubgrph);
                  std::cout<<"\n";
                  ans+=2;

                  return solve(idx+1);
            }
            //Vertex is regular
            else
            {

                  //Next...
                  if(reducible_clique(left_clique))
                  {
                        ans+=1;
                        CliqueEdgesAdd(left_clique);
                        std::cout<<idx<<"---->rc";
                        remove_clique(left_clique);
                        std::cout<<"\n";
                        return solve(idx+1);


                  }

                  else if(reducible_clique(right_clique))
                  {

                        ans+=1;
                        CliqueEdgesAdd(right_clique);
                        std::cout<<idx<<"---->rc ------";
                        remove_clique(right_clique);
                        std::cout<<"\n";
                        return solve(idx+1);


                  }
                  //Chk if left_clique or right_clique is reducible
                  //If one of them is reducible reduce else fasak..
            }

      }
      idx++;
      while(idx<=n&&adj[idx].size()==0)
      {
            idx++;
      }
      return solve(idx);
}

void clawfreeGraph::remove_clique(std::vector<int> &clique)
{
      for(int i:clique)
      {
            remove_vertex(i);
      }
}

void clawfreeGraph::CliqueEdgesAdd(std::vector<int> &clique)
{
      for(int i: neighbourOfSet)
      {
            std::vector<int> pre(n+1,0);
            for(int k : adj[i])
            {
                  pre[k]++;
            }
            for(int j:neighbourOfSet)
            {

                  if(i>j)
                  {
                        int foo = 0;
                        std::vector<int> cnt(pre);
                        for(int k : adj[i])
                        {
                              cnt[k]++;
                        }
                        for(int k : clique)
                        {
                              if(cnt[k]==0)
                              {
                                    foo = 1;
                                    break;
                              }
                              cnt[k]--;
                        }
                        if(foo==0)
                        {
                              add_edge(i,j);
                        }
                  }
            }
      }
}
void clawfreeGraph::add_edge(int x,int y)
{

      int insertion_pt = std::upper_bound(adj[x].begin(),adj[x].end(),y)-adj[x].begin();
      if(adj[x][insertion_pt]!=y)
      {
            adj[x].insert(adj[x].begin()+insertion_pt,y);
      }
      adj_mat[std::make_pair(x,y)] = 1;

      insertion_pt = std::upper_bound(adj[y].begin(),adj[y].end(),x)-adj[y].begin();
      if(adj[y][insertion_pt]!=x)
      {
            adj[y].insert(adj[y].begin()+insertion_pt,x);
      }
      adj_mat[std::make_pair(y,x)] = 1;
}
bool clawfreeGraph::reducible_clique(std::vector<int> &clique)
{
      graph grph;
      grph.set_vertices(n);
      neighbourOfSet.clear();
      for(int i : clique)
      {
            for(int j: adj[i])
            {
                  neighbourOfSet.insert(j);
            }
      }
      for(int i:clique)
      {
            neighbourOfSet.erase(i);
      }

      bool flag = true;
      for(auto i : neighbourOfSet)
      {
            for(auto j:neighbourOfSet)
            {
                  if(adj_mat[std::make_pair(i,j)]==0&&i!=j)
                  {
                        for(int k:neighbourOfSet)
                        {
                              if(adj_mat[std::make_pair(i,k)]==0&&adj_mat[std::make_pair(j,k)]==0&&k!=i&&k!=j)
                              {
                                    flag = false;
                                    break;
                              }
                        }
                  }
                  if(flag==false)
                  {
                        break;
                  }
            }
            if(flag==false)
            {
                  break;
            }
      }

      return flag;
}
void clawfreeGraph::reduce_irregular(int idx,graph* complementSubgrph)
{
      std::unordered_set<int> dist2pnts = dist2points(idx);
      std::vector<int> Y;

      for(int i: dist2pnts)
      {
            if(SubtractioninducesCompleteGraph(i,*complementSubgrph))
            {
                  Y.push_back(i);
            }
      }

      for(int i: Y)
      {
            dist2pnts.erase(i);
            remove_vertex(i);
      }

      std::vector<int> temp = adj[idx];
      for(int i:temp)
      {
            remove_vertex(i);
      }

      remove_vertex(idx);
      for(int i:dist2pnts)
      {
            for(int j:dist2pnts)
            {
                  if(i>j)
                  {
                        if(adj_mat[std::make_pair(i,j)]==0&&adj_mat[std::make_pair(j,i)]==0)
                        {
                              add_edge(i,j);
                        }
                  }
            }
      }
      //remove_duplicates();
      //Remove a union N(a) union Y from Graph.

}
void clawfreeGraph::remove_duplicates()
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
      adj.clear();
      adj.resize(n+1);
      //adj_mat.clear();
      //set_vertices(n);
      for(auto edge: unique)
      {
            int x = edge.first;
            int y = edge.second;

            adj[x].push_back(y);
            adj[y].push_back(x);
            adj_mat[std::make_pair(x,y)] = 1;

            adj_mat[std::make_pair(y,x)] = 1;
      }
}




void clawfreeGraph::remove_vertex(int idx)
{
      std::cout<<idx<<" ";
      for(auto i : adj[idx])
      {
            int pos = std::lower_bound(adj[i].begin(),adj[i].end(),idx)-adj[i].begin();
            if(adj[i][pos]==idx)
            {
                  adj[i].erase(adj[i].begin()+pos);
                  adj_mat[std::make_pair(idx,i)] = 0;
                  adj_mat[std::make_pair(i,idx)] = 0;
            }
      }
      adj[idx].clear();
}


bool clawfreeGraph::SubtractioninducesCompleteGraph(int i,graph subgrph)
{
      for(int j:adj[i])
      {
            subgrph.remove_vertex(j);
      }
      for(int i = 0;i<=n;i++)
      {
            if(adj[i].size()>0)
            {
                  return false;
            }
      }
      return true;
}


std::unordered_set<int> clawfreeGraph::dist2points(int idx)
{
      std::unordered_set<int> d2points;
      for(int i:adj[idx])
      {
            for(int j:adj[i])
            {
                  d2points.insert(j);
            }
      }
      for(int i :adj[idx])
      {
            d2points.erase(i);
      }
      d2points.erase(idx);

      // std::vector<int> final;

      //for(int i:d2points)
      // {final.push_back(i);}

      return d2points;
}



bool clawfreeGraph::regularity_chk(int v,graph** complementSubgrph,std::vector<int> &left_clique,std::vector<int> &right_clique)
{
      (*complementSubgrph) = getComplementSubgraph(v);
      if((*complementSubgrph)->is_bipartite())
      {
            std::vector<int> color = (*complementSubgrph)->color;

            //left_clique->set_vertices(n);
            //right_clique->set_vertices(n);
            //std::vector<int> left,right;


            for(int i : neighbour)
            {
                  if(color[i]==0)
                  {
                        left_clique.push_back(i);
                        // marker_left[i] = 1;
                  }
                  else if(color[i]==1)
                  {
                        right_clique.push_back(i);
                        // marker_right[i] = 1;
                  }
            }
            left_clique.push_back(v);

            right_clique.push_back(v);

            return true;
      }
      else
      {
            //Not Regular.
            return false;
      }

}

graph* clawfreeGraph::getComplementSubgraph(int v)
{
      graph* subgrph = new(graph);
      subgrph->set_vertices(n);

      //std::vector<int> neighbour;
      neighbour.clear();

      for(int i :adj[v])
      {
            neighbour.push_back(i);
      }

      for(int i: neighbour)
      {
            for(int j:neighbour)
            {
                  if(i!=j&&adj_mat[std::make_pair(i,j)]==0)
                  {
                        subgrph->add_edge(i,j);
                  }
            }
      }
      subgrph->remove_duplicates();
      return subgrph;
}
