namespace DLX{
	const int maxn = 1005;
	const int maxnode = 1000005;
	struct DL{
		int n,sz;
		int S[maxn];

		int row[maxnode], col[maxnode];
		int L[maxnode], R[maxnode], U[maxnode], D[maxnode];

		int ansd, ans[maxn];

		void init(int n){ // 这里的n表示的是列数
			this -> n = n;
			for(int i = 0; i <= n; i++){
				L[i] = i-1; R[i] = i+1;
				D[i] = i; U[i] = i;
			}
			L[0] = n; R[n] = 0;
			sz = n + 1;
			memset(S,0,sizeof(S));
		}

		void addRow(int r, vector<int> columns){ // 这里的r其实并没有什么卵用，因为这个函数只能在最后加一行
			int first = sz;
			for(int i = 0; i < columns.size(); i++){
				int c = columns[i];
				L[sz] = sz - 1; R[sz] = sz + 1; U[sz] = U[c]; D[sz] = c;
				D[U[c]] = sz; U[c] = sz;
				row[sz] = r; col[sz] = c;
				S[c]++; sz++;
			}
			L[first] = sz-1; R[sz-1] = first;
		}

#define FOR(i,A,s) for(int i = A[s]; i != s; i = A[i])
		void remove(int c){ // 移除一列
			L[R[c]] = L[c]; R[L[c]] = R[c];
			FOR(i,D,c) FOR(j,R,i){
				U[D[j]] = U[j]; D[U[j]] = D[j]; S[col[j]]--;
			}
		}

		void restore(int c){ // 恢复一列
			FOR(i,U,c) FOR(j,L,i){
				S[col[j]]++; D[U[j]] = j; U[D[j]] = j;
			}
			L[R[c]] = c; R[L[c]] = c;
		}
		bool dfs(int d){
			if(R[0] == 0){
				ansd = d;
				return true;
			}

			int c = R[0];
			FOR(i,R,0) if(S[i] < S[c]) c = i;

			remove(c);
			FOR(i,D,c){
				ans[d] = row[i];
				FOR(j,R,i) remove(col[j]);
				if(dfs(d+1)) return true;
				FOR(j,L,i) restore(col[j]);
			}
			restore(c);

			return false;
		}
#undef FOR
		bool solve(vector<int> &v){
			v.clear();
			if(!dfs(0)) return false;
			for(int i = 0; i < ansd; i++) v.push_back(ans[i]);
			return true;
		}
	}table;
}
