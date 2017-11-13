#include <iostream>
#include <cstring>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
namespace  PrimitiveRoot{
	LL pow_mod(LL x, LL n, LL mod){
		LL ans = 1;
		while(n){
			if(n & 1){ ans *= x; ans %= mod; }
			x *= x; x %= mod; n >>= 1;
		}
		return ans;
	}
	LL Phi(LL n){ // 计算n的欧拉函数
		LL ans = n;
		for(int i = 2; i * i <= n; i++) if(n % i == 0) {
			ans = ans / i * (i-1);
			while(n % i == 0) n /= i;
		}
		if(n > 0) ans = ans / n * (n-1);
		return ans;
	}
	void exgcd(LL a, LL b, LL &x, LL &y){ // calc: ax + by == gcd(a, b)
		if(b == 0){ x = 1, y = 0; return; }
		exgcd(b, a % b, y, x); y -= a / b * x;
	}

	LL gcd(LL a, LL b){ // clac GCD( a, b )
		return b == 0 ? a : gcd(b, a % b);
	}
	bool mod_equation(LL a, LL &x, LL b, LL m) { // calc: ax == b ( mod m ) -> x % m
		b = ((b % m) + m) % m;
		LL g = gcd(a, m);
		if(b % g != 0) return false;
		LL y; exgcd(a, m, x, y);
		LL md = m/g;
		x = ((x % md) + md) % md;
		x %= m;
		x = x * (b/g % m) % m;
		return true;
	}
	bool mod_equation(LL a, vector <LL> &ans, LL b, LL m){ //计算模方程所有可能的解
		ans.clear(); LL x;
		b = ((b % m) + m) % m;
		LL g = gcd(a, m);
		if(b % g != 0) return false;
		LL y; exgcd(a, m, x, y);
		LL md = m/g;
		x = ((x % md) + md) % md;
		x %= m; x = x * (b/g % m) % m;
		for(int i = 0; i < g; i++){
			ans.push_back(x);
			x = (x + md) % m;
		}
		return true;
	}

	LL root, phi, P;

	LL inv(LL a){
		LL x; mod_equation(a, x, 1, P);
		return x;
	}
	void set_mod(LL P_) { // P = 2, 4, p^a, 2*p^a (其中p是奇素数)
		P = P_;
	}
	vector <LL> factor;
	LL get_primitive_root(){ //get x^{Phi(P)} == 1 (mod P) -> x是P的原根 O(玄)
		phi = Phi(P); // P = 2, 4, p^a, 2*p^a (其中p是奇素数)
		factor.clear(); int tmp = phi;
		for(int i = 2; i * i <= phi; i++) if(tmp % i == 0){
			factor.push_back(i);
			while(tmp % i == 0) tmp /= i;
		}
		if(tmp > 1) factor.push_back(tmp);
		for(int i = 1; i <= P; i++){
			bool flag = pow_mod(i, phi, P) == 1;
			if(!flag) continue;
			for(int j = 0; j < factor.size(); j++){
				if(pow_mod(i, phi/factor[j], P) == 1){
					flag = 0; break;
				}
			}
			if(flag) return root = i;
		}
		return -1;
	}
	unordered_map <LL, LL> mp;
	void D_log_prework(){ // 大步小步法的预处理
		mp.clear(); LL q = sqrt(phi) + 1;
		for(int i = 0; i * q <= phi - 1; i++) 
			mp[pow_mod(root, i * q, P)] = i * q;
	}
	LL D_log(LL x){ // 使用大步小步法计算x模P的离散对数
		x %= P;
		LL q = sqrt(phi) + 1;
		LL inv_root = inv(root);
		for(int i = 0; i < q; i++){
			LL right = pow_mod(inv_root, i, P) * x % P;
			if(mp.count(right)){
				return mp[right] + i;
			}
		}
		return -1;
	}
	bool n_times_remainder(vector <LL> x, LL K, LL A, LL P){ // clac: x^K == A (mod P) 的所有的x, 且按照升序
		x.clear();
		if(A == 0) { x.push_back(0); return true; } // log(0), 特判
		else if(P == 2) { x.push_back(A); return true; } // 底为1，特判
		else {
			set_mod(P);
			get_primitive_root();
			D_log_prework();
			LL b = D_log(A);
			if(b == -1){
				return false;
			}

			mod_equation(K, x, b, phi);
			for(int i = 0; i < x.size(); i++){
				x[i] = pow_mod(root, x[i], P);
			}
			sort(x.begin(), x.end());
			return true;
		}
	}
};

//useage:
//要使用n_times_remainder的话，直接调用即可。
//
//只需要求P的原根时
//set_mod(P); ans = get_primitive_root();
//
//只需要求A关于P的离散对数时
//set_mod(P); get_primitive_root();
//D_log_prework(); ans = D_log(A);
