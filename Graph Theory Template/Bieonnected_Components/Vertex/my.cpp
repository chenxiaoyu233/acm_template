const int maxn = 20005;
const int maxm = 100005;
int n, m;
struct Data{
	int from, to, next, id;
}data[maxm * 2];
int head[maxn];
int tot;
void insert(int a, int b, int id){
	tot++;
	data[tot].to = b;
	data[tot].from = a;
	data[tot].next = head[a];
	data[tot].id = id;
	head[a] = tot;
}
int pre[maxn], lowpt[maxn], time_flag;
stack <int> st;
void Vbcc(int v, int u){
	pre[v] = lowpt[v] = ++ time_flag;
	for(int k = head[v]; k; k = data[k].next){
		int w = data[k].to;
		if(!pre[w]){
			st.push(k);
			Vbcc(w, v);
			lowpt[v] = min(lowpt[v], lowpt[w]);
			if(lowpt[w] >= pre[v]){
				while(!st.empty() && pre[data[st.top()].from] >= pre[w]){
					// do what you want to do here
					st.pop();
				}
				// do what you want to do here
				st.pop();
			}
		} else if(pre[w] < pre[v] && w != u){
			st.push(k);
			lowpt[v] = min(lowpt[v], pre[w]);
		}
	}
}
