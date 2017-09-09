/*用法：设定s,t,调用price_flow()*/
/*费用流模板 v1.0*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n;
namespace PRICE_FLOW{
	const int oo = 0x3f3f3f3f;
	const int  max_node = 15005;
	struct Edge{
		int from,to,flow,cap,cost;
		Edge(int from,int to,int flow,int cap,int cost)
			:from(from),to(to),flow(flow),cap(cap),cost(cost){}
	};
	vector <Edge> edges;
	vector <int> graph[max_node];
	void insert(int from,int to,int cap,int cost){
		edges.push_back(Edge(from,to,0,cap,cost));
		edges.push_back(Edge(to,from,0,0,-cost));
		int m = edges.size();
		graph[from].push_back(m-2);
		graph[to].push_back(m-1);
	}
	int s,t;

	void init(int node_num){
		edges.clear();
		for(int i = 1; i <= node_num; i++) graph[i].clear();
	}

	int p[max_node];
	int a[max_node];
	int d[max_node];
	int inq[max_node];
	int bfs(int &flow,int &cost){
		memset(p,0,sizeof(p));
		memset(a,0x3f,sizeof(a));
		memset(d,0x3f,sizeof(d));
		memset(inq,0,sizeof(inq));
		queue <int> q;
		q.push(s);inq[s] = 1;d[s] = 0;
		while(!q.empty()){
			int tt = q.front(); q.pop(); inq[tt] = 0;
			int size = graph[tt].size();
			for(int i = 0; i < size; i++) {
				Edge &e = edges[graph[tt][i]];
				if(e.cap > e.flow && d[e.to] > d[tt] + e.cost){
					d[e.to] = d[tt] + e.cost;
					p[e.to] = graph[tt][i];
					a[e.to] = min(a[tt],e.cap - e.flow);
					if(!inq[e.to]) {q.push(e.to);inq[e.to] = 1;}
				}
			}
		}
		if(d[t] == INF) return 0;
		flow += a[t];
		cost += d[t] * a[t];
		int tmp = t;
		while(tmp != s){
			edges[p[tmp]].flow += a[t];
			edges[p[tmp]^1].flow -= a[t];
			tmp = edges[p[tmp]].from;
		}
		return 1;
	}
	int price_flow(){
		int flow = 0;
		int cost = 0;
		while(bfs(flow,cost)){}
		return cost;
	}
}
