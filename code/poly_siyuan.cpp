#pragma GCC optimize("Ofast", "inline")

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <vector>

typedef std::vector<int> Vec;

const int MOD = 998244353, G = 3;

void add(int &x, int y) { (x += y) >= MOD && (x -= MOD); }
void sub(int &x, int y) { (x -= y) < 0 && (x += MOD); }
int add(int x) { return x >= MOD ? x - MOD : x; }
int sub(int x) { return x < 0 ? x + MOD : x; }
int pow(int a, int m, int MOD = MOD) {
  int res = 1;
  while (m) m & 1 ? res = 1ll * res * a % MOD : 0, a = 1ll * a * a % MOD, m >>= 1;
  return res;
}
int inv(int x, int MOD = MOD) { return pow(x, MOD - 2); }
int extend(int x) {
  int n = 1;
  while (n < x) n <<= 1;
  return n;
}
int BSGS(int a, int b, int p) {
  std::unordered_map<int, int> mp;
  int m = ceil(sqrt(p));
  for (int i = 0; i <= m; b = 1LL * b * a % p, i++) mp[b] = i;
  a = pow(a, m);
  for (int i = 0, j = 1; i < m; j = 1LL * j * a % p, i++) {
    if (mp.count(j) && i * m >= mp[j]) { return i * m - mp[j]; }
  }
  return -1;
}
int root(int p) {
  Vec fac;
  int phi = p - 1, x = phi;
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      fac.emplace_back(i);
      for (; x % i == 0; x /= i)
        ;
    }
  }
  if (x > 1) fac.emplace_back(x);
  for (int i = 2; i <= phi; i++) {
    bool flg = true;
    for (auto j : fac) {
      if (pow(i, phi / j, p) == 1) {
        flg = false;
        break;
      }
    }
    if (flg) return i;
  }
  return -1;
}
int degree(int a, int k, int p) {
  int g = root(p);
  int x = BSGS(g, a, p);
  assert(x >= 0 && x % k == 0);
  int r = pow(g, x / k);
  return std::min(r, p - r);
}

namespace FFT {
  void NTT(Vec &A, bool opt) {
    int n = A.size(), k = 0;
    for (; (1 << k) < n; k++)
      ;
    Vec rev(n);
    for (int i = 0; i < n; i++) {
      rev[i] = rev[i >> 1] >> 1 | (i & 1) << (k - 1);
      if (i < rev[i]) std::swap(A[i], A[rev[i]]);
    }
    for (int l = 2; l <= n; l <<= 1) {
      int m = l >> 1, w = pow(G, (MOD - 1) / l);
      if (opt) w = inv(w);
      for (int i = 0; i < n; i += l) {
        int wk = 1;
        for (int j = 0; j < m; j++, wk = 1LL * wk * w % MOD) {
          int p = A[i + j], q = 1LL * wk * A[i + j + m] % MOD;
          A[i + j] = (p + q) % MOD;
          A[i + j + m] = (p - q + MOD) % MOD;
        }
      }
    }
  }
  void DFT(Vec &A) { NTT(A, false); }
  void IDFT(Vec &A) {
    NTT(A, true);
    int t = inv(A.size());
    for (auto &x : A) x = 1LL * x * t % MOD;
  }
} // namespace FFT

namespace FWT {
  void transAnd(Vec &A, bool opt) {
    int n = A.size();
    for (int l = 2; l <= n; l <<= 1) {
      int m = l >> 1;
      for (int i = 0; i < n; i += l) {
        for (int j = 0; j < m; j++) {
          if (opt) {
            sub(A[i + j], A[i + j + m]);
          } else {
            add(A[i + j], A[i + j + m]);
          }
        }
      }
    }
  }
  void transOr(Vec &A, bool opt) {
    int n = A.size();
    for (int l = 2; l <= n; l <<= 1) {
      int m = l >> 1;
      for (int i = 0; i < n; i += l) {
        for (int j = 0; j < m; j++) {
          if (opt) {
            sub(A[i + j + m], A[i + j]);
          } else {
            add(A[i + j + m], A[i + j]);
          }
        }
      }
    }
  }
  void transXor(Vec &A, bool opt) {
    static const int I2 = (MOD + 1) >> 1;
    int n = A.size();
    for (int l = 2; l <= n; l <<= 1) {
      int m = l >> 1;
      for (int i = 0; i < n; i += l) {
        for (int j = 0; j < m; j++) {
          int x = A[i + j], y = A[i + j + m];
          if (opt) {
            A[i + j] = 1LL * add(x + y) * I2 % MOD;
            A[i + j + m] = 1LL * sub(x - y) * I2 % MOD;
          } else {
            A[i + j] = add(x + y);
            A[i + j + m] = sub(x - y);
          }
        }
      }
    }
  }
} // namespace FWT

namespace Poly {
  Vec operator+(Vec A, Vec B);
  Vec operator+(Vec A, int v);
  Vec operator+(int v, Vec A);
  Vec operator-(Vec A, Vec B);
  Vec operator-(Vec A, int v);
  Vec operator-(int v, Vec A);
  Vec operator-(Vec A);
  Vec operator*(Vec A, Vec B);
  Vec operator*(Vec A, int v);
  Vec operator*(int v, Vec A);
  Vec operator/(Vec A, Vec B);
  Vec operator/(Vec A, int v);
  Vec operator%(Vec A, Vec B);
  Vec operator~(Vec A);
  Vec operator^(Vec A, int k);
  Vec operator<<(Vec A, int x);
  Vec operator>>(Vec A, int x);
  Vec operator&(Vec A, Vec B);
  Vec operator|(Vec A, Vec B);
  Vec operator^(Vec A, Vec B);
  Vec fix(Vec A, int n);
  Vec der(Vec A, bool mod);
  Vec inte(Vec A, bool mod);
  Vec sqrt(Vec A);
  Vec root(Vec A, int k);
  Vec ln(Vec A);
  Vec exp(Vec A);
  Vec sin(Vec A);
  Vec cos(Vec A);
  Vec tan(Vec A);
  Vec asin(Vec A);
  Vec acos(Vec A);
  Vec atan(Vec A);
  void print(Vec A, char mid);

  Vec operator+(Vec A, Vec B) {
    int n = std::max(A.size(), B.size());
    A.resize(n), B.resize(n);
    for (int i = 0; i < n; i++) add(A[i], B[i]);
    return A;
  }
  Vec operator+(Vec A, int v) {
    add(A[0], v);
    return A;
  }
  Vec operator+(int v, Vec A) {
    add(A[0], v);
    return A;
  }
  Vec operator-(Vec A, Vec B) {
    int n = std::max(A.size(), B.size());
    A.resize(n), B.resize(n);
    for (int i = 0; i < n; i++) sub(A[i], B[i]);
    return A;
  }
  Vec operator-(Vec A, int v) {
    sub(A[0], v);
    return A;
  }
  Vec operator-(int v, Vec A) {
    A = -A, add(A[0], v);
    return A;
  }
  Vec operator-(Vec A) {
    for (auto &x : A) x = sub(-x);
    return A;
  }
  Vec operator*(Vec A, Vec B) {
    int n = A.size() + B.size() - 1, N = extend(n);
    A.resize(N), FFT::DFT(A);
    B.resize(N), FFT::DFT(B);
    for (int i = 0; i < N; i++) A[i] = 1LL * A[i] * B[i] % MOD;
    FFT::IDFT(A), A.resize(n);
    return A;
  }
  Vec operator*(Vec A, int v) {
    for (auto &x : A) x = 1LL * x * v % MOD;
    return A;
  }
  Vec operator*(int v, Vec A) {
    for (auto &x : A) x = 1LL * x * v % MOD;
    return A;
  }
  Vec operator/(Vec A, Vec B) {
    int n = A.size() - B.size() + 1;
    if (n <= 0) return Vec(1, 0);
    std::reverse(A.begin(), A.end());
    std::reverse(B.begin(), B.end());
    A.resize(n), B.resize(n);
    A = fix(A * ~B, n);
    std::reverse(A.begin(), A.end());
    return A;
  }
  Vec operator/(Vec A, int v) { return A * inv(v); }
  Vec operator%(Vec A, Vec B) {
    int n = B.size() - 1;
    return fix(A - A / B * B, n);
  }
  Vec operator~(Vec A) {
    int n = A.size(), N = extend(n);
    A.resize(N);
    Vec I(N, 0);
    I[0] = inv(A[0]);
    for (int l = 2; l <= N; l <<= 1) {
      Vec P(l), Q(l);
      std::copy(A.begin(), A.begin() + l, P.begin());
      std::copy(I.begin(), I.begin() + l, Q.begin());
      int L = l << 1;
      P.resize(L), FFT::DFT(P);
      Q.resize(L), FFT::DFT(Q);
      for (int i = 0; i < L; i++) {
        P[i] = 1LL * Q[i] * (2 - 1LL * P[i] * Q[i] % MOD + MOD) % MOD;
      }
      FFT::IDFT(P), P.resize(l);
      std::copy(P.begin(), P.begin() + l, I.begin());
    }
    I.resize(n);
    return I;
  }
  Vec operator^(Vec A, int k) {
    int n = A.size(), x = 0;
    for (; x < n && A[x] == 0; x++)
      ;
    if (1LL * x * k >= n) return Vec(n, 0);
    A = A >> x;
    int v = A[0];
    return (exp(ln(A) * k) * pow(v, k)) << (x * k);
  }
  Vec operator<<(Vec A, int x) {
    int n = A.size();
    Vec B(n, 0);
    for (int i = 0; i < n - x; i++) B[i + x] = A[i];
    return B;
  }
  Vec operator>>(Vec A, int x) {
    int n = A.size();
    Vec B(n, 0);
    for (int i = 0; i < n - x; i++) B[i] = A[i + x];
    return B;
  }
  Vec operator&(Vec A, Vec B) {
    int N = extend(std::max(A.size(), B.size()));
    A.resize(N), FWT::transAnd(A, false);
    B.resize(N), FWT::transAnd(B, false);
    for (int i = 0; i < N; i++) A[i] = 1LL * A[i] * B[i] % MOD;
    FWT::transAnd(A, true);
    return A;
  }
  Vec operator|(Vec A, Vec B) {
    int N = extend(std::max(A.size(), B.size()));
    A.resize(N), FWT::transOr(A, false);
    B.resize(N), FWT::transOr(B, false);
    for (int i = 0; i < N; i++) A[i] = 1LL * A[i] * B[i] % MOD;
    FWT::transOr(A, true);
    return A;
  }
  Vec operator^(Vec A, Vec B) {
    int N = extend(std::max(A.size(), B.size()));
    A.resize(N), FWT::transXor(A, false);
    B.resize(N), FWT::transXor(B, false);
    for (int i = 0; i < N; i++) A[i] = 1LL * A[i] * B[i] % MOD;
    FWT::transXor(A, true);
    return A;
  }
  Vec fix(Vec A, int n) {
    A.resize(n);
    return A;
  }
  Vec der(Vec A, bool mod = true) {
    int n = A.size();
    if (n == 1) return Vec(1, 0);
    Vec D(n - 1, 0);
    for (int i = 1; i < n; i++) D[i - 1] = 1LL * i * A[i] % MOD;
    if (mod) D.resize(n);
    return D;
  }
  Vec inte(Vec A, bool mod = true) {
    int n = A.size();
    Vec I(n + 1, 0);
    for (int i = 1; i <= n; i++) I[i] = 1LL * inv(i) * A[i - 1] % MOD;
    if (mod) I.resize(n);
    return I;
  }
  Vec sqrt(Vec A) {
    int n = A.size(), N = extend(n);
    A.resize(N);
    Vec R(N, 0);
    R[0] = degree(A[0], 2, MOD);
    int i2 = inv(2);
    for (int l = 2; l <= N; l <<= 1) {
      Vec P(l), Q(l);
      std::copy(A.begin(), A.begin() + l, P.begin());
      std::copy(R.begin(), R.begin() + l, Q.begin());
      Vec I = ~Q;
      int L = l << 1;
      P.resize(L), FFT::DFT(P);
      Q.resize(L), FFT::DFT(Q);
      I.resize(L), FFT::DFT(I);
      for (int i = 0; i < L; i++) {
        Q[i] = 1LL * Q[i] * Q[i] % MOD;
        P[i] = 1LL * (P[i] + Q[i]) * i2 % MOD * I[i] % MOD;
      }
      FFT::IDFT(P), P.resize(l);
      std::copy(P.begin(), P.begin() + l, R.begin());
    }
    R.resize(n);
    return R;
  }
  Vec root(Vec A, int k) { return k == 1 ? A : k == 2 ? sqrt(A) : exp(ln(A) / k); }
  Vec ln(Vec A) {
    assert(A[0] == 1);
    int n = A.size();
    return inte(fix(der(A) * ~A, n));
  }
  Vec exp(Vec A) {
    assert(A[0] == 0);
    int n = A.size(), N = extend(n);
    A.resize(N);
    Vec E(N, 0);
    E[0] = 1;
    for (int l = 2; l <= N; l <<= 1) {
      Vec P = (-ln(fix(E, l)) + fix(A, l) + 1) * fix(E, l);
      std::copy(P.begin(), P.begin() + l, E.begin());
    }
    E.resize(n);
    return E;
  }
  Vec sin(Vec A) {
    assert(A[0] == 0);
    int i = degree(MOD - 1, 2, MOD);
    Vec E = exp(i * A);
    return (E - ~E) / (2LL * i % MOD);
  }
  Vec cos(Vec A) {
    assert(A[0] == 0);
    int i = degree(MOD - 1, 2, MOD);
    Vec E = exp(i * A);
    return (E + ~E) / 2;
  }
  Vec tan(Vec A) {
    assert(A[0] == 0);
    int n = A.size();
    return fix(sin(A) * ~cos(A), n);
  }
  Vec asin(Vec A) {
    assert(A[0] == 0);
    int n = A.size();
    return inte(fix(der(A) * ~sqrt(1 - fix(A * A, n)), n));
  }
  Vec acos(Vec A) {
    assert(A[0] == 0);
    return -asin(A);
  }
  Vec atan(Vec A) {
    assert(A[0] == 0);
    int n = A.size();
    return inte(fix(der(A) * ~(1 + fix(A * A, n)), n));
  }
  void print(Vec A, char mid = ' ') {
    int n = A.size();
    for (int i = 0; i < n; i++) { printf("%d%c", A[i], i == n - 1 ? '\n' : mid); }
  }
} // namespace Poly
