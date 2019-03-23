#include"clawfreeGraph.h"
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
            graph *complementSubgrph,*left_clique,*right_clique;
            bool regular = regularity_chk(idx,complementSubgrph,left_clique,right_clique);

            //Vertex idx is irregular
            if(regular==false)
            {
                  //Reduce Irregular Point
                  reduce_irregular(idx,complementSubgrph);
            }
            //Vertex is regular
            else
            {
                  //Next...
                  if(reducible_clique(left_clique))
                  {
                        remove_clique(left_clique);
                  }

                  else if(reducible_clique(right_clique))
                  {
                        remove_clique(right_clique);
                  }
                  //Chk if left_clique or right_clique is reducible
                  //If one of them is reducible reduce else fasak..
            }

      }
      solve(idx+1);
}

void clawfreeGraph::remove_clique(graph* clique)
{
      std::vector<int> vertices;
      for(int i = 0;i<=n;i++)
      {
            if(clique->adj[i].size()>0)
            {
                  remove_vertex(i);
            }
      }
}


bool clawfreeGraph::reducible_clique(graph* clique)
{
      std::vector<int> vertices;
      for(int i = 0;i<=n;i++)
      {
            if(clique->adj[i].size()>0)
            {
                  vertices.push_back(i);
            }
      }

      graph grph;
      grph.set_vertices(n);
      std::unordered_set<int> neighbour;
      for(int i : vertices)
      {
            for(int j: adj[i])
            {
                  neighbour.insert(j);
            }
      }
      for(int i:vertices)
      {
            neighbour.erase(i);
      }

      bool flag = true;
      for(auto i : neighbour)
      {
            for(auto j:neighbour)
            {
                  if(adj_mat[std::make_pair(i,j)]==1)
                  {
                        for(int k:neighbour)
                        {
                              if(adj_mat[std::make_pair(i,k)]==0&&adj_mat[std::make_pair(j,k)]==0)
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
      std::vector<int> dist2pnts = dist2points(idx);
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
            remove_vertex(i);
      }

      for(int i:adj[idx])
      {
            remove_vertex(i);
      }

      remove_vertex(idx);

      //Remove a union N(a) union Y from Graph.

}

void clawfreeGraph::remove_vertex(int idx)
{
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


std::vector<int> clawfreeGraph::dist2points(int idx)
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

      std::vector<int> final;

      for(int i:d2points)
      final.push_back(i);

      return final;
}



bool clawfreeGraph::regularity_chk(int v,graph* complementSubgrph,graph* left_clique,graph* right_clique)
{
      complementSubgrph = getComplementSubgraph(v);
      if(complementSubgrph -> is_bipartite())
      {
            std::vector<int> color = complementSubgrph->color;

            *left_clique = *complementSubgrph;
            *right_clique = *complementSubgrph;

            for(int i = 0;i<=n;i++)
            {
                  if(color[i]==0)
                  {
                        right_clique->remove_vertex(i);
                  }
                  else if(color[i]==1)
                  {
                        left_clique->remove_vertex(i);
                  }
            }

            for(int i:adj[v])
            {
                  if(color[i]==0)
                  {
                        left_clique->add_edge(i,v);
                  }
                  else if(color[i]==1)
                  {
                        right_clique->add_edge(i,v);
                  }
            }
            left_clique->remove_duplicates();
            right_clique->remove_duplicates();

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

      std::vector<int> neighbour;
      std::unordered_map <int,int> map_neighbour;

      for(int i :adj[v])
      {
            neighbour.push_back(i);
            map_neighbour[i] = 1;
      }

      for(int i: neighbour)
      {
            for(int j = 0;j<=n;j++)
            {
                  if(adj_mat[std::make_pair(i,j)]==0&&map_neighbour[i] == 1)
                  {
                        subgrph->add_edge(i,j);
                  }
            }
      }
      subgrph->remove_duplicates();
      return subgrph;
}
