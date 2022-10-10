typedef long long LL;

LL a[N], T, n;
int pr[N], id1[N], id2[N], flag[N], g[N], sum[N], ncnt, m;

int ID(LL x) { return x <= T ? id1[x] : id2[n / x]; }
int calc(LL x) {
  return x %= mod, x * (x + 1) / 2 % mod - 1;
} // 算完全积性函数的前缀和
int f1(LL x) { return x %= mod, x * (x - 1) % mod; } // 算积性函数在质数位置的取值
int f(LL j, int c) {} // 计算 f(j)，其中 j 是某个质数的 c 次方

void init() {
  T = sqrt(n + 0.5);
  for (int i = 2; i <= T; i++) {
    if (!flag[i]) pr[++ncnt] = i, sum[ncnt] = (sum[ncnt - 1] + f1(i)) % mod;
    for (int j = 1; j <= ncnt && (LL)i * pr[j] <= T; j++) {
      flag[i * pr[j]] = 1;
      if (i % pr[j] == 0) break;
    }
  }
  for (LL l = 1; l <= n; l = n / (n / l) + 1) {
    a[++m] = n / l;
    if (a[m] <= T) id1[a[m]] = m;
    else id2[n / a[m]] = m;
    g[m] = calc(a[m]);
  }
  for (int i = 1; i <= ncnt; i++)
    for (int j = 1; j <= m && (LL)pr[i] * pr[i] <= a[j]; j++)
      g[j] =
        (g[j] - (LL)f1(pr[i]) * (g[ID(a[j] / pr[i])] - sum[i - 1]) % mod + mod) % mod;
}

int solve(LL n, int m) {
  if (n < pr[m]) return 0;
  int res = (g[ID(n)] * (LL)2 * t - (LL)sum[m - 1] * 2 * t) % mod;
  res = (res + mod) % mod;
  for (int i = m; i <= ncnt && (LL)pr[i] * pr[i] <= n; i++)
    for (LL j = pr[i], c = 1; j * pr[i] <= n; j *= pr[i], c++)
      Inc(res, ((LL)solve(n / j, i + 1) * f(j, c) + f(j * pr[i], c + 1)) % mod);
  return res;
}