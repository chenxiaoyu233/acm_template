#include <bits/stdc++.h>
#pragma comment(linker,"/STACK:102400000,102400000")
using namespace std;
#define ll long long
#define REPP(I, A, B) for (int I = (A); I <= (B); I++)
#define REP(I, A) for (int I = 0; I < (A); I++)
const ll mod = 1000003;
const int N = 1e5 + 10;
ll n, k, fid[mod+10], a[N];
vector<int> G[N];
int ansA, ansB;
ll pow(ll x, ll n) {
	ll ans = 1;
	while (n) {
		if (n & 1) {
			ans *= x;
			ans %= mod;
		}
		x *= x;
		x %= mod;
		n >>= 1;
	}
	return ans;
}
ll inv(ll a) { return pow(a, mod - 2) % mod; }

int T, vis[N], sz[N], vis_num[mod+10], num[mod+10];

void add(ll mul, int x) {
	if(vis_num[mul] != T) {
		vis_num[mul] = T;
		num[mul] = n+1;
	}
	num[mul] = min(num[mul], x);
}

void check_ans(ll mul, int x) {
	ll rv = fid[mul] * k % mod;
	if(vis_num[rv] != T)
		return;
	int y = num[rv];
	if(x > y) swap(x, y);
	if(x < ansA || (x == ansA && y < ansB)) {
		ansA = x;
		ansB = y;
	}
}

void get_size(int x, int fa) {
	sz[x] = 1;
	for (auto v : G[x]) {
		if(vis[v] || v == fa) continue;
		get_size(v, x);
		sz[x] += sz[v];
	}
}

int BRS, BR;
void get_root(int x, int fa, int subnum) {
	int maxson_size = 0;
	sz[x] = 1;
	for (auto v : G[x]) {
		if (vis[v] || fa == v)
			continue;
		get_root(v, x, subnum);
		maxson_size = max(maxson_size, sz[v]);
		sz[x] += sz[v];
	}
	maxson_size = max(maxson_size, subnum - sz[x]);
	if (maxson_size < BRS) {
		BRS = maxson_size;
		BR = x;
	}
}

int find_root(int x, int val) {
	BRS = n+1;
	BR = x;
	get_root(x, x, val);
	return BR;
}

void dfs(int x, int fa, ll mul) {
	mul = mul * a[x] % mod;
	check_ans(mul, x);
	for (auto v : G[x]) {
		if(v == fa || vis[v])
			continue;
		dfs(v, x, mul);
	}
}

void redfs(int x, int fa, ll mul) {
	mul = mul * a[x] % mod;
	add(mul, x);
	for (auto v : G[x]) {
		if(v == fa || vis[v])
			continue;
		redfs(v, x, mul);
	}
}

void solve(int root) {
	T++;
	vis[root] = 1;
	get_size(root, root);
	int root_val = a[root];
	add(root_val, root);
	for (auto v : G[root]) {
		if(vis[v]) continue;
		dfs(v, root, 1);
		redfs(v, root, root_val);
	}
	for (auto v : G[root]) {
		if(vis[v]) continue;
		solve(find_root(v, sz[v]));
	}
}

int main() {
	REPP(i, 1, mod) fid[i] = inv(i);
	while(~scanf("%lld%lld", &n, &k)) {
		REPP(i, 1, n) scanf("%lld", &a[i]);
		REP(i, n+1) G[i].clear(), vis[i] = 0;
		int u, v;
		REP(i, n-1) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		ansA = n+1;
		solve(1);
		if(ansA == n+1) puts("No solution");
		else printf("%d %d\n", ansA, ansB);
	} 
	return 0;
}
