#include"graph.h"
#include <limits.h>
#include "adjlist.h"
void graph::set_vertices(int no_vertices,int edges)
{
      m =edges;
      n = no_vertices;
      //t = no_vertices+1;
      adj.setVertices(n+1);
      color.resize(t+1);
      degree.resize(t+1);
      cnt = 0;
}

void graph::take_input(char* file_name)
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
				line  = line.substr(5);
				std::stringstream ss(line);
				ss>>n>>m;
                        adj.setVertices(n+1);
				//set_vertices(n,m);
				continue;
			}
			else
			{
				int x,y;
				std::stringstream ss(line);
				ss>>x>>y;
                        adj.addEdge(x,y);
			}

		}
		file.close();
	}
      adj.removeDuplicates();
      adj.printlist();

}

// void graph::kernalization_network_flow()
// {
//       int sz = edges_list.size();
//       for(int i = 0;i<sz;i+=2)
//       {
//             Edge e(edges_list[i].v2,edges_list[i].v1+n,1);
//             edges_list.push_back(e);
//             Edge f(edges_list[i].v1+n,edges_list[i].v2,0);
//             edges_list.push_back(f);
//
//             edges_list[i].v2+=n;
//             edges_list[i+1].v1+=n;
//
//       }
//
//       //std::cout <<"\n\n\n";
//       //for(int i = 0;i<edges_list.size();i++)
//       //{
//       //      Edge e = edges_list[i];
//       //      std::cout<<e.v1<<" "<<e.v2<<" "<<e.capacity<<"\n";
//
//       //}
//       //std::cout <<"\n\n\n";
//       color.resize(2*n+2);
//       for(int i = 0;i<=n;i++)
//       {
//             color[i]=0;
//       }
//       for(int i = n+1;i<=2*n+1;i++)
//       {
//             color[i] = 1;
//       }
//       n = 2*n;
//
// }
// void graph::kernelized_output(std::vector<int> &cover)
// {
//       n = n/2;
//
//       for(int i = 1;i<=n;i++)
//       {
//       	if(cover[i]==1&&cover[n+i]==1)
//       	{
//                   v_cover.push_back(cover[i]);
//                   //std::cout<<i<<"a''";
//                   cover[i] = 1;
//                   cover[n+i] = 1;
//       	}
//       	else if(cover[i]^cover[n+i]==1)
//       	{
//                   cover[i] = 0;
//                   cover[n+i] = 1;
//       	}
//             else
//             {
//                   cover[i] = 1;
//             }
//       }
//
//       for(int i = 1;i<=n;i++)
//       {
//             if(cover[i]==1)
//             {
//                   remove_vertex(i);
//                   continue;
//             }
//             else
//             {
//                   continue;
//             }
//       }
//       color.resize(t+1);
//       reduction_edges();
//
// }

bool graph::bipartite_dfs(int idx,int par)
{
      //std::cout<<idx<<"a''\n";
      for(int u = 0;u<adj.adj[idx].size();u++)
      {
            int i = adj.adj[idx][u];
		if(i!=par)
		{
			if(color[idx]==color[i])
			{
                        cnt++;
                        remove_vertex(i);
                        u--;
                        continue;
				//return false;
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

bool graph::reduction_rule1()
{
      bool flag = false;

      while(!degree_one.empty())
      {
            flag = true;

            int current = degree_one.front();
            degree_one.pop();

            if(adj.adj[current].size()!=1)
            {
                  continue;
            }
            int neighbour = adj.adj[current][0];

            v_cover.push_back(neighbour);
            remove_vertex(neighbour);
            adj.adj[current].clear();
            degree[current] = adj.adj[current].size();
      }
      return flag;
}
bool graph::reduction_rule2()
{
      bool flag = false;
      while (!degree_two.empty())
      {
            flag = true;
            int current = degree_two.front();
            degree_two.pop();

            if(adj.adj[current].size()!=2)
            {
                  continue;
            }
            int neighbour1 = adj.adj[current][0];
            int neighbour2 = adj[current][1];

            int pos1 = std::lower_bound(adj.adj[neighbour1].begin(),adj.adj[neighbour1].end(),neighbour2)-adj.adj[neighbour1].begin();
            int pos2 = std::lower_bound(adj.adj[neighbour2].begin(),adj.adj[neighbour2].end(),neighbour1)-adj.adj[neighbour2].begin();

            if(adj.adj[neighbour1][pos1]==neighbour2&&adj.adj[neighbour2][pos2]==neighbour1)
            {
                  adjacent(current,neighbour1,neighbour2);

            }
            else
            {
                  non_adjacent(current,neighbour1,neighbour2);
            }
      }
      //
      // std::cout<<"Edges in graph : "<<m<<"\n";
      //
      // std::cout<<"No of Edges Removed : "<<removed_edges<<"\n\n";
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
      int prev = removed_edges;
      remove_vertex(current);

      n++;t++;
      adj.setVertices(t+1);
      //adj.resize(t+1);
      color.resize(t+1);
      degree.resize(t+1);


      int ptr1 = 0,ptr2 = 0;
      while(ptr1<adj.adj[neighbour1].size()&&ptr2<adj.adj[neighbour2].size())
      {
            if(adj.adj[neighbour1][ptr1]==adj.adj[neighbour2][ptr2])
            {
                  prev++;
                  adj.adj[n].push_back(adj.adj[neighbour1][ptr1]);
                  ptr1++;ptr2++;
            }
            else if(adj.adj[neighbour1][ptr1]<adj.adj[neighbour2][ptr2])
            {
                  adj.adj[n].push_back(adj.adj[neighbour1][ptr1]);
                  ptr1++;
            }
            else
            {
                  adj.adj[n].push_back(adj.adj[neighbour2][ptr2]);
                  ptr2++;
            }
      }
      while(ptr1<adj.adj[neighbour1].size())
      {
            adj.adj[n].push_back(adj.adj[neighbour1][ptr1]);
            ptr1++;

      }
      while(ptr2<adj.adj[neighbour2].size())
      {
            adj.adj[n].push_back(adj.adj[neighbour2][ptr2]);
            ptr2++;
      }
      for(auto i : adj.adj[neighbour1])
      {
            adj.adj[i].push_back(n);
      }
      for(auto i : adj.adj[neighbour2])
      {
            if (adj.adj[i].back()!=n)
            {
                  adj.adj[i].push_back(n);
            }

      }
      remove_vertex(neighbour1);
      remove_vertex(neighbour2);
      std::vector<int> v{n,current,neighbour1,neighbour2};
      rule.push_back(v);

      prev+=2;
      removed_edges = prev;
      degree[n] = adj.adj[n].size();
}


//
// bool graph::Claw_free()
// {
//       reduction_edges();
//       std::unordered_map<int, int> adj_mat[n+1];
//
//       for(int i = 0;i<edges_list.size();i++)
//       {
//             //std::cout<<edges_list[i].v1<<" "<<edges_list[i].v2<<"\n";
//             adj_mat[edges_list[i].v1][edges_list[i].v2] = 1;
//             adj_mat[edges_list[i].v2][edges_list[i].v1] = 1;
//
//       }
//
//       int number =0;
//
//       int flag = 0;
//
//       adj.calcDegree();
//
//       std::vector<std::pair<int,int>> greed_list;
//       for(int i = 1;i<=n;i++)
//       {
//             if(degree[i]>0)
//                   greed_list.push_back(std::make_pair(degree[i],i));
//       }
//
//       sort(greed_list.begin(),greed_list.end());
//       reverse(greed_list.begin(),greed_list.end());
//
//       for(auto vertx : greed_list)
//       {
//             int i = vertx.second;
//             flag = 0;
//             for(int j = 0;j<adj[i].size();j++)
//             {
//                   for(int k = j+1;k<adj[i].size();k++)
//                   {
//                         if(adj_mat[adj[i][j]][adj[i][k]]==1)
//                         {continue;}
//
//                         for(int l = k+1;l<adj[i].size();l++)
//                         {
//                               if(adj_mat[adj[i][j]][adj[i][l]]==1||adj_mat[adj[i][k]][adj[i][l]]==1)
//                               {
//                                     continue;
//                               }
//                               else
//                               {
//                                     number++;
//                                     flag = 1;
//                                     break;
//                               }
//                         }
//                         if(flag==1)
//                         {break;}
//                   }
//                   if(flag==1)
//                   {break;}
//             }
//             if(flag==1)
//             {
//                   for(auto idx : adj[i])
//                   {
//                         int pos = std::lower_bound(adj[idx].begin(),adj[idx].end(),i)-adj[idx].begin();
//                         if(adj[idx][pos]==i)
//                         {
//                               adj[idx].erase(adj[idx].begin()+pos);
//                               adj_mat[idx][i] = 0;
//                               adj_mat[i][idx] = 0;
//                         }
//                   }
//                   adj[i].clear();
//             }
//       }
//
//       std::cout<<number<<"\n";//<<" No Claw\n";
//       return true;
//
// }
