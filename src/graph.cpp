#include "graph.h"
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <set>
#include<iostream>
#include <unordered_map>
#include<algorithm>

void graph::set_vertices(int no_vertices)
{
      n = no_vertices;
      adj.resize(n+1);
      color.resize(n+1);
}
void graph::get_input(char* file_name)
{
      /*Taking input from file*/
      std::ifstream file(file_name);
      std::string line;
      if(file.is_open())
      {
            while(getline(file,line))
            {
                  if(line.empty()||line[0]=='c'||line[0]==' ')
                  {
                        continue;
                  }
                  if(line.size()>5&&line.substr(0,5)=="p td ")
                  {
                        line = line.substr(5);
                        std::stringstream ss(line);
                        ss>>n>>m;
                        set_vertices(n);
                        continue;
                  }
                  else
                  {
                        int x,y;
                        std::stringstream ss(line);
                        ss>>x>>y;
                        adj[x].push_back(y);
                        adj[y].push_back(x);
                  }
            }
            file.close();
      }
      remove_duplicates();
}
void graph::add_edge(int x,int y)
{
      adj[x].push_back(y);
      adj[y].push_back(x);
}
void graph::remove_duplicates()
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
      set_vertices(n);
      for(auto edge: unique)
      {
            int x = edge.first;
            int y = edge.second;

            adj[x].push_back(y);
            adj[y].push_back(x);
      }
}


bool graph::bipartite_dfs(int idx,int par)
{
      for(auto i :adj[idx])
	{
		if(i!=par)
		{
			if(color[idx]==color[i])
			{
				return false;
			}
			else if(color[i]!=-1)
			{
				continue;
			}
			else if(color[i]==-1)
			{
				color[i] = 1^color[idx];
			}
			if(!bipartite_dfs(i,idx))
				return false;
		}
	}
	return true;
}
bool graph::is_bipartite()
{
      fill(color.begin(),color.end(),-1);

      for(int i = 1;i<=n;i++)
      {
            if(adj[i].size()<=0)
            {
                  continue;
            }
            
            if(color[i]!=-1)
            {
                  continue;
            }
            color[i] = 0;
            if(!bipartite_dfs(i,-1))
            {
                  return false;
            }
      }
      return true;
}

void graph::Bipartite_matching_to_vcover(std::vector<std::pair<int,int>> matching)
{
      //Read Later
}
void graph::remove_vertex(int idx)
{
      for(auto i : adj[idx])
      {
            int pos = std::lower_bound(adj[i].begin(),adj[i].end(),idx)-adj[i].begin();
            if(adj[i][pos]==idx)
            {
                  adj[i].erase(adj[i].begin()+pos);
            }
            if(adj[i].size()==1)
            {
                  degree_one.push(i);
            }
            else if(adj[i].size()==2)
            {
                  degree_two.push(i);
            }
      }
      adj[idx].clear();
}
bool graph::reduction_rule1()
{
      bool flag = false;

      while(!degree_one.empty())
      {

            int current = degree_one.front();
            degree_one.pop();

            if(adj[current].size()!=1)
            {
                  continue;
            }
            flag = true;

            int neighbour = adj[current][0];
            v_cover.push_back(neighbour);
            remove_vertex(neighbour);
            adj[current].clear();
      }
      return flag;
}

bool graph::reduction_rule2()
{
      bool flag = false;
      while (!degree_two.empty())
      {
            int current = degree_two.front();
            degree_two.pop();

            if(adj[current].size()!=2)
            {
                  continue;
            }
            flag = true;

            int neighbour1 = adj[current][0];
            int neighbour2 = adj[current][1];

            int pos1 = std::lower_bound(adj[neighbour1].begin(),adj[neighbour1].end(),neighbour2)-adj[neighbour1].begin();
            int pos2 = std::lower_bound(adj[neighbour2].begin(),adj[neighbour2].end(),neighbour1)-adj[neighbour2].begin();

            if(adj[neighbour1][pos1]==neighbour2&&adj[neighbour2][pos2]==neighbour1)
            {
                  adjacent(current,neighbour1,neighbour2);
            }
            else
            {
                  non_adjacent(current,neighbour1,neighbour2);
            }
      }
      return flag;
}
void graph::adjacent(int current, int neighbour1,int neighbour2)
{
      remove_vertex(neighbour1);
      remove_vertex(neighbour2);
      remove_vertex(current);

      v_cover.push_back(neighbour1);
      v_cover.push_back(neighbour2);
}
void graph::non_adjacent(int current, int neighbour1,int neighbour2)
{
      remove_vertex(current);

      set_vertices(n+1);

      int ptr1 = 0,ptr2 = 0;
      while(ptr1<adj[neighbour1].size()&&ptr2<adj[neighbour2].size())
      {
            if(adj[neighbour1][ptr1]==adj[neighbour2][ptr2])
            {
                  adj[n].push_back(adj[neighbour1][ptr1]);
                  ptr1++;ptr2++;
            }
            else if(adj[neighbour1][ptr1]<adj[neighbour2][ptr2])
            {
                  adj[n].push_back(adj[neighbour1][ptr1]);
                  ptr1++;
            }
            else
            {
                  adj[n].push_back(adj[neighbour2][ptr2]);
                  ptr2++;
            }
      }
      while(ptr1<adj[neighbour1].size())
      {
            adj[n].push_back(adj[neighbour1][ptr1]);
            ptr1++;

      }
      while(ptr2<adj[neighbour2].size())
      {
            adj[n].push_back(adj[neighbour2][ptr2]);
            ptr2++;
      }
      for(auto i : adj[neighbour1])
      {
            adj[i].push_back(n);
      }
      for(auto i : adj[neighbour2])
      {
            if (adj[i].back()!=n)
            {
                  adj[i].push_back(n);
            }

      }
      remove_vertex(neighbour1);
      remove_vertex(neighbour2);

      if(adj[n].size()==1)
      {
            degree_one.push(n);
      }
      else if(adj[n].size()==2)
      {
            degree_two.push(n);
      }


      std::vector<int> v{n,current,neighbour1,neighbour2};
      rule.push_back(v);
}


int graph::remaining_vertices()
{
      int vertices_remaining = 0;
      for(int i = 0;i<adj.size();i++)
      {
            if(adj[i].size()>0)
            {
                  vertices_remaining++;
            }
            if(adj[i].size()==1)
            {
                  degree_one.push(i);
            }
            else if(adj[i].size()==2)
            {
                  degree_two.push(i);
            }
      }
      return vertices_remaining;
}



//Need to study this again and implement this....
void graph::kernalization_network_flow()
{
      set_vertices(2*n);

      for(int i = 0;i<=n/2;i++)
      {
            for(auto j:adj[i])
            {
                  //Edge e(edges_list[i].v2,edges_list[i].v1+n,1);
                  adj[adj[i][j]].push_back(i+n);
                  //edges_list.push_back(e);
                  //Edge f(edges_list[i].v1+n,edges_list[i].v2,0);
                  //edges_list.push_back(f);
                  adj[i+n].push_back(adj[i][j]);
                  //adj[i]+=n;

                  //edges_list[i].v2+=n;
                  //edges_list[i+1].v1+=n;
            }
      }

      color.resize(2*n+2);
      for(int i = 0;i<=n;i++)
      {
            color[i]=0;
      }
      for(int i = n+1;i<=2*n+1;i++)
      {
            color[i] = 1;
      }
      n = 2*n;

}
void graph::kernelized_output(std::vector<int> &cover)
{
      n = n/2;

      for(int i = 1;i<=n;i++)
      {
      	if(cover[i]==1&&cover[n+i]==1)
      	{
                  v_cover.push_back(cover[i]);
                  //std::cout<<i<<"a''";
                  cover[i] = 1;
                  cover[n+i] = 1;
      	}
      	else if(cover[i]^cover[n+i]==1)
      	{
                  cover[i] = 0;
                  cover[n+i] = 1;
      	}
            else
            {
                  cover[i] = 1;
            }
      }

      for(int i = 1;i<=n;i++)
      {
            if(cover[i]==1)
            {
                  remove_vertex(i);
                  continue;
            }
            else
            {
                  continue;
            }
      }
      color.resize(n+1);
}
bool graph::clawfree_chk()
{
      std::vector<std::vector<int> > adj_copy;
      adj_copy = adj;
      std::vector<int> removed_vertices;


      std::unordered_map<int, int> adj_mat[n+1];
      for(int i = 0;i<=n;i++)
      {
            for(int j:adj_copy[i])
            {
                  adj_mat[i][j] = 1;
            }
      }

      int number =0;

      int flag = 0;

      std::vector<std::pair<int,int>> greed_list;
      for(int i = 1;i<=n;i++)
      {
            if(adj_copy[i].size()>0)
                  greed_list.push_back(std::make_pair(adj_copy[i].size(),i));
      }

      sort(greed_list.begin(),greed_list.end());
      reverse(greed_list.begin(),greed_list.end());

      for(auto vertx : greed_list)
      {
            int i = vertx.second;
            flag = 0;
            for(int j = 0;j<adj_copy[i].size();j++)
            {
                  for(int k = j+1;k<adj_copy[i].size();k++)
                  {
                        if(adj_mat[adj_copy[i][j]][adj_copy[i][k]]==1)
                        {continue;}

                        for(int l = k+1;l<adj_copy[i].size();l++)
                        {
                              if(adj_mat[adj_copy[i][j]][adj_copy[i][l]]==1||adj_mat[adj_copy[i][k]][adj_copy[i][l]]==1)
                              {
                                    continue;
                              }
                              else
                              {
                                    number++;
                                    flag = 1;
                                    break;
                              }
                        }
                        if(flag==1)
                        {break;}
                  }
                  if(flag==1)
                  {break;}
            }
            if(flag==1)
            {
                  for(auto idx : adj_copy[i])
                  {
                        int pos = std::lower_bound(adj_copy[idx].begin(),adj_copy[idx].end(),i)-adj_copy[idx].begin();
                        if(adj_copy[idx][pos]==i)
                        {
                              adj_copy[idx].erase(adj_copy[idx].begin()+pos);
                              adj_mat[idx][i] = 0;
                              adj_mat[i][idx] = 0;
                        }
                  }
                  adj_copy[i].clear();
                  removed_vertices.push_back(i);
            }
      }

      std::cout<<number<<"\n";//<<" No Claw\n";
      return true;
}
