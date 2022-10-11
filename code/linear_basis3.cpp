#include "head.h"
struct Basis {
  LL b[61];
  Basis() { memset(b, 0, sizeof(b)); }
  bool insert(LL x) {
    ROF(i, 60, 0) if (x >> i & 1) {
      if (b[i]) x ^= b[i];
      else return b[i] = x, 1;
    }
    return 0;
  }
  LL qmax() {
    LL res = 0;
    ROF(i, 60, 0) if ((res ^ b[i]) > res) res ^= b[i];
    return res;
  }
  Basis operator+(Basis bi) {
    Basis res = bi;
    FOR(i, 0, 60) if (b[i]) res.insert(b[i]);
    return res;
  }
};
/*
 * 上三角矩阵
 * 重载了合并的运算符
 */
