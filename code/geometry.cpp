#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>
using namespace std;
const double EPS = 1e-9;
const double Pi = acos(-1);
inline int sign(double a) { return a < EPS ? -1 : a > EPS; }
inline int cmp(double a, double b) { return sign(a - b); }
struct Point {
  double x, y;
  Point(double xx = 0, double yy = 0) { x = xx, y = yy; }
  Point operator+(Point p) { return Point(x + p.x, y + p.y); }
  Point operator-(Point p) { return Point(x - p.x, y - p.y); }
  Point operator*(double d) { return Point(x * d, y * d); }
  Point operator/(double d) { return Point(x / d, y / d); }
  bool operator<(Point p) const {
    int c = cmp(x, p.x);
    if (c) return c == -1;
    return cmp(y, p.y) == -1;
  }
  bool operator==(Point p) const { return cmp(x, p.x) == 0 && cmp(y, p.y) == 0; }
  double dot(Point p) { return x * p.x + y * p.y; }
  double det(Point p) { return x * p.y - y * p.x; }
  double abs2() { return x * x + y * y; }
  double abs() { return sqrt(abs2()); }
  double dist(Point p) { return (*this - p).abs(); }
  double alpha() { return atan2(y, x); }
  Point rot90() { return Point(-y, x); }
  Point unit() { return *this / abs(); }
  int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
  Point rot(double an) {
    return Point(x * cos(an) - y * sin(an), x * sin(an) + y * cos(an));
  }
};
struct Line {
  Point p1, p2; // p1->p2
  Line(Point q1, Point q2) { p1 = q1, p2 = q2; }
  Point &operator[](int i) { return i == 0 ? p1 : p2; }
  Point dir() { return p2 - p1; }
  bool include(Point p) { return sign((p2 - p1).det(p - p1)) >= 0; }
  Line push() // push eps outward
  {
    const double eps = 1e-7;
    Point delta = (p2 - p1).rot90().unit() * eps;
    p1 = p1 - delta, p2 = p2 - delta;
    return *this;
  }
};
bool chkLL(Point p1, Point p2, Point q1, Point q2) {
  return sign((p2 - p1).det(q2 - q1)) == 0;
}
bool chkLL(Line l1, Line l2) { return chkLL(l1[0], l1[1], l2[0], l2[1]); }
Point isLL(Point p1, Point p2, Point q1, Point q2) // qiu jiao dian
{
  double a = (q1 - p1).det(p2 - p1);
  double b = (p2 - p1).det(q2 - p1);
  return (q1 * b + q2 * a) / (a + b);
}
Point isLL(Line l1, Line l2) { return isLL(l1[0], l1[1], l2[0], l2[1]); }
bool intersect(double l1, double r1, double l2, double r2) {
  if (l1 > r1) swap(l1, r1);
  if (l2 > r2) swap(l2, r2);
  return cmp(l1, r2) >= 0 && cmp(l2, r1) >= 0;
}
bool isMiddle(double a, double m, double b) {
  return sign(a - m) == 0 || sign(b - m) == 0 || ((a > m) != (b > m));
}
bool isMiddle(Point a, Point m, Point b) {
  return isMiddle(a.x, m.x, b.x) && isMiddle(a.y, m.y, b.y);
}
bool isSS(Point p1, Point p2, Point q1, Point q2) // shi fou cun zai jiao dian
{
  if (chkLL(p1, p2, q1, q2)) return 0;
  Point p = isLL(p1, p2, q1, q2);
  if (isMiddle(p1, p, p2) && isMiddle(q1, p, q2)) return 1;
  else return 0;
}
bool onSeg(Point p1, Point p2, Point p) {
  return sign((p - p1).det(p2 - p1)) == 0 && isMiddle(p1, p, p2);
}
Point proj(Point p1, Point p2, Point q) {
  Point dir = p2 - p1;
  return p1 + dir * (dir.dot(q - p1) / dir.abs2());
}
Point reflect(Point p1, Point p2, Point q) { return proj(p1, p2, q) * 2 - q; }
double disLP(Point p1, Point p2, Point q) // dian dao zhi xian de ju li
{
  Point h = proj(p1, p2, q);
  return q.dist(h);
}
double disSP(Point p1, Point p2, Point q) // dian dao xian duan de ju li
{
  Point h = proj(p1, p2, q);
  if (isMiddle(p1, h, p2)) return q.dist(h);
  return min(q.dist(p1), q.dist(p2));
}
double disLL(Point p1, Point p2, Point q1, Point q2) // zhi xian ju li
{
  if (sign((p2 - p1).det(q2 - q1)) != 0) return 0;
  return disLP(q1, q2, p1);
}
double disSS(Point p1, Point p2, Point q1, Point q2) // xian duan ju li
{
  if (isSS(p1, p2, q1, q2)) return 0;
  return min(min(disSP(p1, p2, q1), disSP(p1, p2, q2)),
      min(disSP(q1, q2, p1), disSP(q1, q2, p2)));
}
double rad(Point p1, Point p2) // qiu jia jiao
{
  return atan2(p1.det(p2), p1.dot(p2));
}
double area(vector<Point> ps) // qiu mian ji
{
  double ret = 0;
  int n = ps.size();
  for (int i = 0; i < n; i++) ret += ps[i].det(ps[(i + 1) % n]);
  return ret / 2;
}
int contain(vector<Point> ps, Point p) // 2:insize,1:on_seg,0:outsize
{
  int n = ps.size();
  int ret = 0;
  for (int i = 0; i < n; i++) {
    Point u = ps[i], v = ps[(i + 1) % n];
    if (onSeg(u, v, p)) return 1;
    if (u.y < v.y) swap(u, v);
    if (cmp(u.y, p.y) < 0 || cmp(v.y, p.y) >= 0) continue;
    ret ^= (sign((u - p).det(v - p)) > 0);
  }
  return ret * 2;
}
int check(Point i, Point j, Point k) { return sign((j - i).det(k - i)); }
vector<Point> convexHull(vector<Point> ps) // tu bao
{
  int n = ps.size();
  if (n <= 1) return ps;
  sort(ps.begin(), ps.end());
  vector<Point> qs(n * 2);
  int k = 0;
  for (int i = 0; i < n; qs[k++] = ps[i++])
    while (k > 1 && check(qs[k - 2], qs[k - 1], ps[i]) >= 0) --k;
  for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
    while (k > t && check(qs[k - 2], qs[k - 1], ps[i]) >= 0) --k;
  qs.resize(k - 1);
  return qs;
}
double convexDiameter(vector<Point> ps) // xuan zhuan ka/qia ke
{
  int n = ps.size();
  if (n <= 1) return 0;
  int is = 0, js = 0;
  for (int i = 0; i < n; i++) {
    is = ps[i] < ps[is] ? i : is;
    js = ps[js] < ps[i] ? i : js;
  }
  int i = is, j = js;
  double ans = ps[i].dist(ps[j]);
  do {
    if ((ps[(i + 1) % n] - ps[i]).det(ps[(j + 1) % n] - ps[j]) >= 0) j = (j + 1) % n;
    else i = (i + 1) % n;
    ans = max(ans, ps[i].dist(ps[j]));
  } while (i != is || j != js);
  return ans;
}
vector<Point> convexcut(const vector<Point> &ps, Point q1, Point q2) {
  vector<Point> qs;
  int n = ps.size();
  for (int i = 0; i < n; i++) {
    Point p1 = ps[i], p2 = ps[(i + 1) % n];
    int d1 = check(q1, q2, p1), d2 = check(q1, q2, p2);
    if (d1 >= 0) qs.push_back(p1);
    if (d1 * d2 < 0) qs.push_back(isLL(p1, p2, q1, q2));
  }
  return qs;
}
bool parallel(Line l1, Line l2) { return sign(l1.dir().det(l2.dir())) == 0; }
bool sameDir(Line l1, Line l2) {
  return parallel(l1, l2) && sign(l1.dir().dot(l2.dir())) > 0;
}
bool operator<(Line l1, Line l2) {
  if (sameDir(l1, l2)) return l2.include(l1[0]);
  else return cmp(l1.dir().alpha(), l2.dir().alpha()) == -1;
}
bool check(Line u, Line v, Line w) { return v.include(isLL(u, w)); }
vector<Point> halfPlaneIS(vector<Line> &l) {
  sort(l.begin(), l.end());
  deque<Line> q;
  int n = l.size();
  for (int i = 0; i < n; i++) {
    if (i && sameDir(l[i], l[i - 1])) continue;
    while (q.size() > 1 && check(q[q.size() - 2], q[q.size() - 1], l[i])) q.pop_back();
    while (q.size() > 1 && check(l[i], q[0], q[1])) q.pop_front();
    q.push_back(l[i]);
  }
  while (q.size() > 2 && check(q[0], q[q.size() - 1], q[q.size() - 2])) q.pop_back();
  while (q.size() > 2 && check(q[q.size() - 1], q[0], q[1])) q.pop_front();
  vector<Point> ret;
  int m = q.size();
  for (int i = 0; i < m; i++) ret.push_back(isLL(q[i], q[(i + 1) % m]));
  return ret;
}
//------------------circle--------------------
int type(Point o1, double r1, Point o2, double r2) {
  double d = o1.dist(o2);
  if (cmp(d, r1 + r2) == 1) return 4;
  if (cmp(d, r1 + r2) == 0) return 3;
  if (cmp(d, abs(r1 - r2)) == 1) return 2;
  if (cmp(d, abs(r1 - r2)) == 0) return 1;
  return 0;
}
pair<Point, Point> isCL(Point o, double r, Point p1, Point p2) {
  double x = (p1 - o).dot(p2 - p1);
  double y = (p2 - p1).abs2();
  double d = x * x - y * ((p1 - o).abs2() - r * r);
  d = max(d, 0.0);
  Point m = p1 - (p2 - p1) * (x / y), dr = (p2 - p1) * (sqrt(d) / y);
  return make_pair(m - dr, m + dr);
}
pair<Point, Point> isCC(Point o1, double r1, Point o2, double r2) {
  int t = type(o1, r1, o2, r2);
  if (t == 4 || t == 0) return make_pair(Point(0, 0), Point(0, 0));
  double d = (o2 - o1).abs2();
  d = min(d, (r1 + r2) * (r1 + r2));
  double y = (r1 + r2) * (r1 - r2) + d;
  Point m = o1 + (o2 - o1).unit() * y / (2 * sqrt(d));
  double x = sqrt(r1 * r1 - y * y / (4 * d));
  Point dr = (o2 - o1).unit().rot90() * x;
  return make_pair(m - dr, m + dr);
}
pair<Point, Point> tanCP(Point o, double r, Point p) {
  double d = (p - o).abs2();
  double y = r * r / sqrt(d);
  Point m = o + (p - o).unit() * y;
  double x = sqrt(r * r - r * r * r * r / d);
  Point dr = (p - o).unit().rot90() * x;
  return make_pair(m - dr, m + dr);
}
pair<Line, Line> extanCC(Point o1, double r1, Point o2, double r2) {
  if (cmp(r1, r2) == 0) {
    Point dr = (o2 - o1).unit().rot90();
    Line l1(o1 + dr, o2 + dr);
    Line l2(o2 + dr, o1 + dr);
    return make_pair(l1, l2);
  } else {
    Point p = (o1 * r2 - o2 * r1) / (r2 - r1);
    pair<Point, Point> a = tanCP(o1, r1, p);
    pair<Point, Point> b = tanCP(o2, r2, p);
    Line l1(a.first, b.first);
    Line l2(a.second, b.second);
    return make_pair(l1, l2);
  }
}
pair<Line, Line> intanCC(Point o1, double r1, Point o2, double r2) {
  Point p = (o1 * r2 + o2 * r1) / (r1 + r2);
  pair<Point, Point> a = tanCP(o1, r1, p);
  pair<Point, Point> b = tanCP(o2, r2, p);
  Line l1(a.first, b.first);
  Line l2(a.second, b.second);
  return make_pair(l1, l2);
}
//---simpson---
double F(double x) { return x; }
double simpson(double a, double b) {
  double c = a + (b - a) / 2;
  return (F(a) + F(b) + 4 * F(c)) * (b - a) / 6;
}
double rsimpson(double a, double b, double s) {
  double c = a + (b - a) / 2;
  double l = simpson(a, c), r = simpson(c, b);
  if (sign(s - l - r) == 0) return l + r + (a - l - r) / 15;
  return rsimpson(a, c, l) + rsimpson(c, b, r);
}
//---end---
double areaCT(double r, Point p1, Point p2) {
  if (disSP(p1, p2, Point(0, 0)) > r + EPS) return r * r * rad(p1, p2) / 2;
  bool f1 = p1.abs2() < r * r + EPS, f2 = p2.abs2() < r * r + EPS;
  if (f1 && f2) return p1.det(p2);
  if (f1) {
    Point p = isCL(Point(0, 0), r, p1, p2).second;
    return p1.det(p) + r * r * rad(p, p2) / 2;
  }
  if (f2) {
    Point p = isCL(Point(0, 0), r, p1, p2).first;
    return r * r * rad(p1, p) / 2 + p.det(p2);
  }
  pair<Point, Point> p = isCL(Point(0, 0), r, p1, p2);
  return p1.det(p.first) + r * r * rad(p.first, p.second) + p.second.det(p2);
} // http://acm.hdu.edu.cn/showproblem.php?pid=5130
Point circleCenter(Point a, Point b, Point c) {
  Point p1, p2, q1, q2;
  p1 = (a + b) / 2;
  p2 = p1 + (b - a).rot90();
  q1 = (b + c) / 2;
  q2 = q1 + (b - c).rot90();
  return isLL(p1, p2, q1, q2);
}
pair<Point, double> min_circle(Point *a, int n) {
  random_shuffle(a + 1, a + n + 1);
  Point o = a[1];
  double r = 0;
  for (int i = 2; i < n; i++)
    if (a[i].dist(o) > r + EPS) {
      o = a[i];
      r = 0;
      for (int j = 1; j < i; j++)
        if (a[j].dist(o) > r + EPS) {
          o = (a[i] + a[j]) / 2;
          r = o.dist(a[i]);
          for (int k = 1; k < j; k++)
            if (a[k].dist(o) > r + EPS) {
              o = circleCenter(a[i], a[j], a[k]);
              r = o.dist(a[i]);
            }
        }
    }
  return make_pair(o, r);
}
struct Point3 {
  double x, y, z;
  Point3(double xx = 0, double yy = 0, double zz = 0) { x = xx, y = yy, z = zz; }
  Point3 operator+(Point3 p) { return Point3(x + p.x, y + p.y, z + p.z); }
  Point3 operator-(Point3 p) { return Point3(x - p.x, y - p.y, z - p.z); }
  Point3 operator*(double d) { return Point3(x * d, y * d, z * d); }
  Point3 operator/(double d) { return Point3(x / d, y / d, z / d); }
  bool operator<(Point3 p) const {
    int c = cmp(x, p.x);
    if (c) return c == -1;
    c = cmp(y, p.y);
    if (c) return c == -1;
    return cmp(z, p.z) == -1;
  }
  bool operator==(Point3 p) const {
    return cmp(x, p.x) == 0 && cmp(y, p.y) == 0 && cmp(z, p.z) == 0;
  }
  double dot(Point3 p) { return x * p.x + y * p.y + z * p.z; }
  Point3 det(Point3 p) {
    return Point3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
  }
  double abs2() { return x * x + y * y + z * z; }
  double abs() { return sqrt(abs2()); }
  double dist(Point3 p) { return (*this - p).abs(); }
  Point3 unit() { return *this / abs(); }
};
double disLP(Point3 p1, Point3 p2, Point3 q) {
  return sqrt((p2 - p1).det(q - p1).abs2() / (p2 - p1).abs2());
}
double disLL(Point3 p1, Point3 p2, Point3 q1, Point3 q2) {
  Point3 o = (p2 - p1).det(q2 - q1);
  if (o.abs() <= EPS) return disLP(p1, p2, q1);
  return fabs(o.unit().dot(p1 - p2));
}
Point3 proj(Point3 p, Point3 q, Point3 v) {
  double d2 = (p - q).det(v - q).abs2() / (v - q).abs2();
  double d = sqrt((p - q).abs2() - d2);
  return p - (v - q).unit() * d;
}
Point3 isFL(Point3 p, Point3 o, Point3 q1, Point3 q2) {
  double a = (q2 - p).dot(o), b = (q1 - p).dot(o);
  double d = a - b;
  if (sign(d) == 0) return {};
  return (q1 * a - q2 * b) / d;
}
pair<Point3, Point3> isFF(Point3 p1, Point3 o1, Point3 p2, Point3 o2) {
  Point3 e = o1.det(o2), v = o1.det(e);
  double d = o2.dot(v);
  if (fabs(d) < EPS) return {};
  Point3 q = p1 + v.dot(o2.dot(p2 - p1) / d);
  return make_pair(q, q + e);
}
/*
三维点到平面的垂足：
求点到法向量的垂线，然后把法向量按点积求出长度加到已知点上。
直线交平面：
求两点到平面的垂足，然后用相似解。
平面交平面：
1、两法向量叉积求交线的方向
2、交线和法向量求叉积得出平面上点移动的方向
3、用点积和长度算平移的距离。
$$ans=S_a+\dfrac{(S_b-S_a)v_B}{\Delta_AV_B}\Delta_A$$
异面直线之间的最短距离：
1、两直线叉积求最短距离所在直线的方向
2、确定这条直线和一条直线所在的平面。
3、求另一条直线和这个平面的交点。
球和直线的交点：
照圆和直线的交点求。
向量绕向量旋转：
求向量到轴的投影，下面只需要旋转垂线。
垂线和轴叉积实现旋转90度。
原向量和旋转90度的向量作为x和y，然后变成平面向量旋转。
平面和球的交圆：
球心投影变成圆心，勾股定理求半径。
球和球的交圆：
按平面求。
直线和球求相切的平面：
按平面求。
三个球的公切面：
两两求位似中心，然后两个位似中心连成一条直线，过直线求球的切面。
一共有8个相切平面。
*/
