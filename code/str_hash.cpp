#include "head.h"
const int L = 1e6 + 5, HC = 2;
int bs[HC] = {29, 31}, md[HC] = {int(1e9 + 9), 998244353};
struct StringWithHash {
  char s[L];
  int ls, hs[HC][L], pm[HC][L];
  void init() {
    ls = 0;
    FOR(i, 0, HC - 1) hs[i][0] = 0, pm[i][0] = 1;
  }
  StringWithHash() { init(); }
  void extend(char c) {
    s[++ls] = c;
    FOR(i, 0, HC - 1) {
      pm[i][ls] = (LL)pm[i][ls - 1] * bs[i] % md[i];
      hs[i][ls] = ((LL)hs[i][ls - 1] * bs[i] + c) % md[i];
    }
  }
  vector<int> getHash(int l, int r) {
    vector<int> res(HC, 0);
    FOR(i, 0, HC - 1) {
      int t = (hs[i][r] - (LL)hs[i][l - 1] * pm[i][r - l + 1]) % md[i];
      res[i] = (t + md[i]) % md[i];
    }
    return res;
  }
};
