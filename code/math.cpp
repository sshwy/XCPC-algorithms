#include "head.h"
namespace Rho {
  LL gcdll(LL a, LL b) { return b ? gcdll(b, a % b) : a; }
  LL mull(LL a, LL b, LL p) { // assert(a < p && b < p);
    LL d = a * (long double)b / p + 0.5, res = (a * b - d * p) % p;
    if (res < 0) res += p;
    return res;
  }
  LL Pow(LL a, LL b, LL mod) { // assert(a < mod && b < mod);
    LL res = 1;
    for (; b; b >>= 1, a = mull(a, a, mod))
      if (b & 1) res = mull(res, a, mod);
    return res;
  }
  const LL _A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022ll};
  bool MillerRabin(LL n) { // return true if is prime
    if (n == 1) return false;
    if (n > 2 && n % 2 == 0) return false;
    LL tmp = n - 1;
    int ct = 0;
    while (!(tmp & 1)) tmp >>= 1, ct++;
    for (int i = 0; i < 6; i++) {
      LL a = Pow(_A[i], tmp, n), nxt = a;
      if (a == 0) continue;
      for (int j = 1; j <= ct; j++) {
        nxt = mull(a, a, n);
        if (nxt == 1 && a != 1 && a != n - 1) return false;
        a = nxt;
      }
      if (a != 1) return false;
    }
    return true;
  }
  LL _rand() { return (LL)rand() << 48 | (LL)rand() << 32 | rand() << 16 | rand(); }
  LL absll(LL x) { return x >= 0 ? x : -x; }
  LL PollardRho(LL n) {
    LL s = 0, t = 0, c = _rand() % (n - 1) + 1, val = 1;
    for (int cir = 1;; cir <<= 1, s = t, val = 1) {
      for (int i = 0; i < cir; i++) {
        t = (mull(t, t, n) + c) % n, val = mull(val, absll(t - s), n);
        if (i % 127 == 0) {
          LL g = gcdll(val, n);
          if (g != 1) return g;
        }
      }
      LL g = gcdll(val, n);
      if (g != 1) return g;
    }
  }
  LL findFactor(LL n) {
    if (n == 1) return 1;
    while (!MillerRabin(n)) {
      LL d = n;
      while (d == n) d = PollardRho(n);
      n = d;
    }
    return n;
  }
  vector<LL> PrimeFactor(LL n) {
    vector<LL> res;
    while (n > 1) {
      LL x = findFactor(n);
      res.push_back(x);
      while (n % x == 0) n /= x;
    }
    return res;
  }
} // namespace Rho