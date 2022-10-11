#include "head.h"
const int N = 11000100;
char s[N];
int ls, L, R, d[N], ans;
int main() {
  scanf("%s", s + 1);
  ls = strlen(s + 1);
  FOR(i, 1, ls) {
    if (i < R) d[i] = min(R - i, d[L + R - i]);
    while (
      0 < i - d[i] - 1 && i + d[i] + 1 <= ls && s[i - d[i] - 1] == s[i + d[i] + 1])
      ++d[i];
    if (i + d[i] > R) L = i - d[i], R = i + d[i];
    assert(L > 0);
    ans = max(ans, d[i] * 2 + 1);
  }
  L = R = 0;
  FOR(i, 1, ls) d[i] = 0;
  FOR(i, 1, ls - 1) {
    if (i <= R) d[i] = min(R - i, d[L + R - i - 1]);
    while (0 < i - d[i] && i + d[i] + 1 <= ls && s[i - d[i]] == s[i + d[i] + 1])
      ++d[i];
    if (i + d[i] > R) L = i - d[i] + 1, R = i + d[i];
    ans = max(ans, d[i] * 2);
  }
  printf("%d", ans);
  return 0;
}
