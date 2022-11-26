#include "head.h"
const int N = 5e6 + 6;
int T, n, lim = 5e6, mu[N], pn[N], cnt;
bool vis[N];
LL phi[N];
void sieve(int n) {
  vis[0] = vis[1] = 1, mu[1] = 1, phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) pn[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
    for (int j = 1; j <= cnt; j++) {
      const int x = i * pn[j];
      if (x > n) break;
      vis[x] = 1;
      if (i % pn[j]) {
        phi[x] = phi[i] * phi[pn[j]];
        mu[x] = mu[i] * mu[pn[j]];
      } else {
        phi[x] = phi[i] * pn[j];
        mu[x] = 0;
        break;
      }
    }
  }
  for (int i = 2; i <= n; i++) phi[i] += phi[i - 1], mu[i] += mu[i - 1];
}
unordered_map<int, LL> mphi, mmu;
LL calc_phi(int n) {
  if (n <= lim) return phi[n];
  if (mphi.find(n) != mphi.end()) return mphi[n];
  LL res = (LL)n * (n + 1) / 2;
  int p = 2, q;
  while (p <= n) {
    q = n / (n / p);
    res -= calc_phi(n / p) * (q - p + 1);
    p = q + 1;
  }
  return mphi[n] = res;
}
int calc_mu(int n) {
  if (n <= lim) return mu[n];
  if (mmu.find(n) != mmu.end()) return mmu[n];
  int res = 1, p = 2, q;
  while (p <= n) {
    q = n / (n / p);
    res -= calc_mu(n / p) * (q - p + 1);
    p = q + 1;
  }
  return mmu[n] = res;
}
int main() {
  sieve(lim);
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    printf("%lld %d\n", calc_phi(n), calc_mu(n));
  }
  return 0;
}