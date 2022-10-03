/******************heading******************/
const int N = 100;
int n;
lld p[N];
void insert(lld x) {
  ROF(i, 62, 0) {
    if (!((x >> i) & 1)) continue; //判断第i位是否为0
    if (!p[i]) {
      p[i] = x;
      break;
    } //不能张成，添加到线性基中
    x ^= p[i]; //去掉可以张成的维度（第i维消元）
  }
}
int main() {
  scanf("%d", &n);
  FOR(i, 1, n) {
    lld x;
    scanf("%lld", &x);
    insert(x);
  }
  lld ans = 0;
  ROF(i, 62, 0) {
    if (!((ans >> i) & 1)) ans ^= p[i];
  }
  printf("%lld", ans);
  return 0;
}
