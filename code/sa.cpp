#include "head.h"
const int N = 5e5 + 5;
struct SA {
  char s[N];
  int l, sz, sa[N], rk[N];
  int t[N], bin[N], h[N], he[N]; // h,height
  void qsort() {
    for (int i = 0; i <= sz; i++) bin[i] = 0;
    FOR(i, 1, l) bin[rk[i]]++;
    FOR(i, 1, sz) bin[i] += bin[i - 1];
    ROF(i, l, 1) sa[bin[rk[t[i]]]--] = t[i];
  }
  void make() { // 记得先把 s 赋值（1 起点）
    l = strlen(s + 1), sz = max(l, 127);
    FOR(i, 1, l) t[i] = i, rk[i] = s[i];
    qsort();
    for (int j = 1; j <= l; j <<= 1) {
      int tot = 0;
      FOR(i, l - j + 1, l) t[++tot] = i;
      FOR(i, 1, l) if (sa[i] - j > 0) t[++tot] = sa[i] - j;
      qsort();
      memcpy(t, rk, sizeof(int) * (l + 1));
      rk[sa[1]] = tot = 1;
      for (int i = 2; i <= l; i++)
        rk[sa[i]] =
          t[sa[i - 1]] == t[sa[i]] && t[sa[i - 1] + j] == t[sa[i] + j] ? tot : ++tot;
    }
  }
  // 下面是 height 的部分
  int move(int x, int y, int len) {
    while (x + len <= l && y + len <= l && s[x + len] == s[y + len]) ++len;
    return len;
  }
  void calc_h() {
    FOR(i, 1, l) h[i] = rk[i] == 1 ? 0 : move(i, sa[rk[i] - 1], max(h[i - 1] - 1, 0));
  }
  int st[N][20]; // h[sa[i]]~h[sa[i+2^j]] 中的最小值
  void make_st() {
    FOR(i, 1, l) st[i][0] = h[sa[i]];
    for (int j = 1; (1 << j) <= l; j++)
      for (int i = 1, step = 1 << j - 1; i + step <= l; i++)
        st[i][j] = min(st[i][j - 1], st[i + step][j - 1]);
  }
  int lg2[N];
  void init_lg() { FOR(i, 2, l) lg2[i] = lg2[i / 2] + 1; }
  // 如果要 lcp 的话只用调用这个就行
  void prepare_lcp() { make(), calc_h(), make_st(), init_lg(); }
  int lcp(int x, int y) { // 返回长度
    if (x == y) return l - x + 1;
    x = rk[x], y = rk[y];
    if (x > y) swap(x, y);
    int step = lg2[y - x];
    return min(st[x + 1][step], st[y - (1 << step) + 1][step]);
  }
};
