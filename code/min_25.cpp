#include "head.h"
typedef long long LL;
/**
 * Min_25 筛
 *
 * ref: https://notes.sshwy.name/Math/Min_25/
 *
 * N: 要筛的值的上界
 * CNT: f1 的项数
 * COEF[CNT]: f1 对应的系数。const 指定义为全局变量数组（里面的元素可改）
 * ef1: 计算 f1 的点值。第一个参数是点，第二个参数是要存储的数组
 * esf1: 计算 f1 前缀和的点值
 * f_pe: 计算 f 在质数幂处的值
 * MOD: 模数
 */
// Usage (https://www.luogu.com.cn/problem/P5325):
const LL N = 1e10;
const int P = 1e9 + 7, I6 = (P + 1) / 6, I2 = (P + 1) / 2;

int coef[] = {P - 1, 1};

void f1(LL x, int *result) {
  x %= P;
  result[0] = x % P;
  result[1] = x * 1ll * x % P;
}
void prefixSumF1(LL x, int *result) {
  x %= P;
  result[0] = x * (x + 1) % P * I2 % P;
  result[1] = x * (x + 1) % P * (x * 2 + 1) % P * I6 % P;
}
int f_pe(int p, int e, LL pe) {
  pe %= P;
  return 1ll * pe * (pe - 1) % P;
}

int main() {
  long long n;
  scanf("%lld", &n);

  Min25<N, 2, coef, f1, prefixSumF1, f_pe, P> Sieve;
  int ans = Sieve.sieve(n);

  printf("%d\n", ans);
  return 0;
}
// Min_25
template <const LL N, const int CNT, const int COEF[CNT], void (*ef1)(LL, int *),
  void (*esf1)(LL, int *), int (*f_pe)(int, int, LL), const int MOD>
struct Min25 {
  vector<vector<int>> g, h, hs;
  vector<int> id[2], pn;
  vector<LL> val;
  LL n;
  int SQRT_N, sqrt_n, tot, lp;

  Min25() {
    SQRT_N = 2 * (sqrt(N) + 5);
    tot = lp = 0;
    g.resize(SQRT_N, vector<int>(CNT, 0));
    h.resize(SQRT_N, vector<int>(CNT, 0));
    hs.resize(SQRT_N, vector<int>(CNT, 0));
    id[0].resize(SQRT_N, 0), id[1].resize(SQRT_N, 0);
    val.resize(SQRT_N, 0), pn.resize(SQRT_N, 0);
  }
  // Min_25
  void init() {
    sqrt_n = sqrt(n) + 3;
    vector<bool> co(SQRT_N, false);
    co[0] = co[1] = 1;
    for (int i = 2; i <= sqrt_n; i++) {
      if (!co[i]) pn[++lp] = i;
      for (int j = 1; j <= lp && 1ll * i * pn[j] <= sqrt_n; j++) {
        co[i * pn[j]] = 1;
        if (i % pn[j] == 0) break;
      }
    }
    for (LL pos = 1, nex, w; pos <= n; pos = nex + 1) {
      nex = n / (n / pos), w = n / pos, val[++tot] = w;
      w <= sqrt_n ? id[0][w] = tot : id[1][n / w] = tot;
    } // FOR(i, 1, tot) assert(I(val[i]) == i);
  }
  void calc_h() {
    int tmp[CNT];
    FOR(i, 1, lp) {
      ef1(pn[i], tmp);
      FOR(j, 0, CNT - 1) {
        h[i][j] = tmp[j];
        hs[i][j] = (hs[i - 1][j] + tmp[j]) % MOD;
      }
    }
  }
  int H(int i) { // 计算 sum_j f(p_j) (j <= i） // assert(i <= lp);
    int res = 0;
    FOR(j, 0, CNT - 1) res = (res + 1ll * hs[i][j] * COEF[j]) % MOD;
    return res;
  }
  int I(LL x) { return x <= sqrt_n ? id[0][x] : id[1][n / x]; }
  void calc_g() {
    FOR(i, 1, tot) { //当i=0
      int tmp[CNT];
      esf1(val[i], tmp);
      FOR(j, 0, CNT - 1) {
        g[i][j] = (tmp[j] - 1 + MOD) % MOD; // 对于积性函数来说必然有 f(1) = 1
      }
    }
    FOR(i, 1, lp) FOR(j, 1, tot) { // pn[i]
      if (1ll * pn[i] * pn[i] > val[j]) break;
      int k = I(val[j] / pn[i]);
      FOR(t, 0, CNT - 1) {
        g[j][t] = (g[j][t] - (LL)h[i][t] * (g[k][t] - hs[i - 1][t]) % MOD + MOD) % MOD;
      }
    }
  }
  int G(LL x) { // 计算 sum f(p) (p <= x 且 p 是质数）
    int res = 0;
    FOR(i, 0, CNT - 1) res = (res + (LL)g[I(x)][i] * COEF[i]) % MOD;
    return res;
  }
  int S(int i, LL m) {
    if (m < pn[i] || m <= 1) return 0;
    LL res = (G(m) - H(i - 1) + MOD) % MOD;
    FOR(j, i, lp) {
      if (1ll * pn[j] * pn[j] > m) break;
      LL pje = 1, pje1 = pn[j];
      FOR(e, 1, 100) {
        pje *= pn[j], pje1 *= pn[j];
        if (pje1 > m) break;
        res +=
          (LL)f_pe(pn[j], e, pje) * S(j + 1, m / pje) % MOD + f_pe(pn[j], e + 1, pje1);
        res = (res % MOD + MOD) % MOD;
      }
    }
    return res;
  }

  int sieve(LL _n) {
    n = _n, init(), calc_h(), calc_g();
    return (S(1, n) + 1) % MOD;
  }
};
