#include"bipartite.h"

bipartite::bipartite(graph G)
{
	edges_list = G.edges_list;
	color = G.color;
	m = edges_list.size();
	s= 0;
	n = G.n;
	t = G.n+1;
	adj.resize(t+1);
	level.resize(t+1);
	start.resize(t+1);
	alternating.resize(t+1);
	matching.resize(t+1);
	cover.resize(t+1);
}
std::vector<int> bipartite::kernelization()
{
	Graph_Modify();
	int flow = solve_dinic();
	print_vertexcover();
	n = n/2;
	return cover;

}
void bipartite::add_edge(int v1,int v2)
{
      Edge a(v1,v2,1);
      edges_list.push_back(a);
      adj[v1].push_back(m++);

      Edge b(v2,v1,0);
      edges_list.push_back(b);
      adj[v2].push_back(m++);

}

void bipartite::Graph_Modify()
{

      /*edges_list will be directed from color(0) to color(1)*/
      for(int i = 0;i<edges_list.size();i++)
      {

		Edge e = edges_list[i];
		adj[e.v1].push_back(i);
            if(color[e.v1]==0&&color[e.v2]==1)
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
/*Finds if there is a path between s and t and also Generates levels to the nodes*/
bool bipartite::bfs()
{
	q.push(s);
	level[s] = 0;

	int cur;
	while(!q.empty())
	{
		cur = q.front();
		q.pop();


		for(int idx : adj[cur])
		{
			if(edges_list[idx].capacity != 1)
				continue;

			if(level[edges_list[idx].v2] != -1)
				continue;

			level[edges_list[idx].v2] = 1 + level[cur];
			q.push(edges_list[idx].v2);
		}
	}


	if(level[t]!=-1)
		return true;
	else
		return false;
}



/*Using dfs we check if we can send flow amount of water through the edges_list*/
/*start vector keep tracks of the adjacent neighbour checked till now.*/
int bipartite::dfs(int idx,int flow)
{
	if(flow ==0)
		return 0;

	if(idx==t)
		return flow;

	for(int& i = start[idx];i<adj[idx].size();i++)
	{
		Edge e = edges_list[adj[idx][i]];
		int v1 = e.v1;
		int v2 = e.v2;
		int cap = e.capacity;

		/*Neighbour is acceptable only if the following condition is true*/
		if(level[v1]+1 == level[v2]&&cap==1)
		{
			if(dfs(v2,1))
			{
				edges_list[adj[idx][i]].capacity--;

				edges_list[adj[idx][i] ^ 1].capacity++;

				return 1;
			}
		}
	}

	return 0;

}


/*This function uses the above bfs function to check if there is a path between s and t*/
/*If the path exists from s to t then we use dfs to calculate the amount of water which can be pumped in through the graph.*/
int bipartite::solve_dinic()
{
	total = 0;

	fill(level.begin(),level.end(),-1);
	while(bfs())
	{
		fill(start.begin(),start.end(),0);
		while(int flow = dfs(s,1))
		{
			total += flow;
		}

		fill(level.begin(),level.end(),-1);
	}
	// std::cout<<total<<"\n";
	return total;
}

void bipartite::travel_alternating(int i)
{

	q.push(i);

	int cur;
	while(!q.empty())
	{
		cur = q.front();
		q.pop();

		if(alternating[cur]==1)
		{
			continue;
		}
		alternating[cur] = 1;
		for(int idx : adj[cur])
		{
			if(edges_list[idx].v1==s||edges_list[idx].v1==t||edges_list[idx].v2==s||edges_list[idx].v2==t)
			{
				continue;
			}
			if(edges_list[idx].capacity != 1)
				continue;
			if(alternating[edges_list[idx].v2]==1)
				continue;


			q.push(edges_list[idx].v2);
		}
	}
}
void bipartite::print_vertexcover()
{


	for(int i = 0;i<edges_list.size();i++)
	{
		Edge e = edges_list[i];
		if(e.v1==s||e.v1==t||e.v2==s||e.v2==t)
		{
			continue;
		}
		if(color[e.v1]==0&&color[e.v2]==1&&e.capacity==0)
		{
			matching[e.v1] = 1;
			matching[e.v2] = 1;
		}
	}
	for(int i = 1;i<=n;i++)
	{
		if(matching[i]==0&&color[i]==0)
		{
			travel_alternating(i);
		}
	}
	int cnt=0;
	for(int i = 1;i<=n;i++)
	{
		if(color[i]==0&&alternating[i]!=1)
		{
			cnt++;
			cover[i] = 1;
			// std::cout<<i<<" ";
		}
		else if(color[i]==1&&alternating[i]==1)
		{
			cnt++;
			cover[i] = 1;
			// std::cout<<i<<" ";
		}


	}

	if(cnt!=total)
	{
		std::cout<<"Wrong\n\n\n";
	}

}

void bipartite::chk()
{
	for(int i = 0;i<edges_list.size();i++)
	{
		Edge e = edges_list[i];
		if(e.v1==s||e.v1==t||e.v2==s||e.v2==t)
		{
			continue;
		}
		else if(cover[e.v1]==1||cover[e.v2]==1)
		{
			continue;
		}
		else
		{
			std::cout<<"\n\n";
			std::cout<<e.v1<<" "<<e.v2<<"\n";
			std::cout<<"Wrong";
		}
	}
	std::cout<<"\n\n\nPerfect\n\n\n";
}