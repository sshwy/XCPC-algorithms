// by Yao
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)

const int N = 404;
const long long INF = 1e18;

int n, nl, nr, m;
long long w[N][N], hl[N], hr[N], slack[N];
int pre[N], toR[N], toL[N], q[N], ql, qr;
bool vl[N], vr[N];

bool push(int v) { // v in L。找到増广路则返回 true
  vl[v] = true;
  if (toR[v]) { // 存在与 v 匹配的点，就入队
    q[++qr] = toR[v];
    vr[toR[v]] = true;
    return false;
  }
  while (v) { // 找到増广路，就増广
    toR[v] = pre[v];
    swap(v, toL[pre[v]]);
  }
  return true;
}
void bfs(int s) { // s in R
  fill(vl + 1, vl + n + 1, false);
  fill(vr + 1, vr + n + 1, false);
  fill(slack + 1, slack + n + 1, INF);
  ql = qr = 0, q[++qr] = s, vr[s] = true;
  while (1) {
    while (ql < qr) {
      int u = q[++ql]; // u in R
      FOR(v, 1, n) if (!vl[v]) {
        long long d = hl[v] + hr[u] - w[v][u];
        if (d == 0) { // 是相等子图里的点
          pre[v] = u;
          if (push(v)) return;
        } else if (slack[v] >= d) {
          slack[v] = d, pre[v] = u;
        }
      }
    }
    long long d = INF;
    FOR(i, 1, n) if (!vl[i] && d > slack[i]) d = slack[i];
    FOR(i, 1, n) {
      if (vl[i]) hl[i] += d;
      else slack[i] -= d;
      if (vr[i]) hr[i] -= d;
    }
    FOR(i, 1, n) if (!vl[i] && !slack[i] && push(i)) return;
  }
}
void KM() {
  FOR(i, 1, n) {
    hl[i] = *max_element(w[i] + 1, w[i] + n + 1);
    hr[i] = 0;
  }
  fill(slack + 1, slack + n + 1, INF);
  FOR(i, 1, n) { bfs(i); }
}
int main() {
  scanf("%d%d%d", &nl, &nr, &m);
  FOR(i, 1, m) {
    int u, v, ww;
    scanf("%d%d%d", &u, &v, &ww);
    w[u][v] = ww; // w[u,v] 和 w[v,u] 不是一个东西
  }
  n = max(nl, nr);
  KM();
  long long ans = 0;
  FOR(i, 1, n) ans += hl[i] + hr[i];
  printf("%lld\n", ans);
  // 不能用 toR[i] > nr 来判断是否有匹配，因为 0 权边是不存在的
  FOR(i, 1, nl) printf("%d%c", w[i][toR[i]] == 0 ? 0 : toR[i], " \n"[i == nl]);
  return 0;
}
