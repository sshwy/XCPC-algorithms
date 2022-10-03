const int SZ = 2e6 + 500, ALP = 26;

struct SAM {
  int tot, last;
  int tr[SZ][ALP], fail[SZ];
  int len[SZ], cnt[SZ], end[SZ];
  int s[SZ], ls;
  SAM() { tot = last = 1, len[1] = 0, fail[1] = 0; }
  void insert(char x) {
    s[++ls] = x;
    x -= 'a';
    int u = ++tot, p = last;
    len[u] = len[last] + 1, last = u;
    cnt[u] = 1, end[u] = ls; // u 的卫星信息
    while (p && tr[p][x] == 0) tr[p][x] = u, p = fail[p];
    if (!p) fail[u] = 1;
    else {
      int q = tr[p][x];
      if (len[q] == len[p] + 1) fail[u] = q;
      else {
        int cq = ++tot;
        len[cq] = len[p] + 1, fail[cq] = fail[q];
        end[cq] = end[q]; //如果需要，更新的cq的卫星信息
        memcpy(tr[cq], tr[q], sizeof(tr[q]));
        fail[q] = fail[u] = cq;
        while (p && tr[p][x] == q) tr[p][x] = cq, p = fail[p];
      }
    }
  }
  int a[SZ], bin[SZ], tim[SZ];
  void count() { //桶排，统计cnt
    FOR(i, 1, tot) bin[len[i]]++;
    FOR(i, 1, tot) bin[i] += bin[i - 1];
    FOR(i, 1, tot) a[bin[len[i]]--] = i;
    ROF(i, tot, 1) cnt[fail[a[i]]] += cnt[a[i]];
  }
  void print_node(int u) { //输出每个结点的状态
    printf("u=%d,cnt=%d,len=%d,fail=%d, ", u, cnt[u], len[u], fail[u]);
    FOR(i, end[u] - len[u] + 1, end[u]) putchar(s[i]);
    puts("");
  }
};
/*
 * cnt:状态出现次数;end：状态的结尾位置
 * tim：每个结点的时间戳
 */
