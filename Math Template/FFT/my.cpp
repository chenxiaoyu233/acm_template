/*
 * FFT 模板v1.0, 注意调用时，先需要保证 n = 2^k, 并且搞好初始值。
 * 调用DFT()进行FFT，调用DFT_h()进行逆运算（插值）。
 * A数组: [0,n)
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;
namespace FFT{
	const double pi = acos(-1);
	int inv_flag = 1;
	complex<double> omega(int n){ 
		double u = 2 * pi/ n * inv_flag;
		return complex<double>(cos(u),sin(u));
	}
	inline void BitReverseCopy(complex<double> A[], int n, int k){
		for(int i = 0; i < n; i++){
			int t = 0;
			for(int j = 0; j < k; j++) if(i & (1<<j)){ // 二进制位[0,k)
				t |= 1 << (k - j - 1);
			}
			if(t > i) swap(A[i],A[t]);
		}
	}
	inline void DFT(complex<double> A[], int n){ // 保证n = 2^k之后再调用。
		int k = 0; while((1<<k) < n) k++;
		BitReverseCopy(A,n,k);
		complex<double> wm,w,t,u;
		for(int s = 1; s <= k; s++){
			int m = 1 << s;
			wm = omega(m);
			for(int k = 0; k < n; k += m){
				w = 1;
				for(int j = 0, md = m/2; j < md; j++){
					t = w * A[k+j+md], u = A[k+j];
					A[k+j] = u + t, A[k+j+md] = u - t;
					w *= wm;
				}
			}
		}
	}
	inline void DFT_h(complex<double> A[], int n){
		inv_flag = -1;
		DFT(A,n);
		inv_flag = 1;
		for(int i = 0; i < n; i++) A[i] /= n;
	}
}
