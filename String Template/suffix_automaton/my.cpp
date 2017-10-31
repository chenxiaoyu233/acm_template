/*
 *  后缀自动机模板 v1.0
 *  INFO:
 *  1. root = 0;
 *  2. slink[root] = -1;
 *  3. L,R 表示当前状态中的串的长度区间
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;
namespace SUFFIX_AUTO{
	const int maxn = 200005;
	const int letter_num = 30;

	struct Suffix_Auto{
		int L[maxn * 2], R[maxn * 2];
		int slink[maxn * 2];
		int trans[maxn * 2][letter_num];

		int tot_sam;
		int last;
		int root;
		void init(){
			tot_sam = -1;
			root = last = new_node(0,0,NULL,-1);
		}
		int new_node(int l,int r,int *tran, int s){
			tot_sam++;
			L[tot_sam] = l; R[tot_sam] = r;
			slink[tot_sam] = s;
			if(tran == NULL) memset(trans[tot_sam],-1,sizeof(trans[tot_sam]));
			else memcpy(trans[tot_sam], tran, sizeof(trans[tot_sam]));

			return tot_sam;
		}

		inline void update(int x){
			L[x] = R[slink[x]] + 1;
		}

		void add(char s){
			int now = s - 'a';
			int y = new_node(-1,R[last] + 1, NULL, -1);
			int p = last; last = y;

			while(p != -1 && trans[p][now] == -1){
				trans[p][now] = y;
				p = slink[p];
			}

			if(p == -1){
				slink[y] = 0;
				update(y);
				return;
			}

			int q = trans[p][now];
			if(R[q] == R[p] + 1){
				slink[y] = q;
				update(y);
				return;
			}

			int nq = new_node(L[q],R[p]+1,trans[q],slink[q]);
			slink[q] = slink[y] = nq;
			update(q); update(y);
			while(p != - 1 && trans[p][now] == q){
				trans[p][now] = nq;
				p = slink[p];
			}
			return;
		}
		inline int next(int state, char ch){
			return trans[state][ch - 'a'];
		}
	};
}
//SUFFIX_AUTO::Suffix_Auto sa;

/* Useage
   1. sa.init();

   2. sa.add(char s);
   3. sa.next(stats, ch);
*/
