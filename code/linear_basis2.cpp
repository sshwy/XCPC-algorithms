#include "head.h"
LL b[70], lb;
bool insert(LL x) { //消成对角矩阵
  ROF(i, 63, 0) {
    if (!(x >> i & 1)) continue;
    if (!b[i]) {
      b[i] = x, lb++;
      ROF(j, i - 1, 0) if (b[i] >> j & 1) b[i] ^= b[j]; //消掉i的其他元
      FOR(j, i + 1, 63) if (b[j] >> i & 1) b[j] ^= b[i]; //消掉其他元的i
      return 1;
    }
    x ^= b[i];
  }
  return 0;
}