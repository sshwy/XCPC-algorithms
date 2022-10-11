#include "head.h"
namespace EXBSGS {
  const LL SZ = 433337;
  struct hash_map {
    struct data {
      LL u, v, nex;
    };
    data e[SZ];
    LL h[SZ], le;
    LL hash(LL u) { return (u % SZ + SZ) % SZ; }
    LL &operator[](LL u) {
      LL hu = hash(u);
      for (LL i = h[hu]; i; i = e[i].nex)
        if (e[i].u == u) return e[i].v;
      return e[++le] = (data){u, -1, h[hu]}, h[hu] = le, e[le].v;
    }
    void clear() { memset(h, 0, sizeof(h)), le = 0; }
  } h;
  LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }
  LL mul(LL a, LL b, LL p) {
    if (p <= 1000000000ll) return 1ll * a * b % p;
    if (p <= 1000000000000ll)
      return (((a * (b >> 20) % p) << 20) % p + a * (b & ((1 << 20) - 1))) % p;
    LL d = floor(a * (long double)b / p);
    LL res = (a * b - d * p) % p;
    if (res < 0) res += p;
    return res;
  }
  LL pw(LL a, LL m, LL p) {
    LL res = 1;
    while (m) m & 1 ? res = mul(res, a, p) : 0, a = mul(a, a, p), m >>= 1;
    return res;
  }
  LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) return x = 1, y = 0, a;
    LL t = exgcd(b, a % b, y, x);
    return y = y - (a / b) * x, t;
  }
  LL inv(LL a, LL p) {
    LL b, t, g = exgcd(a, p, b, t);
    if (g > 1) return -1;
    return ((b % p) + p) % p;
  }
  LL bsgs(LL a, LL b, LL p) {
    a %= p, b %= p, h.clear();
    if (b == 1) return 0;
    if (!a && !b) return 1;
    if (!a) return -1;
    LL t = sqrt(p) + 0.5, cur = b, q = 1;
    FOR(i, 0, t) h[cur] = i, cur = mul(cur, a, p);
    cur = pw(a, t, p);
    FOR(i, 0, t) {
      if (h[q] != -1 && i * t - h[q] >= 0) return i * t - h[q];
      q = mul(q, cur, p);
    }
    return -1;
  }
  LL exbsgs(LL a, LL b, LL p) {
    LL d = 0, f = 1, g;
    while ((g = gcd(a, p)) > 1) {
      if (b % g) return -1;
      ++d, f = mul(f, g, p), b /= g, p /= g;
    }
    LL ia = inv(a, p);
    f = mul(f, pw(ia, d, p), p);
    b = mul(b, f, p);
    LL res = bsgs(a, b, p);
    return ~res ? res + d : -1;
  }
} // namespace EXBSGS
/*
 * exbsgs: 求a^x=b mod p 的最小非负整数解。-1表示无解
 */
