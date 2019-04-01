#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <stack>
#include <set>
#include <map>
using namespace std;

template <class KeyType, class ValType>
struct SkipListNode {
    KeyType key; ValType val;
    SkipListNode<KeyType, ValType> *up, *down, *left, *right;
    SkipListNode<KeyType, ValType>(KeyType key, ValType val): key(key), val(val) {
        up = down = left = right = NULL;
    }
};

template <class KeyType, class ValType>
class SkipList {
    typedef SkipListNode<KeyType, ValType> Node;
private:
    KeyType lb, ub;
    //Node *head, *tail; // point to the entry of the link list
    stack<Node*> head, tail;
    Node *buttom;
    inline Node* Head() { return head.top(); }
    inline Node* Tail() { return tail.top(); }
    inline bool isLB(Node *node) { return node -> left == NULL; }
    inline bool isUB(Node *node) { return node -> right == NULL; }
    inline void forwarding(Node* &cur, KeyType key) {
        if (cur == NULL) cur = Head();
        while (!isUB(cur) && cur -> right -> key <= key) cur = cur -> right;
    }
    inline void backwarding(Node* &cur) {
        while (!isLB(cur) && cur -> up == buttom) cur = cur -> left;
    }
    inline bool filpACoin() { return rand() & 1; }
    inline void insertNode(Node *l, Node *m, Node *r, Node *d) {
        l -> right = m; m -> left = l;
        r -> left = m; m -> right = r;
        d -> up = m; m -> down = d;
        m -> up = buttom;
    }
    inline Node* deleteNode(Node *m) {
        Node *l = m -> left, *r = m -> right, *u = m -> up;
        l -> right = r; r -> left = l;
        delete m;
        return u;
    }
    inline bool isOneLevel() { return head.size() == 1; }
    inline void pushLevel(Node *ohead, Node *otail) {
        head.push(new Node(lb, ValType()));
        tail.push(new Node(ub, ValType()));
        Head() -> right = Tail(); Head() -> down = ohead;
        Tail() -> left = Head(); Tail() -> down = otail;
        Head() -> up = buttom; Tail() -> up = buttom;
        ohead -> up = Head(); otail -> up = Tail();
    }
    inline void popLevel() {
        delete Head(); delete Tail();
        head.pop(); tail.pop();
        Head() -> up = buttom; Tail() -> up = buttom;
    }

public:
    SkipList<KeyType, ValType>(KeyType lb, KeyType ub): lb(lb), ub(ub) {
        buttom = new Node(KeyType(), ValType());
        pushLevel(buttom, buttom);
    }

    ~SkipList<KeyType, ValType>() {
        while (!head.empty()) {
            for (Node *pt = Head(), *nxt = NULL; pt != NULL; pt = nxt) {
                nxt = pt -> right;
                delete pt;
            }
            head.pop();
        }
        delete buttom;
    }

    Node* QueryLB(KeyType key, Node *cur = NULL) {
        forwarding(cur, key);
        return cur -> down == buttom ? cur : QueryLB(key, cur -> down);
    }

    // if key is exists, then the result is unpredictable
    void Insert(KeyType key, ValType val, Node *cur = NULL) {
        Node *left = cur == NULL ? QueryLB(key) : cur;
        if (left -> key == key) return;
        bool promotion = true;
        for (Node *node = NULL, *down = buttom; promotion; down = node) {
            node = new Node(key, val);
            insertNode(left, node, left -> right, down);
            if ((promotion = filpACoin())) {
                backwarding(left);
                if (left -> up == buttom) pushLevel(Head(), Tail());
                left = left -> up;
            }
        }
    }

    void Delete(KeyType key, Node *cur = NULL) {
        cur = cur == NULL ? QueryLB(key) : cur;
        if (cur -> key != key) return;
        for (; cur != buttom; cur = deleteNode(cur)) {}
        while (Head() -> right == Tail() && !isOneLevel()) popLevel();
    }
};

void test() {
    int oo = 0x3f3f3f3f;
    map<int, int> mp;
    int n; scanf(" %d", &n);
    SkipList<int, int> skl(-oo, oo);
    for (int i = 1; i <= n; i++) {
        //int op = rand() % 3, a = rand() % 10, b = rand() % 10;
        //cerr << i << endl;
        int op, a, b; scanf(" %d%d%d", &op, &a, &b);
        if (op == 0) { 
            if (skl.QueryLB(a) -> key == a) continue;
            mp[a] = b; skl.Insert(a, b); 
        }
        else if (op == 1) {
            if (mp.count(a)) mp.erase(a);
            if (skl.QueryLB(a) -> key == a) skl.Delete(a);
        } else if (op == 2) {
            bool fa = mp.count(a) != 0;
            bool fb = (skl.QueryLB(a) -> key == a);
            if (fa && fb) {
                if (mp[a] != skl.QueryLB(a) -> val) {
                    cerr << "Wrong" << endl;
                    exit(233);
                } 
            } else if(fa != fb) {
                cerr << "Wrong" << endl;
                exit(233);
            }
        }
    }
}

int main() {
    freopen("main.in", "r", stdin);
    test();
    cerr << "accept" << endl;
    return 0;
}
