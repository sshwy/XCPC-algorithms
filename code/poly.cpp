#include "head.h"
const int N = 300010, mod = 998244353;
typedef long long LL;
int Pow(int x, int y) {
  int res = 1;
  for (; y; y >>= 1, x = (LL)x * x % mod)
    if (y & 1) res = (LL)res * x % mod;
  return res;
}

int Wn[2][17][N << 1], r[N << 2];

void Pre(int len) {
  for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++) {
    int t1 = Pow(3, (mod - 1) / mid), t2 = Pow(t1, mod - 2);
    Wn[0][step][0] = Wn[1][step][0] = 1, Wn[1][step][1] = t1, Wn[0][step][1] = t2;
    for (int i = 2; i < (mid >> 1); i++) {
      Wn[1][step][i] = (LL)Wn[1][step][i - 1] * t1 % mod;
      Wn[0][step][i] = (LL)Wn[0][step][i - 1] * t2 % mod;
    }
  }
}

void Inc(int &x, int y) { x += y, x -= x >= mod ? mod : 0; }
int Sub(int x, int y) {
  int t = x - y;
  return t < 0 ? t + mod : t;
}

void NTT(vector<int> &a, int len, int type) {
  for (int i = 0; i < len; i++)
    if (i < r[i]) swap(a[i], a[r[i]]);
  for (int mid = 2, step = 0; mid <= len; mid <<= 1, step++)
    for (int i = 0; i < len; i += mid)
      for (int j = i; j < i + (mid >> 1); j++) {
        int t = (LL)Wn[type][step][j - i] * a[j + (mid >> 1)] % mod;
        a[j + (mid >> 1)] = Sub(a[j], t), Inc(a[j], t);
      }
  if (!type)
    for (int i = 0, inv = Pow(len, mod - 2); i < len; i++) a[i] = (LL)a[i] * inv % mod;
}

void GetR(int len, int l) {
  for (int i = 1; i < len; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << l - 1);
}

vector<int> mul(vector<int> a, vector<int> b) {
  int t = a.size() + b.size() - 2, len = 1, l = 0;
  while (len <= t) len <<= 1, l++;
  GetR(len, l), a.resize(len + 1), b.resize(len + 1);
  NTT(a, len, 1), NTT(b, len, 1);
  for (int i = 0; i < len; i++) a[i] = (LL)a[i] * b[i] % mod;
  NTT(a, len, 0); // a.resize(min(n + 1, t + 1));
  return a;
}

vector<int> Inv(const vector<int> &a, int n) {
  if (n == 1) return {Pow(a[0], mod - 2)};
  vector<int> b = Inv(a, (n + 1) / 2);
  int len = 1, l = 0;
  while (len <= n * 2) len <<= 1, l++;
  GetR(len, l), b.resize(len);
  vector<int> tmp(len);
  for (int i = 0; i < n && i < a.size(); i++) tmp[i] = a[i];
  NTT(tmp, len, 1), NTT(b, len, 1);
  for (int i = 0; i < len; i++)
    b[i] = (2 - (LL)tmp[i] * b[i] % mod + mod) * b[i] % mod;
  NTT(b, len, 0), b.resize(n);
  return b;
}

int inv[N];

vector<int> Ln(const vector<int> &a, int n) {
  vector<int> a1, inva = Inv(a, n);
  for (int i = 1; i < n && i < a.size(); i++) a1.push_back((LL)a[i] * i % mod);
  a1 = mul(a1, inva), a1.resize(n);
  for (int i = n - 1; i >= 1; i--)
    a1[i] = (LL)a1[i - 1] * inv[i] % mod, assert(inv[i]);
  return a1[0] = 0, a1;
}

vector<int> Exp(const vector<int> &a, int n) {
  if (n == 1) return {1};
  vector<int> tmp = Exp(a, (n + 1) / 2), ln = Ln(tmp, n), tmp1;
  for (int i = 0; i < n; i++) tmp1.push_back((a[i] - ln[i] + mod) % mod);
  tmp1[0]++, tmp = mul(tmp, tmp1), tmp.resize(n);
  return tmp;
}