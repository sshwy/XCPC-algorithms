namespace EXBSGS {
  const lld SZ = 433337;
  struct hash_map {
    struct data {
      lld u, v, nex;
    };
    data e[SZ];
    lld h[SZ], le;
    lld hash(lld u) { return (u % SZ + SZ) % SZ; }
    lld &operator[](lld u) {
      lld hu = hash(u);
      for (lld i = h[hu]; i; i = e[i].nex)
        if (e[i].u == u) return e[i].v;
      return e[++le] = (data){u, -1, h[hu]}, h[hu] = le, e[le].v;
    }
    void clear() { memset(h, 0, sizeof(h)), le = 0; }
  } h;
  lld gcd(lld a, lld b) { return b ? gcd(b, a % b) : a; }
  lld mul(lld a, lld b, lld p) {
    if (p <= 1000000000ll) return 1ll * a * b % p;
    if (p <= 1000000000000ll)
      return (((a * (b >> 20) % p) << 20) % p + a * (b & ((1 << 20) - 1))) % p;
    lld d = floor(a * (long double)b / p);
    lld res = (a * b - d * p) % p;
    if (res < 0) res += p;
    return res;
  }
  lld pw(lld a, lld m, lld p) {
    lld res = 1;
    while (m) m & 1 ? res = mul(res, a, p) : 0, a = mul(a, a, p), m >>= 1;
    return res;
  }
  lld exgcd(lld a, lld b, lld &x, lld &y) {
    if (!b) return x = 1, y = 0, a;
    lld t = exgcd(b, a % b, y, x);
    return y = y - (a / b) * x, t;
  }
  lld inv(lld a, lld p) {
    lld b, t, g = exgcd(a, p, b, t);
    if (g > 1) return -1;
    return ((b % p) + p) % p;
  }
  lld bsgs(lld a, lld b, lld p) {
    a %= p, b %= p, h.clear();
    if (b == 1) return 0;
    if (!a && !b) return 1;
    if (!a) return -1;
    lld t = sqrt(p) + 0.5, cur = b, q = 1;
    FOR(i, 0, t) h[cur] = i, cur = mul(cur, a, p);
    cur = pw(a, t, p);
    FOR(i, 0, t) {
      if (h[q] != -1 && i * t - h[q] >= 0) return i * t - h[q];
      q = mul(q, cur, p);
    }
    return -1;
  }
  lld exbsgs(lld a, lld b, lld p) {
    lld d = 0, f = 1, g;
    while ((g = gcd(a, p)) > 1) {
      if (b % g) return -1;
      ++d, f = mul(f, g, p), b /= g, p /= g;
    }
    lld ia = inv(a, p);
    f = mul(f, pw(ia, d, p), p);
    b = mul(b, f, p);
    lld res = bsgs(a, b, p);
    return ~res ? res + d : -1;
  }
} // namespace EXBSGS
/*
 * exbsgs: 求a^x=b mod p 的最小非负整数解。-1表示无解
 */
