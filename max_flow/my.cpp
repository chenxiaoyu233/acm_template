/*
 * 最大流模板 v1.0
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
namespace flow{
	const int oo = 0x3f3f3f3f;
	const int max_node = 1005;
	struct Edge{
		int from,to,cap,flow;
		Edge(int from = 0, int to = 0, int cap = 0, int flow = 0)
			:from(from), to(to), cap(cap), flow(flow){}
	};
	struct Dinic{
		int s,t;
		vector <int> G[max_node];
		vector <Edge> edges;
		void init(int n){
			edges.clear();
			for(int i = 1; i <= n; i++) G[i].clear();
		}
		void insert(int from, int to, int cap){
			edges.push_back(Edge(from,to,cap,0));
			edges.push_back(Edge(to,from,0,0));
			int m = edges.size();
			G[from].push_back(m-2);
			G[to].push_back(m-1);
		}
		int dis[max_node];
		int bfs(){
			memset(dis,0x3f,sizeof(dis));
			queue <int> q; dis[s] = 0;
			q.push(s);
			while(!q.empty()){
				int tt = q.front(); q.pop();
				for(int i = 0; i < G[tt].size(); i++){
					Edge &e = edges[G[tt][i]];
					if(e.cap > e.flow){
						if(dis[e.to] > dis[tt] + 1){
							dis[e.to] = dis[tt] + 1;
							q.push(e.to);
						}
					}
				}
			}
			return dis[t] != oo;
		}
		int cur[max_node];
		int dfs(int x,int a){
			if(x == t || a == 0) return a;
			int flow = 0, f;
			for(int &i = cur[x]; i < G[x].size(); i++){
				Edge &e = edges[G[x][i]];
				if(dis[x] + 1 == dis[e.to] && (f = dfs(e.to,min(a,e.cap - e.flow))) >0 ){
					e.flow += f;
					a -= f;
					edges[G[x][i]^1].flow -= f;
					flow += f;
					if(a == 0) break;
				}
			}
			return flow;
		}
		int max_flow(int s,int t){
			this->s = s; this->t = t;
			int flow = 0;
			while(bfs()){
				memset(cur,0,sizeof(cur));
				flow += dfs(s,oo);
			}
			return flow;
		}
	}dinic;

}
