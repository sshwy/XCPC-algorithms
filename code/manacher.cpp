#include "head.h"
// odd[i]: [i - odd[i], i + odd[i]]
// even[i]: [i - even[i] + 1, i + even[i]]
pair<vector<int>, vector<int>> manacher(string s) {
  assert(s.size());
  vector<int> v(s.size() * 2), d(v.size()), odd(s.size()), even(s.size() - 1);
  for_each(i, s) v[i * 2] = s[i], v[i * 2 + 1] = -1;
  int L = 0, R = 0;
  for_each(i, v) {
    if (i < R) d[i] = min(R - i, d[L + R - i]);
    while (i > d[i] && i + d[i] + 1 < v.size() && v[i - d[i] - 1] == v[i + d[i] + 1])
      ++d[i];
    if (i + d[i] > R) L = i - d[i], R = i + d[i];
  }
  for_each(i, odd) odd[i] = d[i * 2] / 2;
  for_each(i, even) even[i] = (d[i * 2 + 1] + 1) / 2;
  return make_pair(odd, even);
}