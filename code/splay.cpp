const int SZ = 1e5 + 5;

struct Splay {
  int tot, ch[SZ][2], key[SZ], sz[SZ], pa[SZ], root;
  int rv[SZ];
  int new_node(int v) {
    ++tot, ch[tot][0] = ch[tot][1] = pa[tot] = 0, key[tot] = v;
    sz[tot] = rv[tot] = 0;
    return tot;
  }
  Splay() {
    tot = 0, new_node(-INF), new_node(INF), pa[1] = 2, ch[2][0] = 1, root = 2;
  }
  bool get(int u) { return ch[pa[u]][1] == u; }
  void pushup(int u) { sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1; }
  void node_rv(int u) {
    if (!u) return;
    swap(ch[u][0], ch[u][1]), rv[u] ^= 1;
  }
  void pushdown(int u) {
    if (rv[u]) node_rv(ch[u][0]), node_rv(ch[u][1]), rv[u] = 0;
  }
  void rotate(int u) {
    int p = pa[u], pp = pa[p], gu = get(u);
    pushdown(u);
    ch[pp][get(p)] = u, pa[u] = pp;
    ch[p][gu] = ch[u][gu ^ 1], pa[ch[u][gu ^ 1]] = p;
    ch[u][gu ^ 1] = p, pa[p] = u;
    pushup(p), pushup(u);
  }
  void splay(int u, int v) {
    while (pa[u] != v) {
      int p = pa[u];
      if (pa[p] != v) rotate(get(u) == get(p) ? p : u);
      rotate(u);
    }
    if (!v) root = u;
  }
  bool find(int v) { // return if v exists. Based on key
    if (!root) return 0;
    int u = root;
    while (key[u] != v && ch[u][key[u] < v]) pushdown(u), u = ch[u][key[u] < v];
    splay(u, 0);
    return key[root] == v;
  }
  void insert(int v) {
    if (!root) return root = new_node(v), void();
    int u = root, nu = new_node(v);
    while (ch[u][key[u] < v]) pushdown(u), u = ch[u][key[u] < v];
    ch[u][key[u] < v] = nu, pa[nu] = u;
    splay(nu, 0);
  }
  int kth(int rk) {
    ++rk;
    if (!root) return 0;
    int u = root;
    while (sz[ch[u][0]] + 1 != rk) {
      pushdown(u);
      if (rk <= sz[ch[u][0]]) u = ch[u][0];
      else rk -= sz[ch[u][0]] + 1, u = ch[u][1];
    }
    splay(u, 0);
    return u;
  }
};
