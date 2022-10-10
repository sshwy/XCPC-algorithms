#include <cstdio>
using namespace std;
const int N = 1e5 + 5, SZ = N;
int n;

struct Treap {
  int seed = 1, root, tot;
  int ch[SZ][2];
  int val[SZ], rnd[SZ], sz[SZ]; // sz:子树大小

  int rrand() { return seed = seed * 482711; }
  void pushup(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1; }
  void split(int u, int key, int &x, int &y) {
    if (!u) x = y = 0;
    else {
      if (val[u] <= key) x = u, split(ch[u][1], key, ch[u][1], y);
      else y = u, split(ch[u][0], key, x, ch[u][0]);
      pushup(u);
    }
  }
  int merge(int x, int y) { // x<y
    if (!x || !y) return x + y; //返回x，y或0
    if (rnd[x] < rnd[y]) return ch[x][1] = merge(ch[x][1], y), pushup(x), x;
    else return ch[y][0] = merge(x, ch[y][0]), pushup(y), y;
  }
  void insert(int v) { //插入v
    int x, y, u = ++tot;
    val[u] = v, sz[u] = 1, rnd[u] = rrand();
    split(root, v, x, y);
    root = merge(merge(x, u), y);
  }
  void del(int v) {
    int x, y, z;
    split(root, v - 1, x, y); //所有的v就被分在y中
    split(y, v, y, z); //所有的v仍被分在y中
    if (!y) return; //不存在v这个权值
    y = merge(ch[y][0], ch[y][1]); //根节点的不要了
    root = merge(x, merge(y, z));
  }
  int rank(int v) { //即相同的数中，第一个数的排名
    int x, y, res;
    split(root, v - 1, x, y);
    res = sz[x] + 1, root = merge(x, y);
    return res;
  }
  int kth(int k) { //查询排名为k的数
    int u = root;
    while (k != sz[ch[u][0]] + 1) {
      if (k <= sz[ch[u][0]]) u = ch[u][0];
      else k -= sz[ch[u][0]] + 1, u = ch[u][1];
    }
    return val[u];
  }
  int pre(int v) { return kth(rank(v) - 1); } //严格前驱
  int suc(int v) { return kth(rank(v + 1)); } //严格后继
} treap;
