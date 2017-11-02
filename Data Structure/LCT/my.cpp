#include <bits/stdc++.h>
using namespace std;
#define FILE "read"  
#define MAXN 30010  
#define INF 1000000000  
#define up(i,j,n) for(int i=j;i<=n;++i)  
#define dn(i,j,n) for(int i=j;i>=n;--i)  
namespace INIT{  
    char buf[1<<15],*fs,*ft;  
    inline char getc(){return (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<15,stdin),fs==ft))?0:*fs++;}  
    inline int read(){  
        int x=0,f=1;  char ch=getchar();  
        while(!isdigit(ch))  {if(ch=='-')  f=-1;  ch=getchar();}  
        while(isdigit(ch))  {x=x*10+ch-'0';  ch=getchar();}  
        return x*f;  
    }  
}using namespace INIT;  
int n,m,v[MAXN],X[MAXN],Y[MAXN];  
namespace Link_Cut_Tree{  
    int maxx[MAXN],sum[MAXN],f[MAXN],q[MAXN],vis[MAXN],son[MAXN][2];  
    bool get(int x){return son[f[x]][1]==x;}  
    bool isroot(int x){return (f[x]==0||(son[f[x]][0]!=x&&son[f[x]][1]!=x));}  
    void updata(int x){  
        maxx[x]=max(maxx[son[x][0]],max(maxx[son[x][1]],v[x]));  
        sum[x]=sum[son[x][0]]+sum[son[x][1]]+v[x];  
    }  
    void pushdown(int x){  
        if(vis[x]){  
            swap(son[x][0],son[x][1]);  
            vis[son[x][0]]^=1;  vis[son[x][1]]^=1;  
            vis[x]=0;  
        }  
    }  
    void rotate(int x){  
        int y=f[x],z=f[y],which=get(x);  
        if(!isroot(y))  son[z][son[z][1]==y]=x;  
        son[y][which]=son[x][which^1];  f[son[y][which]]=y;  
        son[x][which^1]=y;  f[y]=x;  f[x]=z;  
        updata(y);  updata(x);  
    }  
    void splay(int x){  
        int top(0);  q[++top]=x;  
        for(int i=x;!isroot(i);i=f[i])  q[++top]=f[i];  
        dn(i,top,1)  pushdown(q[i]);  
        for(int y=f[x];!isroot(x);rotate(x),y=f[x])  
            if(!isroot(y))  rotate(get(x)==get(y)?y:x);  
    }  
    void access(int x){for(int temp(0);x;temp=x,x=f[x])splay(x),son[x][1]=temp,updata(x);}  
    void reverse(int x){access(x);splay(x);vis[x]^=1;}  
    void linkk(int x,int y){reverse(x);f[x]=y;}  
    void split(int x,int y){reverse(x);access(y);splay(y);}  
    void makeroot(int x) {access(x);splay(x);vis[x] ^= 1;}
}  
int main(){  
    freopen(FILE".in","r",stdin);  
    freopen(FILE".out","w",stdout);  
    using namespace Link_Cut_Tree;  
    n=read();  maxx[0]=-INF;  
    up(i,1,n-1)  X[i]=read(),Y[i]=read();  
    up(i,1,n)  v[i]=read(),sum[i]=maxx[i]=v[i];  
    up(i,1,n-1)  linkk(X[i],Y[i]);  
    m=read();  
    up(i,1,m){  
        char ch[10];  scanf("%s",ch); int x=read(),y=read();  
        if(ch[1]=='H')  splay(x),v[x]=y,updata(x);  
        else if(ch[1]=='M')  split(x,y),printf("%d\n",maxx[y]);  
        else split(x,y),printf("%d\n",sum[y]);  
    }  
} 