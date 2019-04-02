
int d = 3; // 最外侧维数
const int maxd = 4; // == d + 1
struct Point { int w[maxd], id; bool inS; }; 
// inS == True  表示该点是贡献答案的点
// inS == False 表示改点是收集答案的点 (即inQ)
// id 表示存放答案的位置
int cmp(const Point &a, const Point &b) { 
    if (a.w[d] == b.w[d]) return a.inS > b.inS;
    return a.w[d] < b.w[d]; 
}

Point P[maxd][maxn];
int PC[maxd][maxn];
void PCD(int l, int r, int &d, bool needSort = true) {
    if (l == r) return;
    if (needSort) sort (P[d]+l, P[d]+r+1, cmp);
    if (d == 1) {
        for (int i = l, cnt = 0; i <= r; i++) 
            if (P[d][i].inS) ++cnt;
            else PC[d][P[d][i].id] = cnt;
        return;
    }
    int mid = (l + r) >> 1;
    PCD(l, mid, d, false);
    for (int i = l; i <= r; i++) {
        P[d-1][i] = P[d][i];
        if (i >= mid+1) P[d-1][i].inS = false;
        PC[d-1][P[d][i].id] = 0;
    }
    --d; PCD(l, r, d); ++d;
    for (int i = mid+1; i <= r; i++) 
        if (!P[d][i].inS) PC[d][P[d][i].id] += PC[d-1][P[d][i].id];
    PCD(mid+1, r, d, false);
}

