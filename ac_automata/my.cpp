/*  AC自动机模板v2.0
 *  1. root的to函数比较特别，将原本为-1的转移全部变成了0的转移，减少了大量的特判.
 *  2. 直接将ac自动机建立成一个dfn，加速50%.
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <utility>
using namespace std;
namespace AC_AUTOMATA{
	const int max_letter_size = 2; //字符集大小的上界
	const int max_ac_auto_node = 125; //ac自动机内部结点个数的上界
	struct Node_AC{
		int to[max_letter_size];
		int fail;
		int flag; // set
	};
	struct AC_AUTO{
		int root;
		int tot;
		int letter_num;
		Node_AC node[max_ac_auto_node];
		int new_node(){
			tot++;
			for(int i = 0; i < letter_num; i++) node[tot].to[i] = -1;
			node[tot].fail = -1;
			node[tot].flag = 0;
			return tot;
		}
		void init(int letter_num_){
			letter_num = letter_num_;
			tot = -1;
			root = new_node(); // == 0
			node[root].fail = 0;
		}
		//#define trans(x) ((x) - '0') 宏加速
		inline int trans(char x){
			return x - '0';
		}
		void add_word(char *s,int x){
			int state = root;
			int len = strlen(s);
			for(int i = 0; i < len; i++){
				int at = trans(s[i]);
				if(node[state].to[at] == -1)
					node[state].to[at] = new_node();
				state = node[state].to[at];
			}
			//node[state].flag |= (1 << x); //状态保存的是集合中的元素
		}
		void build_fail(){
			for(int i = 0; i < letter_num; i++) if(node[root].to[i] == -1) 
				node[root].to[i] = 0;
			queue <int> q; q.push(root);
			while(!q.empty()){
				int tt = q.front(); q.pop();
				//node[tt].flag |= node[node[tt].fail].flag; // 合并答案
				for(int i = 0; i < letter_num; i++){
					int state = node[tt].fail;
					if(node[tt].to[i] > 0){
						int nex = node[tt].to[i];
						q.push(nex);
						if(tt == 0){node[nex].fail = 0; continue;}
						node[nex].fail = node[state].to[i];
					}else {
						if(tt == root) continue;
						node[tt].to[i] = node[state].to[i];
					}
				}
			}
		}
		//#define next(state,x) node[state].to[trans(x)] 宏加速
		inline int next(int state, char x){
			int at = trans(x);
			return node[state].to[at];
		}
		inline pair<int,int> query(char *s){
			int state = root;
			int ans = 0;
			for(int i = 0; s[i]; i++){
				state = next(state,s[i]);
				//ans |= node[state].flag;
			}
			return make_pair(state,ans);
		}
	};
	//建议调用顺序
	//ac.init(26);
	//ac.add_word(s);
	//ac.build_fail();
	//int ans = ac.query(s);
}
