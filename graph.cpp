#include"graph.h"
void graph::set_vertices(int no_vertices)
{
      m =0;
      n = no_vertices;
      t = no_vertices+1;
      adj.resize(t+1);
      color.resize(t+1);
}
void graph::add_edge(int v1,int v2)
{
      Edge a(v1,v2,1);
      edges_list.push_back(a);
      adj[v1].push_back(m++);

      Edge b(v2,v1,0);
      edges_list.push_back(b);
      adj[v2].push_back(m++);

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
				set_vertices(n);
				continue;
			}
			else
			{
				int x,y;
				std::stringstream ss(line);
				ss>>x>>y;
                        add_edge(x,y);
			}

		}
		file.close();
	}

}


bool graph::bipartite_dfs(int idx,int par)
{
      for(auto i :adj[idx])
	{
		Edge e = edges_list[i];
		if(e.v2!=par)
		{
			if(color[idx]==color[e.v2])
			{
				return false;
			}
			else if(color[e.v2]!=-1)
			{
				continue;
			}
			else if(color[e.v2]==-1)
			{
				color[e.v2] = 1^color[idx];
			}

			if(!bipartite_dfs(e.v2,idx))
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
void graph::add_SourceSink()
{

      /*edges_list will be directed from color(0) to color(1)*/
      for(int i = 0;i<edges_list.size();i++)
      {
            if(color[edges_list[i].v1]==0&&color[edges_list[i].v2]==1)
            {
                  edges_list[i].capacity = 1;
            }
            else
            {
                  edges_list[i].capacity = 0;
            }

      }

      /*Connecting s to all vertices with color 0 and color 1 to t*/
      for(int i = 1;i<=n;i++)
      {
            if(color[i]==0)
                  add_edge(s,i);


            else if(color[i]==1)
                  add_edge(i,t);

      }
}
