#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;
typedef long long LL;
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
// return the minmum non-negetive x


/*
   	clac:
   	/ x == b1 (mod m1)
	| x == b2 (mod m2)
	|  ...
	\ x == bn (mod mn)
	return the minmum non-negetive x
*/

struct Equation{
	LL b, m;
	Equation(LL b = 0, LL m = 0):b(b), m(m){}
};
stack <Equation> st;
void mod_equation_vector(){
	while(st.size() >= 2){
		Equation e1 = st.top(); st.pop();
		Equation e2 = st.top(); st.pop();
		LL g = gcd(e1.m, e2.m);
		LL k1;
	        if((e2.b - e1.b) % g == 0 && mod_equation(e1.m/g, k1, (e2.b - e1.b)/g, e2.m/g)){
			LL m = e1.m / g * e2.m;
			k1 = ((k1 % m) + m)%m;
			LL b = (k1 * e1.m) % m + e1.b;
			b = ((b % m) + m) % m;
			st.push(Equation(b, m));
		} else {
			cout << "-1" << endl;
			return;
		}
	}
	LL x; Equation e = st.top();
	mod_equation(1, x, e.b, e.m);
	cout << x << endl;
}
