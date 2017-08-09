/*
 * suffix_array 模板 v1.1
 */
//s : [0,length) 原串
//sa : 对原串后缀进行排序后的顺序
//rank : 原串的某个后缀在sa中的位置
//height : height[i] = sa[i]和sa[i-1]的lcp长度
//character : [0,range)
//height : [1,n)
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
namespace SUFFIX_ARRAY{
	const int maxn = 20005; // 用于设置字符串的长度
	struct SuffixArray{
		int n,range;
		int sa[maxn];
		int w[maxn];
		int tmp[maxn*2];
		int rank[maxn*2];
		int height[maxn];
		void init(){ //如果有多组数据，则一定记得调用
			n = range = 0;
			memset(sa,0,sizeof(sa));
			memset(w,0,sizeof(w));
			memset(tmp,-1,sizeof(tmp)); //设为-1简化比较
			memset(rank,-1,sizeof(rank)); //设为-1简化比较
			memset(height,0,sizeof(height));
		}
		int cmp(int i,int j, int *r, int step){ //内部函数,注意数组tmp和rank要开到2n，不然这里会越界访问
			return r[i] == r[j] && r[i+step] == r[j+step];
		}
		void build(int *s,int len_,int range_){ // s表示原串，len_表示原串长度，range_表示原串中字符的范围, 建议：range很大时，先离散化，模板不具备离散化的功能
			n = len_; range = max(n,range_);
			int i;
			for(i = 0; i < n; i++) w[rank[i] = s[i]]++;
			for(i = 1; i < range; i++) w[i] += w[i-1];
			for(i = n-1; i >= 0; i--) sa[--w[rank[i]]] = i;
			for(int step = 1; step < n; step <<= 1){
				int p = 0;
				for(i = n - step; i < n; i++) tmp[p++] = i;
				for(i = 0; i < n; i++) if(sa[i] >= step) tmp[p++] = sa[i] - step; 
				for(int i = 0; i < range; i++) w[i] = 0;
				for(i = 0; i < n; i++) w[rank[tmp[i]]]++;
				for(i = 1; i < range; i++) w[i] += w[i-1];
				for(i = n-1; i >= 0; i--) sa[--w[rank[tmp[i]]]] = tmp[i];
				for(swap(tmp,rank), p = 0, i = 0; i < n; i++)
					rank[sa[i]] = (i == 0 || cmp(sa[i-1],sa[i],tmp,step)) ? p : ++p;
			}
		}
		void get_real_rank(){
			for(int i = 0; i < n; i++) rank[sa[i]] = i;
		}
		void get_height(int *s){ //[1,n)
			s[n] = -1; // 不然循环可能不会终止
			for(int i = 0,h = 0; i < n; height[rank[i++]] = h){
				if(rank[i]-1 < 0) { h = 0; continue;}
				for(h?--h:0; s[sa[rank[i]-1]+h] == s[i+h]; h++);
			}
		}
	}suffix_array;
}

/*建议调用顺序
  suffix_array.init();
  suffix_array.build(...);
  suffix_array.get_real_rank();
  suffix_array.get_height(...);
 */
