//用法：设置F(x)，调用asr(double a,double b,dobule eps)
/*
 * simpson自适应积分模板 v1.0
 */
#include <iostream>
#include <cstring>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
namespace SIMPSON{
	double F(double x){
		/*
		 *
		 */
	}
	double simpson(double a, double b){
		double c = a + (b-a)/2.0;
		return (F(a) +4*F(c) + F(b)) * (b-a) / 6.0;
	}
	double asr(double a, double b, double eps, double A){
		double c = a + (b-a) / 2.0;
		double L = simpson(a, c), R = simpson(c, b);
		if(fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15.0;
		return asr(a, c, eps/2.0, L) + asr(c, b, eps/2.0, R);
	}
	double asr(double a, double b, double eps){
		return asr(a, b, eps, simpson(a,b));
	}
}
