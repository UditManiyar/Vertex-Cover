#include "graph.h"

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

                        adj[x].push_back(y);
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
