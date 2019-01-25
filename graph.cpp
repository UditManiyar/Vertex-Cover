#include"graph.h"
#include <limits.h>
void graph::set_vertices(int no_vertices,int edges)
{
      m =edges;
      n = no_vertices;
      t = no_vertices+1;
      adj.resize(t+1);
      color.resize(t+1);
      degree.resize(t+1);
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
				set_vertices(n,m);
				continue;
			}
			else
			{
				int x,y;
				std::stringstream ss(line);
				ss>>x>>y;

                        Edge a(x,y,1);
                        edges_list.push_back(a);
                        adj[x].push_back(y);

                        Edge b(y,x,0);
                        edges_list.push_back(b);
                        adj[y].push_back(x);

			}

		}
		file.close();
	}

}
void graph::reduction_edges()
{
      edges_list.clear();
      for(int i = 1;i<=n;i++)
      {
            for(auto j : adj[i])
            {
                  if(i>j)
                  {
                        continue;
                  }
                  else
                  {

                        Edge a(i,j,1);
                        edges_list.push_back(a);
                        Edge b(j,i,0);
                        edges_list.push_back(b);
                  }
            }
      }
      m = edges_list.size();
}
void graph::kernalization_network_flow()
{
      int sz = edges_list.size();
      for(int i = 0;i<sz;i+=2)
      {
            Edge e(edges_list[i].v2,edges_list[i].v1+n,1);
            edges_list.push_back(e);
            Edge f(edges_list[i].v1+n,edges_list[i].v2,0);
            edges_list.push_back(f);

            edges_list[i].v2+=n;
            edges_list[i+1].v1+=n;

      }

      std::cout <<"\n\n\n";
      for(int i = 0;i<edges_list.size();i++)
      {
            Edge e = edges_list[i];
            std::cout<<e.v1<<" "<<e.v2<<" "<<e.capacity<<"\n";

      }
      std::cout <<"\n\n\n";
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
                  std::cout<<i<<"a''";
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
      color.resize(t+1);
      reduction_edges();

}
bool graph::bipartite_dfs(int idx,int par)
{
      for(auto i :adj[idx])
	{
		// Edge e = edges_list[i];
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

void graph::calc_degree()
{
      fill(degree.begin(),degree.end(),0);
      int sum = 0;
      for(int i = 1;i<=n;i++)
      {
            degree[i] = adj[i].size();
            sum+=degree[i];
            if(degree[i]==1)
            {
                  degree_one.push(i);
            }
            else if(degree[i]==2)
            {
                  degree_two.push(i);
            }
      }

}

void graph::remove_vertex(int idx)
{
      for(auto i : adj[idx])
      {
            int pos = std::lower_bound(adj[i].begin(),adj[i].end(),idx)-adj[i].begin();
            if(adj[i][pos]==idx)
            {
                  removed_edges++;
                  adj[i].erase(adj[i].begin()+pos);
                  degree[i] = adj[i].size();
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
      degree[idx] = adj[idx].size();
}


bool graph::reduction_rule1()
{
      bool flag = false;

      while(!degree_one.empty())
      {
            flag = true;

            int current = degree_one.front();
            degree_one.pop();

            if(adj[current].size()!=1)
            {
                  continue;
            }
            int neighbour = adj[current][0];

            v_cover.push_back(neighbour);
            remove_vertex(neighbour);
            adj[current].clear();
            degree[current] = adj[current].size();
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

            if(adj[current].size()!=2)
            {
                  continue;
            }
            int neighbour1 = adj[current][0];
            int neighbour2 = adj[current][1];

            int pos1 = std::lower_bound(adj[neighbour1].begin(),adj[neighbour1].end(),neighbour2)-adj[neighbour1].begin();
            int pos2 = std::lower_bound(adj[neighbour2].begin(),adj[neighbour2].end(),neighbour1)-adj[neighbour2].begin();

            if(adj[neighbour1][pos1]==neighbour2&&adj[neighbour2][pos2]==neighbour1)
            {
                  remove_vertex(neighbour1);
                  remove_vertex(neighbour2);
                  remove_vertex(current);

                  v_cover.push_back(neighbour1);
                  v_cover.push_back(neighbour2);
            }
      }
      //
      // std::cout<<"Edges in graph : "<<m<<"\n";
      //
      // std::cout<<"No of Edges Removed : "<<removed_edges<<"\n\n";
      return flag;
}

void graph::degeneracy()
{
      calc_degree();
      int maxn = INT_MIN;
      int idx = 1;
      for(int j = 1;j<=n;j++)
      {
            int minx = INT_MAX;
            for(int i = 1;i<=n;i++)
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
      // std::cout<<"Degeneracy : "
      std::cout<<maxn<<"\n";
}
