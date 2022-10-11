#include "head.h"
/// dft(f,len,typ): len 必须是 2^k
/// init(l): l 是参与运算的多项式的长度之和，返回一个2^k的长度
namespace FFT {
  const int N = (1 << 21) + 5;
  const double PI = acos(-1);
  struct cpx {
    double a, b;
    cpx(double _a = 0, double _b = 0) { a = _a, b = _b; }
    cpx operator+(cpx c) { return cpx(a + c.a, b + c.b); }
    cpx operator-(cpx c) { return cpx(a - c.a, b - c.b); }
    cpx operator*(cpx c) { return cpx(a * c.a - b * c.b, a * c.b + b * c.a); }
  };
  int tr[N], d;
  void dft(cpx f[], int len, int typ) {
    for (int i = 0; i < len; i++)
      if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int j = 1; j < len; j <<= 1) {
      cpx wn(cos(PI / j), sin(typ * PI / j));
      for (int i = 0; i < len; i += j << 1) {
        cpx w(1, 0), u, v;
        for (int k = i; k < i + j; k++, w = w * wn)
          u = f[k], v = f[k + j] * w, f[k] = u + v, f[k + j] = u - v;
      }
    }
    if (typ == -1)
      for (int i = 0; i < len; i++) f[i].a /= len;
  }
  int init(int l) {
    d = 0;
    int len = 1;
    while (len < (l << 1)) len <<= 1, d++;
    for (int i = 1; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1) << (d - 1);
    return len;
  }
} // namespace FFT
typedef FFT::cpx dft[FFT::N];