/* SCC模板 v1.0 */
/* maxn表示的是点的数量*/
#include <cstring>
#include <cstdio>
#include <cstdio>
#include <stack>
using namespace std;

int pre[maxn], lowpt[maxn], time_flag, cnt_scc;
stack <int> st;
bool in_stack[maxn];
void scc(int v){
	lowpt[v] = pre[v] = ++time_flag;
	st.push(v); in_stack[v] = 1;
	for(int k = head[v]; k; k = data[k].next){
		int w = data[k].tov;
		if(!pre[w]){
			scc(w);
			lowpt[v] = min(lowpt[w], lowpt[v]);
		}else if(pre[w] < pre[v]){
			if(in_stack[w]){
				lowpt[v] = min(lowpt[v], pre[w]);
			}
		}
	}
	if(lowpt[v] == pre[v]){
		cnt_scc++; 
		while(!st.empty() && pre[st.top()] >= pre[v]){
			//belong[st.top()] = cnt_scc;
			//num[cnt_scc]++;
			/* add what you what to do here . */
			in_stack[st.top()] = 0;
			st.pop();
		}
	}
}

