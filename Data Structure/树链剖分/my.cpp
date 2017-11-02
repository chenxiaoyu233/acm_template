// my QTREE

#include <cstdio>
#include <cstring>
#include <iostream>

#define lc (u << 1)
#define rc (u << 1 | 1)

using namespace std;

int read() {
	int sign = 1, n = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			sign = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		n = n * 10 + c - '0';
		c = getchar();
	}
	return sign * n;
}

const int Nmax = 10005;

int T, N;
int root, tot;
int dep[Nmax], size[Nmax], son[Nmax], fa[Nmax];
int top[Nmax], w[Nmax];

struct ed {
	int v, w, next;
} e[2 * Nmax];
int k = 1, head[Nmax];
int eed[Nmax][3];

inline void adde(int u, int v, int w) {
	e[k] = (ed){v, w, head[u]};
	head[u] = k++;
}

struct BIT {
	int mmax[Nmax * 3];

	inline void init() { memset(mmax, 0, sizeof(mmax)); }

	void update(int u, int l, int r, int pos, int w) {}

	int query(int u, int l, int r, int L, int R) {}
} t;

void dfs(int u) {
	size[u] = 1, son[u] = 0;
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].v;
		if (v == fa[u])
			continue;
		fa[v] = u;
		dep[v] = dep[u] + 1;
		dfs(v);
		size[u] += size[v];
		if (size[v] > size[son[u]])
			son[u] = v;
	}
}

void build_tree(int u, int tp) {
	w[u] = ++tot;
	top[u] = tp;
	if (son[u])
		build_tree(son[u], tp);
	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].v;
		if (v == son[u] || v == fa[u])
			continue;
		build_tree(v, v);
	}
}

int find(int l, int r) {
	int f1 = top[l], f2 = top[r], res = 0;
	while (f1 != f2) {
		if (dep[f1] > dep[f2]) {
			swap(f1, f2);
			swap(l, r);
		}
		res = max(res, t.query(1, 1, tot, w[f2], w[r]));
		r = fa[f2];
		f2 = top[r];
	}
	if (l == r)
		return res;
	if (dep[l] > dep[r])
		swap(l, r);
	return max(res, t.query(1, 1, tot, w[son[l]], w[r]));
}

int main() {
	for (T = read(); T--;) {
		N = read();
		root = (1 + N) >> 1;
		fa[root] = tot = dep[root] = 0;
		memset(head, 0, sizeof(head));
		k = 1;
		for (int i = 1; i < N; ++i) {
			eed[i][0] = read(), eed[i][1] = read(), eed[i][2] = read();
			adde(eed[i][0], eed[i][1], eed[i][2]);
			adde(eed[i][1], eed[i][0], eed[i][2]);
		}
		dfs(root);
		build_tree(root, root);

		t.init();
		for (int i = 1; i < N; ++i) {
			if (dep[eed[i][0]] > dep[eed[i][1]])
				swap(eed[i][0], eed[i][1]);
			t.update(1, 1, tot, w[eed[i][1]], eed[i][2]);
		}

		char c[10];
		int a, b;
		while (scanf("%s", c) && c[0] != 'D') {
			a = read();
			b = read();
			if (c[0] == 'Q')
				printf("%d\n", find(a, b));
			else
				t.update(1, 1, tot, w[eed[a][1]], b);
		}
	}
	return 0;
}