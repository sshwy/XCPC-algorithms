#include "head.h"
const int P = 1e9 + 7, K = 1005;
int pw(int a, int m) {
  int res = 1;
  while (m) m & 1 ? res = 1ll * res * a % P : 0, a = 1ll * a * a % P, m >>= 1;
  return res;
}
int fnv[K], d[K];
void work(int k, int *d) { // prepare for 0^k + 1^k + 2^k + ...
  FOR(i, 0, k + 1) d[i] = pw(i, k);
  FOR(i, 1, k + 1) ROF(j, k + 1, i + 1) d[j] = (d[j] - d[j - 1] + P) % P;
  fnv[0] = 1;
  FOR(i, 1, k + 1) fnv[i] = 1ll * fnv[i - 1] * pw(i, P - 2) % P;
}
int calc(int n, int k, int *d) { // 0^k + ... + n^k
  int res = 0, coef = 1;
  FOR(i, 0, k + 1) {
    res = (res + 1ll * coef * fnv[i] % P * d[i]) % P;
    coef = 1ll * coef * (n - i) % P;
  }
  return res;
}