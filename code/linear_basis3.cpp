struct basis {
  long long b[61];
  basis() { memset(b, 0, sizeof(b)); }
  bool insert(long long x) {
    ROF(i, 60, 0) {
      if (x >> i & 1) {
        if (b[i]) x ^= b[i];
        else return b[i] = x, 1;
      }
    }
    return 0;
  }
  long long qmax() {
    long long res = 0;
    ROF(i, 60, 0) if ((res ^ b[i]) > res) res ^= b[i];
    return res;
  }
  basis operator+(basis bi) {
    basis res = bi;
    FOR(i, 0, 60) if (b[i]) res.insert(b[i]);
    return res;
  }
};
/*
 * 上三角矩阵
 * 重载了合并的运算符
 */
