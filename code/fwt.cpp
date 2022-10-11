#include "head.h"
const LL N = 1 << 17, P = 998244353;
// fwt: tag=1
// ifwt: tag=-1
// in = pw(n, P-2, P) (inverse element if n)
LL n, in, a[N], b[N], c[N];
LL pw(LL a, LL m, LL p) {
  LL res = 1;
  while (m) m & 1 ? res = res * a % p : 0, a = a * a % p, m >>= 1;
  return res;
}
void fwt_and(LL *f, LL tag) {
  for (LL j = 1; j < n; j <<= 1)
    for (LL i = 0; i < n; i += j << 1)
      for (LL k = i; k < i + j; k++) f[k] = (f[k] + f[k + j] * tag) % P;
  FOR(i, 0, n - 1) f[i] += f[i] < 0 ? P : 0;
}
void fwt_or(LL *f, LL tag) {
  for (LL j = 1; j < n; j <<= 1)
    for (LL i = 0; i < n; i += j << 1)
      for (LL k = i; k < i + j; k++) f[k + j] = (f[k + j] + f[k] * tag) % P;
  FOR(i, 0, n - 1) f[i] += f[i] < 0 ? P : 0;
}
void fwt_xor(LL *f, LL tag) {
  for (LL j = 1; j < n; j <<= 1)
    for (LL i = 0; i < n; i += j << 1)
      for (LL k = i; k < i + j; k++) {
        LL x = f[k], y = f[k + j];
        f[k] = (x + y) % P, f[k + j] = (x - y) % P;
      }
  if (tag == -1) FOR(i, 0, n - 1) f[i] = f[i] * in % P;
  FOR(i, 0, n - 1) f[i] += f[i] < 0 ? P : 0;
}