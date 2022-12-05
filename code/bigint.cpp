#include "head.h"
const int W = 30, Lim = 1 << W;
template <const int Len> struct Big {
  int v[Len];
  Big() { memset(v, 0, sizeof(v)); }
  Big(int val) {
    memset(v, 0, sizeof(v));
    v[1] = val >> W, v[0] = val & (Lim - 1);
  }
  int &operator[](int i) { return v[i]; }
  bool isZero() {
    FOR(i, 0, Len - 1) if (v[i] != 0) return false;
    return true;
  }
};
template <const int Len> Big<Len> operator+(Big<Len> a, Big<Len> b) {
  Big<Len> c = a;
  FOR(i, 0, Len - 1) {
    c[i] += b[i];
    if (i + 1 < Len) c[i + 1] += c[i] >> W;
    c[i] &= Lim - 1;
  }
  return c;
}
template <const int Len> Big<Len> operator-(Big<Len> a, Big<Len> b) {
  Big<Len> c = a;
  FOR(i, 0, Len - 1) {
    c[i] -= b[i];
    if (c[i] < 0) {
      if (i + 1 < Len) c[i + 1]--, c[i] += Lim;
      else assert(0);
    } // assert(c[i] >= 0);
  }
  return c;
}
template <const int Len> Big<Len> operator*(Big<Len> a, Big<Len> b) {
  LL t[Len] = {0};
  FOR(i, 0, Len - 1) FOR(j, 0, Len - 1) {
    LL s = (LL)a[i] * b[j];
    if (i + j < Len) t[i + j] += s & (Lim - 1);
    if (i + j + 1 < Len) t[i + j + 1] += s >> W;
  }
  Big<Len> c;
  FOR(i, 0, Len - 1) {
    c[i] = t[i] & (Lim - 1);
    if (i + 1 < Len) t[i + 1] += t[i] >> W;
  }
  return c;
}
template <const int Len> int operator%(Big<Len> a, int b) {
  LL res = 0;
  ROF(i, Len - 1, 0) res = (res * Lim + a[i]) % b;
  return res;
}
template <const int Len> Big<Len> operator/(Big<Len> a, int b) {
  Big<Len> c;
  LL s = 0;
  ROF(i, Len - 1, 0) s = (s << W) + a[i], c[i] = s / b, s %= b;
  // assert(c[i] < Lim);
  return c;
}
template <const int Len> Big<Len> operator>>(Big<Len> a, unsigned m) {
  int k = m / W, r = m % W, box = (1 << r);
  if (k >= Len) return Big<Len>(0);
  Big<Len> b;
  FOR(i, k, Len - 1) b[i - k] = a[i];
  if (r == 0) return b;
  FOR(i, 0, Len - 1) {
    int high = i + 1 < Len ? (b[i + 1] & (box - 1)) << (W - r) : 0;
    b[i] = b[i] >> r | high;
  }
  return b;
}
template <const int Len> Big<Len> operator<<(Big<Len> a, unsigned m) {
  int k = m / W, r = m % W;
  if (k >= Len) return Big<Len>(0);
  Big<Len> b;
  FOR(i, k, Len - 1) b[i] = a[i - k];
  if (r == 0) return b;
  ROF(i, Len - 1, 0) {
    int low = i - 1 >= 0 ? (b[i - 1] >> (W - r)) : 0;
    b[i] = b[i] << r | low;
  }
  return b;
}
template <const int Len> int operator&(Big<Len> a, int m) { return a[0] & m; }
template <const int Len> ostream &operator<<(ostream &out, Big<Len> m) {
  vector<int> v;
  while (!m.isZero()) v.push_back(m % 10), m = m / 10;
  if (v.empty()) v.push_back(0);
  for (int i = v.size() - 1; i >= 0; i--) out << v[i];
  return out;
}
template <const int Len> istream &operator>>(istream &in, Big<Len> &m) {
  string s;
  in >> s;
  for (unsigned i = 0; i < s.size(); i++) m = m * Big<Len>(10) + Big<Len>(s[i] - '0');
  return in;
}
// typedef Big<2000 / 30 + 1> big;
