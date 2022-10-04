const int N = 100;
long long p[N];
void insert(long long x) {
  ROF(i, 62, 0) {
    if (!((x >> i) & 1)) continue; //判断第i位是否为0
    if (!p[i]) {
      p[i] = x;
      break;
    } //不能张成，添加到线性基中
    x ^= p[i]; //去掉可以张成的维度（第i维消元）
  }
}
