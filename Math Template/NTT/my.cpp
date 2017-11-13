#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
namespace NTT{
	const LL P = 998244353;// == 2^23 * 7 * 17 + 1
	const LL G = 3; // G^Phi(P) == 1 (mod P)
	LL g = 3;

	inline LL pow_mod(LL x, LL n, LL mod){
		LL ans = 1;
		while(n){
			if(n & 1){ ans *= x; ans %= mod; }
			x *= x; x %= mod; n >>= 1;
		}
		return ans;
	}
	inline LL inv(LL x){
		return pow_mod(x, P-2, P);
	}
	inline LL omega(int n){ 
		LL u = (P-1) / n;
		return pow_mod(g, u, P);
	}
	inline void BitReverseCopy(LL A[], int n, int k){
		for(int i = 0; i < n; i++){
			int t = 0;
			for(int j = 0; j < k; j++) if(i & (1<<j)) // 二进制位[0,k)
				t |= 1 << (k - j - 1);
			if(t > i) swap(A[i],A[t]);
		}
	}
	inline void DFT(LL A[], int &n){
		int k = 0; while((1LL<<k) < n) k++;
		for(int i = n, ed = 1LL << k; i < ed; i++) A[i] = 0;
		n = 1LL << k;
		BitReverseCopy(A,n,k);
		LL wm,w,t,u;
		for(int s = 1; s <= k; s++){
			int m = 1 << s;
			wm = omega(m);
			for(int k = 0; k < n; k += m){
				w = 1;
				for(int j = 0, md = m/2; j < md; j++){
					t = w * A[k+j+md] % P, u = A[k+j];
					A[k+j] = u + t, A[k+j+md] = u - t + P;
					A[k+j] -= A[k+j] >= P ? P : 0;
					A[k+j+md] -= A[k+j+md] >= P ? P : 0;
					w = (w * wm) % P;
				}
			}
		}
	}
	inline void DFT_h(LL A[], int n){
		g = inv(G);
		DFT(A,n);
		g = G;
		LL invN = inv(n);
		for(int i = 0; i < n; i++) A[i] = A[i] * invN % P;
	}
}
// 使用DFT进行NT变换
// 使用DFT_h进行逆变换
// 因为模数的关系，n不能超过1e6
