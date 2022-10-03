struct SA {
  char s[N];
  int l;
  int sa[N], rk[N];
  int t[N], bin[N], sz;
  int h[N], he[N]; // h,height
  void qsort() {
    for (int i = 0; i <= sz; i++) bin[i] = 0;
    for (int i = 1; i <= l; i++) bin[rk[i]]++;
    for (int i = 1; i <= sz; i++) bin[i] += bin[i - 1];
    for (int i = l; i >= 1; i--) sa[bin[rk[t[i]]]--] = t[i];
  }
  void make(char *s) {
    l = strlen(s + 1), sz = max(l, 'z' - '0' + 1);
    for (int i = 1; i <= l; i++) t[i] = i, rk[i] = s[i] - '0' + 1;
    qsort();
    for (int j = 1; j <= l; j <<= 1) {
      int tot = 0;
      for (int i = l - j + 1; i <= l; i++) t[++tot] = i;
      for (int i = 1; i <= l; i++)
        if (sa[i] - j > 0) t[++tot] = sa[i] - j;
      qsort();
      memcpy(t, rk, sizeof(int) * (l + 1));
      rk[sa[1]] = tot = 1;
      for (int i = 2; i <= l; i++)
        rk[sa[i]] =
            t[sa[i - 1]] == t[sa[i]] && t[sa[i - 1] + j] == t[sa[i] + j] ? tot : ++tot;
    }
  }
  int move(int x, int y, int len) {
    while (x + len <= l && y + len <= l && s[x + len] == s[y + len]) ++len;
    return len;
  }
  void calc_h() {
    for (int i = 1; i <= l; i++)
      h[i] = rk[i] == 1 ? 0 : move(i, sa[rk[i] - 1], max(h[i - 1] - 1, 0));
  }
  int st[N][16]; // h[sa[i]]~h[sa[i+2^j]] 中的最小值
  void make_st() {
    for (int i = 1; i <= l; i++) st[i][0] = h[sa[i]];
    for (int j = 1; (1 << j) <= l; j++) {
      int step = 1 << (j - 1);
      for (int i = 1; i + step <= l; i++) {
        st[i][j] = min(st[i][j - 1], st[i + step][j - 1]);
      }
    }
  }
  int lcp(int x, int y) { // 返回长度
    if (x == y) return l - x + 1;
    x = rk[x], y = rk[y];
    if (x > y) swap(x, y);
    x++; // 取不到 x
    int step = log(y - x + 1) / log(2);
    return min(st[x][step], st[y - (1 << step) + 1][step]);
  }
};
