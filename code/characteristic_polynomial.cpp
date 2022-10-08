int pw(int a, int m) {
  int res = 1;
  while (m) m & 1 ? res = 1ll * res * a % P : 0, a = 1ll * a * a % P, m >>= 1;
  return res;
}

typedef vector<int> Poly;

Poly operator-(const Poly &p, const Poly &q) {
  Poly res = p;
  res.resize(max(p.size(), q.size()), 0);
  for (long unsigned i = 0; i < q.size(); ++i) res[i] = (res[i] - q[i] + P) % P;
  return res;
}
Poly operator+(const Poly &p, const Poly &q) {
  Poly res = p;
  res.resize(max(p.size(), q.size()), 0);
  for (long unsigned i = 0; i < q.size(); ++i) res[i] = (res[i] + q[i]) % P;
  return res;
}
Poly operator*(const Poly &p, const Poly &q) {
  if (!p.size() || !q.size()) return Poly();
  Poly res(p.size() + q.size() - 1, 0);
  for (long unsigned i = 0; i < p.size(); i++)
    for (long unsigned j = 0; j < q.size(); j++)
      res[i + j] = (res[i + j] + p[i] * 1ll * q[j] % P) % P;
  return res;
}
Poly operator%(const Poly &p, const Poly &q) { // mod
  assert(q.size());
  Poly res = p;
  while (res.size() >= q.size()) {
    int d = res.size() - q.size();
    int rate = res.back() * 1ll * pw(q.back(), P - 2) % P;
    for (long unsigned i = 0; i < q.size(); i++)
      res[i + d] = (res[i + d] - q[i] * 1ll * rate % P + P) % P;
    assert(res.back() == 0);
    res.pop_back();
  }
  return res;
}

int t[N][N];
int det(int g[N][N], int n) {
  memcpy(t, g, sizeof(t)), g = t;
  int res = 1;
  FOR(i, 1, n) {
    if (!g[i][i]) FOR(j, i + 1, n) if (g[j][i]) {
        FOR(k, i, n) swap(g[i][k], g[j][k]);
        res = P - res;
        break;
      }
    if (!g[i][i]) return 0;
    FOR(j, 1, n) if (i != j) {
      int rate = g[j][i] * 1ll * pw(g[i][i], P - 2) % P;
      FOR(k, i, n) g[j][k] = (g[j][k] - g[i][k] * 1ll * rate % P + P) % P;
    }
  }
  FOR(i, 1, n) res = res * 1ll * g[i][i] % P;
  return res;
}

int t2[N][N];
Poly p[N];
Poly characteristic_polynomial(int M[N][N], int n) { //求M的特征多项式
  memcpy(t2, M, sizeof(t2)), M = t2;
  int x = det(M, n);
  // 1. 化为上海森堡矩阵
  FOR(j, 1, n - 1) { //列
    if (!M[j + 1][j]) FOR(i, j + 2, n) if (M[i][j]) {
        FOR(k, 1, n) swap(M[j + 1][k], M[i][k]); // R[j+1] <-> R[i]
        FOR(k, 1, n) swap(M[k][j + 1], M[k][i]); // C[j+1] <-> C[i]
        break;
      }
    //把第j列的第j+1行以下的位置全部消元
    FOR(i, j + 2, n) if (M[i][j]) {
      int rate = M[i][j] * 1ll * pw(M[j + 1][j], P - 2) % P;
      FOR(k, 1, n)
      M[i][k] = (M[i][k] - M[j + 1][k] * 1ll * rate % P + P) %
                P; // R[i]   = R[i]-rate*R[j+1]
      FOR(k, 1, n)
      M[k][j + 1] =
          (M[k][j + 1] + M[k][i] * 1ll * rate % P) % P; // C[j+1] = C[j+1]+rate*C[i]
    }
  }
  assert(x == det(M, n));
  // 2. 计算特征多项式：即(xI-A)的行列式
  p[n + 1] = Poly(1, 1);
  ROF(i, n, 1) {
    Poly s, t;

    t = Poly(1, P - M[i][n]);
    if (i == n) t.pb(1); // x-M[n][n]
    s = p[n + 1] * t;
    ROF(j, n, i + 1) {
      t = Poly(1, P - M[i][j - 1]);
      if (i == j - 1) t.pb(1);
      s = t * p[j] - Poly(1, P - M[j][j - 1]) * s;
    }
    p[i] = s;
  }
  return p[1];
}
