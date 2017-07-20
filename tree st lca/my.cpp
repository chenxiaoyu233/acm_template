/*
 * 树上倍增模板，仅供参考（用于yy不出来的时候）
 */
void init_table(){
	for(int i = 1; i <= 30; i++)
		for(int j = 1; j <= pp; j++){
			f[j][i] = f[f[j][i-1]][i-1];
			minn[j][i] = min(minn[j][i-1],minn[f[j][i-1]][i-1]);
		}
}

int query(int u,int v){
	if(dep[u] < dep[v]) swap(u,v);
	int ans = 0x3f3f3f3f;
	for(int del = dep[u]-dep[v],i = 0; del > 0; del >>= 1,i++){
		if(del & 1){
			ans = min(ans,minn[u][i]);
			u = f[u][i];
		}
	}
	if(u == v) return ans;
	for(int i = 30; i >= 0; i--) {
		if(f[u][i] != f[v][i]){
			ans = min(ans,minn[u][i]);
			ans = min(ans,minn[v][i]);
			u = f[u][i];
			v = f[v][i];
		}
	}
	ans = min(ans,minn[u][0]);
	ans = min(ans,minn[v][0]);
	return ans;
}
