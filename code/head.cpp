#include <bits/stdc++.h>
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