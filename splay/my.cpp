/*
 * splay 模板 v1.0
 * 使用时记得在一头一尾加上虚点。
 */
#include <cstring>
#include <cstdio>
using namespace std;
namespace SPLAY{
	const int max_node = 200005;
	const int oo = 0x3f3f3f3f;
#define lson(x) son[(x)][0]
#define rson(x) son[(x)][1]
#define g(x) pre[pre[(x)]]
	struct Splay{
		int root,tot;
		int pre[max_node];
		int son[max_node][2];
		int size[max_node]; // the size of the subtree

		int new_node(){
			tot++;
			pre[tot] = 0;
			son[tot][0] = son[tot][1] = 0;
			return tot;
		}
		void init(){
			tot = -1;
			root = new_node();
		}
		void push_down(int x){
			if(x == 0) return;
			/*
			 *
			 */
		}
		void push_up(int x){
			if(x == 0) return;
			size[x] = size[lson(x)] + size[rson(x)] + 1;
			/*
			 *
			 */
		}
		void rotate(int x){ // 0 left, 1 right
			int y = pre[x], z = pre[y], kind = (x == lson(y));
			push_down(y), push_down(x); // push_down
			son[y][kind^1] = son[x][kind];
			son[x][kind] = pre[son[y][kind^1]] = y;
			pre[y] = x, pre[x] = z;
			if(z) son[z][y == rson(z)] = x;
			push_up(y); // push_up
		}
		void splay(int x,int at){
			push_down(x); // push_down
			while(pre[x] != at){
				if(g(x) == at) { rotate(x); break; }
				int y = pre[x], z = pre[y];
				if((y == lson(z))^(x == lson(y))) { rotate(x); rotate(x);}
				else { rotate(y); rotate(x); }
			}
			push_up(x); // push_up
			if(at == 0) root = x;
		}
		int access(int x, int cur){ 
			if(x == 0) return cur;
			while(1){
				push_down(cur); //
				if(size[lson(cur)] + 1 == x) return cur;
				else if(size[lson(cur)] >= x) cur = lson(cur);
				else { x -= size[lson(cur)] + 1; cur = rson(cur); }
			}
		}
		int get_min(int cur){
			while(lson(cur)) cur = lson(cur);
			return cur;
		}

		void INSERT(int x,int w){ // left subtree has x node; 用于插入节点
			x = access(x,root); splay(x,0);
			root = new_node(); val[root] = w;
			lson(root) = x; rson(root) = rson(x);
			pre[lson(root)] = pre[rson(root)] = root;
			rson(x) = 0; 
			push_up(lson(root)); push_up(rson(root));
			push_up(root);
		}
		void DELETE(int x){ //用于删除节点
			int l = access(x-1,root), r = access(x+1,root);
			splay(l,0), splay(r,l);
			lson(r) = 0;
			push_up(r), push_up(l);
		}
	};
#undef lson
#undef rson
#undef g
}
