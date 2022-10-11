#include "head.h"
const int N = 2010;
const double eps = 1e-5;

double s[N][N], c[N];
int n, m;

void pivot(int x, int y) {
  double tmp = s[y][x];
  s[y][x] = -1;
  for (int i = 1; i <= n + 1; i++) s[y][i] /= -tmp;
  for (int i = 1; i <= m; i++)
    if (i != y) {
      tmp = s[i][x], s[i][x] = 0;
      if (-eps <= tmp && tmp <= eps) continue;
      for (int j = 1; j <= n + 1; j++) s[i][j] += s[y][j] * tmp;
    }
  tmp = c[x], c[x] = 0;
  for (int j = 1; j <= n + 1; j++) c[j] += s[y][j] * tmp;
}
double LP() {
  for (int pos = 0, cur = 0;; pivot(pos, cur), pos = cur = 0) {
    for (int i = 1; i <= n; i++)
      if (c[i] > eps) pos = i;
    if (!pos) return c[n + 1];
    double mn = 1e100;
    for (int i = 1; i <= m; i++)
      if (s[i][pos] < -eps) {
        double t = s[i][n + 1] / -s[i][pos];
        if (t < mn) mn = t, cur = i;
      }
    if (!cur) return 1e100;
  }
}

bool init() {
  while (233) {
    int r = 0, c = 0;
    for (int i = 1; i <= m; i++)
      if (s[i][n + 1] < -eps && (!r || rand() & 1)) r = i;
    if (!r) return true;
    for (int i = 1; i <= n; i++)
      if (s[r][i] > eps && (!c || rand() & 1)) c = i;
    if (!c) return false;
    pivot(c, r);
  }
}

int main() {
  n = 3, m = 2;
  c[1] = 1, c[2] = 2, c[3] = 5;
  s[1][1] = -1, s[1][2] = -1, s[1][3] = -1, s[1][4] = 5;
  s[2][1] = -2, s[2][2] = -1, s[2][3] = -4, s[2][4] = 10;
  assert(init());
  cout << LP() << endl;
  /*
      (m, n): numbers of equations and variables
      maximize x1 * 1 + x2 * 2 + x3 * 5, satisfies
      5 - 1 * x1 - 1 * x2 - 1 * x3 >= 0
      10 - 2 * x1 - 1 * x2 - 4 * x3 >= 0
      if exists i, j s[i][j] > 0, then init() is required
      output: 15 (x1 = 1, x2 = 2, x3 = 2)
  */
}
