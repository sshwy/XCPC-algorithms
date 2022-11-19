#include "head.h"
const int SZ = 1e6 + 500, ALP = 26;
// 0 号结点表示 0 结点，1 号结点表示 -1 结点，长度为 -1
// las 记录上一次插入的字符所在结点的编号
int tot, las, s[SZ], ls; // 字符串的内容 -'0'
int len[SZ], tr[SZ][ALP], fail[SZ];
// d[u] == len[u] - len[fail[u]]，等差数列公差
// top[u]: u 所在等差数列的开头父亲，第一个 d[u] != d[top[u]] 的结点
int d[SZ], top[SZ];
int newNode(int l) {
  ++tot, len[tot] = l, fail[tot] = 0;
  FOR(i, 0, ALP - 1) tr[tot][i] = 0;
  return tot;
}
int getfail(int u) {
  // 将 u 的 fail 链状态上的状态尝试去用 s[ls] 扩展，返回第一个可扩展结点
  while (s[ls - len[u] - 1] != s[ls]) u = fail[u];
  return u;
}
void insert(int c) { // assert(0 <= c && c < ALP);
  s[++ls] = c;
  int cur = getfail(las);
  if (!tr[cur][c]) { // 如果没有转移就添加
    int u = newNode(len[cur] + 2);
    fail[u] = tr[getfail(fail[cur])][c], tr[cur][c] = u;

    d[u] = len[u] - len[fail[u]]; // assert(d[u] >= d[fail[u]]);
    if (d[u] != d[fail[u]]) top[u] = fail[u];
    else top[u] = top[fail[u]];
  }
  las = tr[cur][c];
}
void init() {
  tot = -1, newNode(0), newNode(-1), fail[0] = 1, las = 0;
  d[0] = d[1] = 0, top[0] = 1;
  s[ls = 0] = -1; // -1 表示非匹配字符
}

const int N = 1e6 + 5, P = 1e9 + 7;
// f: 回文划分方案数
// g[u]: sum f[i - len[v]]，v 是 u 的祖先（含）top[u] 的子孙（不含）
int g[SZ], f[N];
int solve(string str) {
  int n = str.size();
  init();
  f[0] = 1;
  FOR(i, 1, n) {
    insert(str[i - 1] - 'a');
    for (int u = las; u > 1; u = top[u]) {
      g[u] = f[i - len[top[u]] - d[u]] % P;
      if (fail[u] != top[u]) g[u] = (g[u] + g[fail[u]]) % P;
    }
    for (int u = las; u > 1; u = top[u]) f[i] = (f[i] + g[u]) % P;
  }
  return f[n];
}
