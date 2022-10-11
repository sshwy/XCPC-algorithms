#include "head.h"
namespace BM {
  typedef long long LL;
  const int mod = 998244353;

  int Pow(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = (LL)x * x % mod)
      if (y & 1) res = (LL)res * x % mod;
    return res;
  }
  void Dec(int &x, const int &y) { x -= y, x += x < 0 ? mod : 0; }
  void Inc(int &x, const int &y) { x += y, x -= x >= mod ? mod : 0; }

  vector<int> solve(vector<int> val) {
    int cnt = 0, mn = 0;
    int n = val.size();
    vector<int> now, mncoef, ls, delta(n * 2 + 1), fail(n * 2 + 1);
    now.clear(), ls.clear(), mncoef.clear();
    for (int i = 0; i < n; i++) {
      delta[i] = val[i];
      for (int j = 0; j < ls.size(); j++)
        Dec(delta[i], (LL)val[i - j - 1] * ls[j] % mod);
      if (!delta[i]) continue;
      else fail[++cnt] = i;
      if (cnt == 1) {
        ls.clear(), ls.resize(i);
        continue;
      }
      int tmp = (LL)delta[i] * Pow(delta[fail[mn]], mod - 2) % mod;
      now.clear(), now.resize(i - fail[mn] - 1), now.push_back(tmp);
      for (int j = 0; j < mncoef.size(); j++)
        now.push_back((LL)mncoef[j] * (mod - tmp) % mod);
      if (now.size() < ls.size()) now.resize(ls.size());
      for (int j = 0; j < ls.size(); j++) Inc(now[j], ls[j]);
      if (ls.size() - i < mncoef.size() - fail[mn]) mn = cnt, mncoef = ls;
      ls = now;
    }
    return now;
  }
} // namespace BM

int main() {
  vector<int> res = BM::solve({1, 1, 3, 5, 11}); // a[i] = a[i - 1] + 2 * a[i - 2]
  for (int i = 0; i < res.size(); i++) cout << res[i] << ' ';
  // output: 1 2
}
