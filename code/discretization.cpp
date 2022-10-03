namespace DC {
  int dc[N * 4], ld;
  void add(int x) { dc[++ld] = x; }
  void work() { sort(dc + 1, dc + ld + 1), ld = unique(dc + 1, dc + ld + 1) - dc - 1; }
  int tr(int x) { return lower_bound(dc + 1, dc + ld + 1, x) - dc; }
} // namespace DC
/*
 * 离散化
 */
