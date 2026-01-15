#include "head.h"
bool is_leap(int y) {
  return y % 400 == 0 || (y % 4 == 0 && y % 100);
}

bool is_valid(int y, int m, int d) {
  const static int days[] = 
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (m < 1 || m > 12) return false;
  if (d < 1 || d > days[m] + (m == 2 && is_leap(y))) return false;
  return true;
}

// Zeller's Congruence
int weekday(int y, int m, int d) {
  if (m <= 2) m += 12, y--;
  int q = d, K = y % 100, J = y / 100;
  int h = q;
  h += 13 * (m + 1) / 5;
  h += K + K / 4 + J / 4;
  h -= 2 * J;
  h = (h % 7 + 7) % 7; // h = 0 means Sat., h = 1 means Sun. ...
  return h;
}
