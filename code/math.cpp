namespace math {
  int powmod(int a, int b, int mod) {
    int res = 1;
    for (; b; b >>= 1, a = 1ll * a * a % mod)
      if (b & 1) res = 1ll * res * a % mod;
    return res;
  }
  LL mul(LL a, LL b, LL p) {
    if (p <= 1000000000ll) return 1ll * a * b % p;
    if (p <= 1000000000000ll)
      return (((a * (b >> 20) % p) << 20) % p + a * (b & ((1 << 20) - 1))) % p;
    LL d = floor(a * (long double)b / p);
    LL res = (a * b - d * p) % p;
    if (res < 0) res += p;
    return res;
  }
  LL powmod(LL a, LL b, LL mod) {
    LL res = 1;
    for (; b; b >>= 1, a = mul(a, a, mod))
      if (b & 1) res = mul(res, a, mod);
    return res;
  }
  bool check(LL a, LL x, LL times, LL n) {
    LL tmp = powmod(a, x, n);
    while (times--) {
      LL last = mul(tmp, tmp, n);
      if (last == 1 && tmp != 1 && tmp != n - 1) return 0;
      tmp = last;
    }
    return tmp == 1;
  }
  int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
  const int S = 8;
  bool Miller(LL n) {
    FOR(i, 0, S) {
      if (n == base[i]) return 1;
      if (n % base[i] == 0) return 0;
    }
    LL x = n - 1, times = 0;
    while (!(x & 1)) times++, x >>= 1;
    FOR(_, 0, S) if (!check(base[_], x, times, n)) return 0;
    return 1;
  }
#define mytz __builtin_ctzll
  LL gcd(LL a, LL b) {
    if (!a) return b;
    if (!b) return a;
    register int t = mytz(a | b);
    a >>= mytz(a);
    do {
      b >>= mytz(b);
      if (a > b) {
        LL t = b;
        b = a, a = t;
      }
      b -= a;
    } while (b);
    return a << t;
  }
#define F(x) ((mul(x, x, n) + c) % n)
  LL rho(LL n, LL c) {
    LL x = 1ll * rand() * rand() % n, y = F(x);
    while (x ^ y) {
      LL w = gcd(abs(x - y), n);
      if (w > 1 && w < n) return w;
      x = F(x), y = F(y), y = F(y);
    }
    return 1;
  }
  LL calc(LL x) {
    if (Miller(x)) return x;
    LL fsf = 0; // while((fsf=rho(x,rand()%x))==1);
    while ((fsf = rho(x, 2)) == 1)
      ;
    return max(calc(fsf), calc(x / fsf));
  }
} // namespace math
/*
 * 不知从何处拉来的强大板子
 * func.powmod(int,int,int) 32位整型快速幂
 * func.mul(LL,LL,LL) 64位长整型数的乘法运算
 * func.powmod(LL,LL,LL) 64位长整型数的快速幂
 */
