/*
 *  Millar Rabin &  Pollard Rho 模板 v1.0
 */
#include <cstring>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
typedef long long LL;
LL GCD, LCM;
inline LL multiply_mod(LL a, LL b, LL mod){
	LL ans = 0;
	while(b){
		if(b & 1){
			ans += a; ans %= mod;
		}
		a += a; a %= mod; b >>= 1;
	}
	return ans;
}
inline LL pow_mod(LL x, LL n, LL mod){
	x %= mod;
	LL ans = 1;
	while(n){
		if(n & 1){
			ans = multiply_mod(ans, x, mod); ans %= mod;
		}
		x = multiply_mod(x, x, mod); x %= mod; n >>= 1;
	}
	return ans;
}
inline LL add_mod(LL a, LL b, LL mod){
	return (a + b) % mod;
}
LL gcd(LL a, LL b){
	if(b == 0) return a;
	return gcd(b, a%b);
}

int prime[10000005];
int not_prime[10000005];
int cnt_prime;
const int PRIME_LIM = 10000000;
inline void init_prime(){
	not_prime[1] = 1;
	for(int i = 2; i <= PRIME_LIM; i++){
		if(!not_prime[i]) prime[++cnt_prime] = i;
		for(int k = 1; k <= cnt_prime; k++){
			if(prime[k] * i > PRIME_LIM) break;
			not_prime[prime[k] * i] = 1;
			if(i % prime[k] == 0) break;
		}
	}
}
inline bool test(LL n, LL b){
	LL m = n - 1;
	LL counter = 0;
	while(~m & 1){
		m >>= 1;
		counter++;
	}
	LL ret = pow_mod(b, m, n);
	if(ret == 1 || ret == n - 1){
		return true;
	}
	counter --;
	while(counter >= 0){
		ret = multiply_mod(ret, ret, n);
		if(ret == n - 1){
			return true;
		}
		counter --;
	}
	return false;
}
const int BASE[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
inline bool is_prime(LL n){
	if(n < 2) return false;
	if(n < 4) return true;
	if((n & 1) == 0) return false;
	if(n == 3215031751LL){
		return false;
	}
	for(int i = 0; i < 14 && BASE[i] < n; ++i){
		if(!test(n, BASE[i])){
			return false;
		}
	}
	return true;
}
LL pollard_rho(LL n, LL seed){
	LL x, y, head = 1, tail = 2; 
	x = y = rand() % (n - 1) + 1;
	while(1){
		x = multiply_mod(x, x, n);
		x = add_mod(x, seed, n);
		if(x == y){
			return n;
		}
		LL d = gcd(abs(x - y), n);
		if(1 < d && d < n){
			return d;
		}
		head ++;
		if(head == tail){
			y = x;
			tail <<= 1;
		}
	}
}
LL divisors[1005], mul[1005];
int tot;
void factorize(LL n){
	if(n > 1){
		if(is_prime(n)){
			divisors[++tot] = n;
		} else {
			cerr << n << endl;
			LL d = n;
			while(d >= n){
				d = pollard_rho(n, rand() % (n - 1) + 1);
			}
			factorize(n / d);
			factorize(d);
		}
	}
}
void Factorize(LL n){
	tot = 0;
	for(int i = 1; i <= cnt_prime && prime[i] <= n; i++){
		while(n % prime[i] == 0){
			divisors[++tot] = prime[i];
			n /= prime[i];
		}
	}
	factorize(n);
}
 
//注意 以上 模板要使用小素数先判断之后才能继续使用。
