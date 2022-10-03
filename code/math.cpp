typedef long long lld;
namespace math {
  inline int powmod(int a, int b, int mod) {
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
      if (b & 1) res = 1ll * res * a % mod;
    return res;
  }
  inline lld mul(lld a, lld b, lld p) {
    if (p <= 1000000000ll) return 1ll * a * b % p;
    if (p <= 1000000000000ll)
      return (((a * (b >> 20) % p) << 20) % p + a * (b & ((1 << 20) - 1))) % p;
    lld d = floor(a * (long double)b / p);
    lld res = (a * b - d * p) % p;
    if (res < 0) res += p;
    return res;
  }
  inline lld powmod(lld a, lld b, lld mod) {
    lld res = 1;
    for (; b; b >>= 1, a = mul(a, a, mod))
      if (b & 1) res = mul(res, a, mod);
    return res;
  }
  inline bool check(lld a, lld x, lld times, lld n) {
    lld tmp = powmod(a, x, n);
    while (times--) {
      lld last = mul(tmp, tmp, n);
      if (last == 1 && tmp != 1 && tmp != n - 1) return 0;
      tmp = last;
    }
    return tmp == 1;
  }
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  const int S = 8;
  inline bool Miller(lld n) {
    FOR(i, 0, S) {
      if (n == base[i]) return 1;
      if (n % base[i] == 0) return 0;
    }
    lld x = n - 1, times = 0;
    while (!(x & 1)) times++, x >>= 1;
    FOR(_, 0, S) if (!check(base[_], x, times, n)) return 0;
    return 1;
  }
#define mytz __builtin_ctzll
  inline lld gcd(lld a, lld b) {
    if (!a) return b;
    if (!b) return a;
    register int t = mytz(a | b);
    a >>= mytz(a);
    do {
      b >>= mytz(b);
      if (a > b) {
        lld t = b;
        b = a, a = t;
      }
      b -= a;
    } while (b);
    return a << t;
  }
#define F(x) ((mul(x, x, n) + c) % n)
  inline lld rho(lld n, lld c) {
    lld x = 1ll * rand() * rand() % n, y = F(x);
    while (x ^ y) {
      lld w = gcd(abs(x - y), n);
      if (w > 1 && w < n) return w;
      x = F(x), y = F(y), y = F(y);
    }
    return 1;
  }
  inline lld calc(lld x) {
    if (Miller(x)) return x;
    lld fsf = 0; // while((fsf=rho(x,rand()%x))==1);
    while ((fsf = rho(x, 2)) == 1)
      ;
    return max(calc(fsf), calc(x / fsf));
  }
} // namespace math
/*
 * 不知从何处拉来的强大板子
 * func.powmod(int,int,int) 32位整型快速幂
 * func.mul(lld,lld,lld) 64位长整型数的乘法运算
 * func.powmod(lld,lld,lld) 64位长整型数的快速幂
 */
