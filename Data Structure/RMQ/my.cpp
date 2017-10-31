/*
 * St RMQ 模板 v1.0 --不稳定版
 *
 */
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
namespace ST_TABLE{
	const int maxn = 100005; // 设置总长度
	const int max_ex = 25; // 设置指数的最大值
	struct ST{
		int l,r;
		int w[max_ex + 5][maxn];
		void build(int *num,int l_,int r_){
			memset(w[0],0x3f,sizeof(w[0]));
			l = l_; r = r_;
			for(int i = l; i <= r; i++){
				w[0][i] = num[i];
			}
			for(int i = 1; i <= max_ex; i++){
				for(int j = l; j <= r; j++){
					w[i][j] = min(w[i-1][j],w[i-1][min(max(l,r - (1<<(i-1)) + 1),j+(1<<(i-1)) )]);
				}
			}
		}
		int query(int l,int r){
			int del = r - l + 1;
			int now = 0;
			while((1 << (now+1)) <= del) now++;
			return min(w[now][l],w[now][max(l,r-(1<<now)+1)]);
		}
	};
}
/* 建议使用流程：
 * build()
 * query()
 */
