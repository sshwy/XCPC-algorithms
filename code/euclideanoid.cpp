#include "head.h"
/**
 * 类欧几里德算法
 * 计算 sum (0 <= i <= n) floor((a*i+b)/c)
 */
int f(int a, int b, int c, int n) {
  if (a == 0) return (b / c) * (n + 1);
  if (a < c && b < c) {
    int m = (a * n + b) / c;
    return m * n - f(c, c - b - 1, a, m - 1);
  }
  return f(a % c, b % c, c, n) + (b / c) * (n + 1) + (a / c) * (n * (n + 1) / 2);
}
