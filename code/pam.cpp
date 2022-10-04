const int SZ = 5e5 + 500, ALP = 26;
struct PAM {
  int tot, last;
  int len[SZ], tr[SZ][ALP], fail[SZ];
  int s[SZ], ls; // 字符串的内容 -'0'
  int cnt[SZ], num[SZ]; //状态出现次数、fail树上的深度（有多少回文后缀）
  int newnode(int l) {
    ++tot, len[tot] = l, fail[tot] = 0, cnt[tot] = 0;
    FOR(i, 0, ALP - 1) tr[tot][i] = 0;
    return tot;
  }
  void clear() {
    tot = -1, newnode(0), newnode(-1), fail[0] = 1, last = 0,
    s[ls = 0] = -1; //减掉'a'后0就不是非匹配字符了，所以要整成-1
  }
  PAM() { clear(); }
  int getfail(int u) {
    // 将结点 u 的 fail 链状态上的状态尝试去用 s[ls] 扩展，返回这个可扩展的结点
    while (s[ls - len[u] - 1] != s[ls]) u = fail[u];
    return u;
  }
  void insert(char c) {
    s[++ls] = (c -= 'a');
    int cur = getfail(last);
    if (!tr[cur][c]) { // 如果没有转移就添加
      int u = newnode(len[cur] + 2);
      fail[u] = tr[getfail(fail[cur])][c];
      tr[cur][c] = u;
      // 在此处更新 tot 的卫星信息
      num[tot] = num[fail[tot]] + 1;
    }
    last = tr[cur][c];
    // 在此处更新 last 的卫星信息
    cnt[last]++;
  }
  void count() { //最后用来计算每个状态的出现次数
    ROF(i, tot, 0) cnt[fail[i]] += cnt[i];
  }
};
/*
 * 0 号结点表示 0 结点
 * 1 号结点表示 -1 结点，长度为 -1
 * last 记录上一次插入的字符所在结点的编号
 */
