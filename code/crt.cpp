#include "head.h"
LL mul(LL a, LL b, LL p) { // 这个函数貌似目前只支持非负整数
  if (a <= 1000000000 && b <= 1000000000) return a * b % p;
  LL res = 0;
  while (b) {
    if (b & 1) res = (res + a) % p;
    a = a * 2 % p, b >>= 1;
  }
  return res;
}
LL exgcd(LL a, LL b, LL &x, LL &y) {
  if (!b) return x = 1, y = 0, a;
  LL t = exgcd(b, a % b, y, x);
  return y = y - (a / b) * x, t;
}
// v_i(A, B): x = A (mod B)
pair<LL, LL> go(vector<pair<LL, LL>> v) {
  LL b = 0, a = 1; // x=0 mod 1
  for (auto p : v) {
    LL a1, b1, k, k1;
    a1 = p.second;
    b1 = p.first;
    LL g = exgcd(a, a1, k, k1), d = ((b1 - b) % a1 + a1) % a1;
    if (d % g) return make_pair(-1, -1);
    k = mul(k, d / g, a1);
    // 然后合并方程
    b = b + a * k, a = a / g * a1, b = (b + a) % a;
  }
  return make_pair((b + a) % a, a);
}
