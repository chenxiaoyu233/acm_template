const int maxn = 20005;
const int maxm = 100005;
int n, m;
struct Data{
	int from, to, next;
}data[maxm * 2];
int head[maxn];
int tot;
void insert(int a, int b){
	tot++;
	data[tot].to = b;
	data[tot].from = a;
	data[tot].next = head[a];
	head[a] = tot;
}

int pre[maxn], lowpt[maxn], time_flag;
stack <int> st;
int ins[maxn];
void Ebcc(int v, int u){
	pre[v] = lowpt[v] = ++time_flag;
	st.push(v); ins[v] = 1;
	for(int k = head[v]; k; k = data[k].next){
		int w = data[k].to;
		if(!pre[w]){
			Ebcc(w, v);
			lowpt[v] = min(lowpt[v], lowpt[w]);
		} else if(pre[w] < pre[v] && ins[w] && w != u){
			lowpt[v] = min(lowpt[v], pre[w]);
		}
	}
	if(lowpt[v] == pre[v]){
		while(!st.empty() && st.top() != v){
			//do what you want to do here
			ins[st.top()] = 0;
			st.pop();
		}
		//do what you want to do here
		ins[st.top()] = 0;
		st.pop();
	}
}
