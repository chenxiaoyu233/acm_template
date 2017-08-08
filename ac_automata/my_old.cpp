/*  AC自动机模板v1.0
 *  describe: root的to函数比较特别，将原本为-1的转移全部变成了0的转移，减少了大量的特判
 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
namespace AC_AUTOMATA{
	const int max_letter_size = 30; //字符集大小的上界
	const int max_ac_auto_node = 500005; //ac自动机内部结点个数的上界
	struct Node_AC{
		int to[max_letter_size];
		int fail;
		int flag; // num
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
		int trans(char x){
			return x - 'a';
		}
		void add_word(char *s){
			int state = root;
			int len = strlen(s);
			for(int i = 0; i < len; i++){
				int at = trans(s[i]);
				if(node[state].to[at] == -1)
					node[state].to[at] = new_node();
				state = node[state].to[at];
			}
			node[state].flag++;
		}
		void build_fail(){
			for(int i = 0; i < letter_num; i++) if(node[root].to[i] == -1) 
				node[root].to[i] = 0;
			queue <int> q; q.push(root);
			while(!q.empty()){
				int tt = q.front(); q.pop();
				for(int i = 0; i < letter_num; i++)if(node[tt].to[i] > 0){
					int nex = node[tt].to[i]; q.push(nex);
					if(tt == 0){node[nex].fail = 0; continue;}
					int state = node[tt].fail;
					while(node[state].to[i] == -1) state = node[state].fail;
					node[nex].fail = node[state].to[i];
					//这里可以加入对答案的合并
				}
			}
		}
		int query(char *s){
			int ans = 0;
			int len = strlen(s);
			int state = root;
			for(int i = 0; i < len; i++){
				int at = trans(s[i]);
				while(node[state].to[at] == -1) state = node[state].fail;
				state = node[state].to[at];
				//这里可以加入对答案的计算，上述代码只是负责转移到此处。
			}
			return ans;
		}
	};
	//建议调用顺序
	//ac.init(26);
	//ac.add_word(s);
	//ac.build_fail();
	//int ans = ac.query(s);
}
