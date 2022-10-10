#define double long double
typedef pair<double, double> Point;
typedef pair<double, double> Vec;
Point p[N];
double det(Vec a, Vec b) { return a.fi * b.se - a.se * b.fi; }
Vec operator-(Point a, Point b) { return {a.fi - b.fi, a.se - b.se}; }

int vis[N], s[N], tp;
void andrew() { //开头结尾是重复的
  sort(p + 1, p + n + 1);
  s[++tp] = 1;
  FOR(i, 2, n) {
    while (tp > 1 && det(p[s[tp]] - p[s[tp - 1]], p[i] - p[s[tp]]) <= 0) --tp;
    s[++tp] = i;
  }
  FOR(i, 1, tp) vis[s[i]] = 1;
  vis[1] = 0;
  int tt = tp;
  ROF(i, n, 1) if (!vis[i]) {
    while (tp > tt && det(p[s[tp]] - p[s[tp - 1]], p[i] - p[s[tp]]) <= 0) --tp;
    s[++tp] = i;
  }
  assert(s[tp] == 1 && s[1] == 1);
}
