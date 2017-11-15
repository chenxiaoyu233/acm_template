/*
 * 圆的面积并模板  v1.0
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

const double pi = acos(-1);

const double eps = 1e-8;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}

struct Point {
	double x, y;
	Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
bool operator == (const Point& a, const Point &b) { return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0; }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double angle(Vector v) { return atan2(v.y, v.x); }

struct Circle {
	Point c;
	double r;
	Circle(Point c = Point(), double r = 0):c(c),r(r) {}
	Point point(double a) {
		return Point(c.x + cos(a)*r, c.y + sin(a)*r);
	}
};
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
	double d = Length(C1.c - C2.c);
	if(dcmp(d) == 0) {
		if(dcmp(C1.r - C2.r) == 0) return -1; // 重合，无穷多交点
		return 0;
	}
	if(dcmp(C1.r + C2.r - d) < 0) return 0;
	if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;

	double a = angle(C2.c - C1.c);
	double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
	Point p1 = C1.point(a-da), p2 = C1.point(a+da);

	sol.push_back(p1);
	if(p1 == p2) return 1;
	sol.push_back(p2);
	return 2;
}

namespace Circle_Union{
	const int maxn = 1005;

	int n;
	Circle c[maxn];
	int vis[maxn];
	double ans[maxn];
	struct Node{
		double ang;
		int kind;
		Node(double ang = 0, int kind = 0):ang(ang), kind(kind){}
		friend bool operator < (const Node &a, const Node &b){
			if(a.ang == b.ang) return a.kind > b.kind;
			return a.ang < b.ang;
		}
	};
	void work(int x){
		for(int i = 1; i <= n; i++) if( i != x ){
			if(Length(c[i].c - c[x].c) + c[x].r <= c[i].r) {
				vis[x]++;
			}
		}
		vector <Node> vec; vec.clear();
		vector <Point> sol;
		for(int i = 1; i <= n; i++) if( i != x ){
			sol.clear();
			getCircleCircleIntersection(c[x], c[i], sol);
			if(sol.size() < 2) continue;
			if(angle(sol[1] - c[x].c) < angle(sol[0] - c[x].c)){
				vec.push_back(Node(pi, -1));
				vec.push_back(Node(-pi, 1));
			}
			vec.push_back(Node(angle(sol[0] - c[x].c), 1));
			vec.push_back(Node(angle(sol[1] - c[x].c), -1));
		}
		vec.push_back(Node(-pi, 1));
		vec.push_back(Node(pi, -1));
		sort(vec.begin(), vec.end());
		Node last = vec[0]; int cnt = 0;
		for(int i = 0; i < vec.size(); i++){
			ans[cnt + vis[x]] += 0.5 * Cross(c[x].point(last.ang) - Point(0,0), c[x].point(vec[i].ang) - Point(0,0));
			double del = vec[i].ang - last.ang;
			ans[cnt + vis[x]] += 0.5 * c[x].r * c[x].r * (del - sin(del));
			last = vec[i];
			cnt += vec[i].kind;
		}
	}
	void init(){
		memset(vis, 0, sizeof(vis));
		memset(ans, 0, sizeof(ans));
	}
	void WORK(){ for(int i = 1; i <= n; i++) work(i); }
};

//useage
//调用init()
//输入n个圆c[1...n]
//调用WORK()
//ans[i] 表示被覆盖i次及以上的面积。
