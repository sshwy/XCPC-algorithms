int pw(int a, int m, int p) {
  int res = 1;
  while (m) m & 1 ? res = 1ll * res * a % p : 0, a = 1ll * a * a % p, m >>= 1;
  return res;
}
struct sqrtNum {
  int W, P;
  int a, b; // a+b*sqrt(W)
  sqrtNum(int _a, int _b, int _w, int _p) { a = _a, b = _b, W = _w, P = _p; }
  sqrtNum operator*(const sqrtNum &x) const {
    return sqrtNum((1ll * a * x.a % P + 1ll * b * x.b % P * W) % P,
      (1ll * a * x.b % P + 1ll * b * x.a) % P, W, P);
  }
};
int quad_res(int n, int p) {
  n %= p;
  assert(p & 1);
  if (pw(n, (p - 1) / 2, p) == p - 1) return -1; // no solution
  if (n == 0) return 0;
  int a;
  srand(clock() + time(0));
  do a = rand() % p;
  while (pw((a * 1ll * a % p - n + p) % p, (p - 1) / 2, p) == 1);
  int w2 = (a * 1ll * a % p - n + p) % p;
  sqrtNum q(a, 1, w2, p), qm(1, 0, w2, p);
  for (int m = (p + 1) / 2; m; m >>= 1, q = q * q)
    if (m & 1) qm = qm * q;
  assert(qm.b == 0);
  return qm.a;
}
