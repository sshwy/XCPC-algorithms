#include <algorithm>/*{{{*/
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long lld;
typedef long double lf;
typedef unsigned long long uld;
typedef pair<int, int> pii;
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define ROF(i, a, b) for (int i = (a); i >= (b); --i)
namespace RA {
  int r(int p) { return 1ll * rand() * rand() % p; }
  int r(int L, int R) { return r(R - L + 1) + L; }
} // namespace RA
namespace IO {
  char nc() {
    static char bf[100000], *p1 = bf, *p2 = bf;
    return p1 == p2 && (p2 = (p1 = bf) + fread(bf, 1, 100000, stdin), p1 == p2)
               ? EOF
               : *p1++;
  }
  int rd() {
    int res = 0;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
  }
} // namespace IO
/******************heading******************/
const int SZ = 233341;
int y, z, p, t, k;

int pw(int a, int m, int p) {
  int res = 1;
  while (m) m & 1 ? res = 1ll * res * a % p : 0, a = 1ll * a * a % p, m >>= 1;
  return res;
}
struct hash_map {
  struct data {
    int u, v, nex;
  };
  data e[SZ];
  int h[SZ], le;
  int hash(int u) { return (u % SZ + SZ) % SZ; }
  int &operator[](int u) {
    int hu = hash(u);
    for (int i = h[hu]; i; i = e[i].nex)
      if (e[i].u == u) return e[i].v;
    return e[++le] = (data){u, -1, h[hu]}, h[hu] = le, e[le].v;
  }
  void clear() { memset(h, 0, sizeof(h)), le = 0; }
} h;
int bsgs(int a, int b, int p) {
  a %= p, b %= p;
  int t = sqrt(p) + 0.5, cur = b, q = 1;
  h.clear();
  FOR(i, 0, t) h[cur] = i, cur = 1ll * cur * a % p;
  cur = pw(a, t, p);
  FOR(i, 0, t) {
    if (h[q] != -1 && i * t >= h[q]) return i * t - h[q];
    q = 1ll * q * cur % p;
  }
  return -1;
}
void solve1() {
  y %= p;
  printf("%d\n", pw(y, z, p));
}
void solve2() {
  y %= p;
  if (y == 0 && z != 0) {
    puts("Orz, I cannot find x!");
    return;
  }
  int res = 1ll * z * pw(y, p - 2, p) % p;
  if (res) printf("%d\n", res);
  else puts("Orz, I cannot find x!");
}
void solve3() {
  y %= p, z %= p;
  if (y == 0 && z == 0) {
    puts("1");
    return;
  }
  if (y == 0 && z != 0) {
    puts("Orz, I cannot find x!");
    return;
  }
  int res = bsgs(y, z, p);
  if (~res) printf("%d\n", res);
  else puts("Orz, I cannot find x!");
}
int go() {
  scanf("%d%d%d", &y, &z, &p);
  if (k == 1) solve1();
  else if (k == 2) solve2();
  else solve3();
  return 0;
}
int main() {
  scanf("%d%d", &t, &k);
  while (t--) go();
  return 0;
}
