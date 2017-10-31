/* Liner Base 模板v1.0 */

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;

namespace LINER_BASE{
	const int MAX_BASE = 63;
	struct LinerBase{
		LL b[70];
		inline void add(LL a){
			for(int i = MAX_BASE; i >= 0; i--) if((a >> i) & 1){
				if(b[i]) a ^= b[i];
				else {
					b[i] = a;
					for(int j = i-1; j >= 0; j--) if(b[j] && (b[i] >> j) & 1) b[i] ^= b[j];
					for(int j = i+1; j <= MAX_BASE; j++) if((b[j] >> i) & 1) b[j] ^= b[i];
					break;
				}
			}
		}
		void init(){
			memset(b, 0, sizeof(b));
		}
	};
};

/*Useage: 
  通过调用add(long long)函数来在线性基中增加数字。
*/
