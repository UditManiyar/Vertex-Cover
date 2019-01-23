#include"graph.h"
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
      for(int i = 1;i<=n;i++)
      {
            degree[i] = adj[i].size();
            // std::cout<<degree[i]<<" ";
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
      //
      // std::cout<<"Edges in graph : "<<m<<"\n";
      //
      // std::cout<<"No of Edges Removed : "<<removed_edges<<"\n\n";
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
