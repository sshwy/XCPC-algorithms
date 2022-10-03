namespace NTT {
  const int N = (1 << 21) + 5, P = 998244353;
  int pw(int a, int m) {
    int res = 1;
    while (m) m & 1 ? res = 1ll * res * a % P : 0, a = 1ll * a * a % P, m >>= 1;
    return res;
  }
  int tr[N], d;
  void dft(int f[], int len, int typ) {
    FOR(i, 0, len - 1) if (i < tr[i]) swap(f[i], f[tr[i]]);
    for (int j = 1; j < len; j <<= 1) {
      int wn = pw(3, (P - 1) / (j << 1) * typ + P - 1);
      for (int i = 0; i < len; i += j << 1) {
        int w = 1, u, v;
        for (int k = i; k < i + j; k++, w = 1ll * w * wn % P) {
          u = f[k], v = 1ll * w * f[k + j] % P;
          f[k] = u + v, f[k] < P ? 0 : f[k] -= P;
          f[k + j] = u - v, f[k + j] < 0 ? f[k + j] += P : 0;
        }
      }
    }
    if (typ == -1) {
      int x = pw(len, P - 2);
      for (int i = 0; i < len; i++) f[i] = 1ll * f[i] * x % P;
    }
  }
  int init(int l) {
    d = 0;
    int len = 1;
    while (len < (l << 1)) len <<= 1, ++d;
    for (int i = 1; i < len; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1) << (d - 1);
    return len;
  }
} // namespace NTT
typedef int dft[NTT::N];
/*
 * 必须保证初始时f里的值非负！
 */
