const int SZ = 1e6 + 6;

int tot, ch[SZ][2], f[SZ], val[SZ], sz[SZ], rv[SZ];
int sxor[SZ];

int new_node(int v) {
  ++tot, ch[tot][0] = ch[tot][1] = f[tot] = rv[tot] = 0;
  sz[tot] = 1, val[tot] = v, sxor[tot] = v;
  return tot;
}
void pushup(int u) {
  sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
  sxor[u] = sxor[ch[u][0]] ^ sxor[ch[u][1]] ^ val[u];
}
void noderv(int u) {
  if (u) rv[u] ^= 1;
}
void nodeassign(int u, int v) { val[u] = v, pushup(u); }
void pushdown(int u) {
  if (rv[u]) swap(ch[u][0], ch[u][1]), noderv(ch[u][0]), noderv(ch[u][1]), rv[u] = 0;
}
bool isroot(int u) { return ch[f[u]][0] != u && ch[f[u]][1] != u; }
bool get(int u) { return ch[f[u]][1] == u; }
void rotate(int u) {
  int p = f[u], pp = f[p], k;
  pushdown(p), pushdown(u), k = get(u); // k的赋值必须在pushdown后！
  if (!isroot(p)) ch[pp][get(p)] = u; //!!!
  ch[p][k] = ch[u][!k], f[ch[u][!k]] = p;
  ch[u][!k] = p, f[p] = u, f[u] = pp;
  pushup(p), pushup(u);
}
void splay(int u) {
  pushdown(u);
  for (int p; p = f[u], !isroot(u); rotate(u))
    if (!isroot(p)) rotate(get(p) == get(u) ? p : u);
}
void access(int u) {
  for (int p = 0; u; p = u, u = f[u]) splay(u), ch[u][1] = p, pushup(u);
}
void makeroot(int u) { access(u), splay(u), noderv(u); }
bool check_link(int x, int y) {
  makeroot(x), access(y), splay(x), splay(y);
  return !(isroot(x) && isroot(y));
}
void link(int x, int y) { makeroot(x), f[x] = y; }
bool check_edge(int x, int y) {
  if (!check_link(x, y)) return 0;
  makeroot(x), access(y), splay(y);
  if (ch[y][0] != x || ch[x][1]) return 0;
  return 1;
}
void cut(int x, int y) {
  makeroot(x), access(y), splay(y), ch[y][0] = f[x] = 0, pushup(y);
}
void assign(int x, int y) { splay(x), nodeassign(x, y); }
int query(int x, int y) { return makeroot(x), access(y), splay(y), sxor[y]; }
/*
 * 模板：Luogu3690
 * new_node: 新建权值为 v 的结点
 * pushup: 信息更新
 * pushdown: 标记下传，主要是翻转标记
 * noderv: 对某一个结点施加标记。
 *     LCT的标记不同于线段树，必须在下传的时侯再更新当前结点的信息。不然
 *     get 的时侯会出锅
 * nodeassign: 模板题需要
 * isroot: 是否是所在Splay的根
 * get: 是Splay上左儿子还是右儿子
 * print: 调试函数
 * rotate: 双旋，注意与Splay的双旋不同，要判f[u]是不是root，不然f[f[u]]的
 *     儿子不能乱赋值
 * splay: 把当前结点旋转到当前Splay的根结点，要用到isroot函数。一开始
 *     先pushdown。
 * access: 把当前结点到根的路径连成一个Splay，注意这个Splay只包含当前结点
 *     到根这段路径上的点，不包括当前结点子树的那一段（非到叶结点的树链）
 *     access完之后这个点不一定是所在splay的根，需要手动splay一下
 * makeroot: 把当前结点变成原树的根，这个结点也会顺便变成所在Splay的根。
 * check_link: 判断两个点是否连通。
 * link: 连接两个不连通的点
 * check_edge: 判断两个点是否直连通（有没有边）
 * cut: 删掉 (x,y) 的边。
 * assign: 模板题需要
 * query: 模板题需要
 * 提醒：在修改了ch指针后要考虑是否pushup
 */
