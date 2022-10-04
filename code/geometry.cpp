/**
 * Computing Geometry Library
 * ref1: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all
 * ref2: https://darkbzoj.tk/problem/2178
 * @author Sshwy
 */
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define ROF(i, a, b) for (int i = (int)(a); i >= (int)(b); --i)

namespace cg {
  typedef long double vtyp;
  const vtyp eps = 1e-9;
  const vtyp PI = 3.1415926535897932626;

  bool isZero(vtyp x) { return -eps < x && x < eps; }
  bool eq(vtyp x, vtyp y) { return isZero(x - y); }
  bool neq(vtyp x, vtyp y) { return !eq(x, y); }
  bool lt(vtyp x, vtyp y) { return !eq(x, y) && x < y; }
  bool gt(vtyp x, vtyp y) { return !eq(x, y) && x > y; }
  bool le(vtyp x, vtyp y) { return eq(x, y) || x < y; }
  bool ge(vtyp x, vtyp y) { return eq(x, y) || x > y; }

  struct vec {
    vtyp x, y;
    vec() { x = y = 0; }
    vec(vtyp _x, vtyp _y) { x = _x, y = _y; }

    vec operator+(const vec V) const { return vec(x + V.x, y + V.y); }
    vec operator-() const { return vec(-x, -y); }
    vec operator-(const vec V) const { return *this + (-V); }
    vec operator*(const vtyp a) const { return vec(x * a, y * a); }
    friend vec operator*(const vtyp a, const vec v) { return v * a; }
    vec operator/(const vtyp a) const { return vec(x / a, y / a); }
    operator bool() const { return !(isZero(x) && isZero(y)); }
    bool operator==(const vec V) const { return bool(*this - V) == 0; }
    bool operator!=(const vec V) const { return bool(*this - V) != 0; }
    bool operator<(const vec V) const { return x == V.x ? y < V.y : x < V.x; }
    bool operator>(const vec V) const { return x == V.x ? y > V.y : x > V.x; }

    vtyp length() const { return sqrt(x * x + y * y); }
    /**
     * 方向角，单位 rad
     */
    vtyp ang() const { return atan2(y, x); }
    /**
     * 方向向量
     * @return 0向量或者一个单位向量
     */
    vec dir() const {
      if (*this) {
        vtyp len = length();
        // vtyp ang = atan2(y,x); return vec(cos(ang), sin(ang));
        return vec(x / len, y / len);
      } else return vec(0, 0);
    }
    // void read(){ scanf("%Lf%Lf",&x,&y); }
  };
  typedef vec point;

  vec r90_clockwise(const vec v) { // 顺时针旋转 90 度
    return vec(v.y, -v.x);
  }

  struct line {
    point p1, p2;
    line(point _p1, point _p2) { p1 = _p1, p2 = _p2; }
    line operator+(point p) { return line(p1 + p, p2 + p); } // shift
    line operator-(point p) { return line(p1 - p, p2 - p); }
    vec dir() const { return (p2 - p1).dir(); }
  };
  typedef line segment;

  istream &operator>>(istream &in, vec &v) { return in >> v.x >> v.y, in; }
  ifstream &operator>>(ifstream &in, vec &v) { return in >> v.x >> v.y, in; }
  ostream &operator<<(ostream &out, const vec &v) {
    return out << v.x << " " << v.y, out;
  }
  ofstream &operator<<(ofstream &out, const vec &v) {
    return out << v.x << " " << v.y, out;
  }
  /**
   * 点积
   * a dot b == |a||b|cos theta
   */
  vtyp dot(const vec a, const vec b) { return a.x * b.x + a.y * b.y; }
  /**
   * 叉积
   * 两个向量围成的有向面积
   */
  vtyp det(const vec a, const vec b) { return a.x * b.y - a.y * b.x; }
  /**
   * 向量夹角
   * @return 一个[0, PI) 内的数表示角度，单位 rad
   */
  vtyp angle(vec a, vec b) {
    if (det(a, b) < 0) swap(a, b);
    vtyp res = b.ang() - a.ang();
    if (res < 0) res += 2 * PI;
    return res;
  }

  /**
   * 投影
   * @param L 直线
   * @param p 要求投影的点
   * @return p 在 L 上的投影坐标（即垂足）
   */
  point projection(line L, point p) {
    vec d = L.p2 - L.p1;
    return L.p1 + (dot(d, p - L.p1) / d.length()) * d.dir();
  }
  /**
   * 对称点
   * @param L 直线
   * @param p 点
   * @return p 关于直线 L 的对称点
   */
  point reflection(line L, point p) {
    point o = projection(L, p);
    return vtyp(2) * (o - p) + p;
  }

  /**
   * 判断向量是否平行
   */
  bool parallel(vec a, vec b) { return isZero(det(a, b)); }
  /**
   * 判断直线是否平行
   */
  bool parallel(line a, line b) { return parallel(a.p2 - a.p1, b.p2 - b.p1); }
  /**
   * 判断向量是否垂直
   */
  bool orthogonal(vec a, vec b) { return isZero(dot(a, b)); }
  /**
   * 判断直线是否垂直
   */
  bool orthogonal(line a, line b) { return orthogonal(a.p2 - a.p1, b.p2 - b.p1); }
  /**
   * 判断点 p 是否在直线L上
   */
  bool online(line L, point p) { return parallel(L.p2 - L.p1, p - L.p1); }
  /**
   * 判断两直线是否重合
   */
  bool coincident(line a, line b) { return online(a, b.p1) && online(a, b.p2); }
  /**
   * 判断点 p 是否与有向线段共线且在反向延长线上
   */
  bool online_back(segment sl, point p) {
    vec a = sl.p2 - sl.p1, b = p - sl.p1;
    return parallel(a, b) && lt(dot(a, b), 0);
  }
  /**
   * 判断点 p 是否与有向线段共线且在正向延长线上
   */
  bool online_front(segment sl, point p) {
    vec a = sl.p1 - sl.p2, b = p - sl.p2; // 倒过来
    return parallel(a, b) && lt(dot(a, b), 0);
  }
  /**
   * 判断点 p 是否在线段上（含端点）
   */
  bool on_segment(segment sl, point p) {
    return online(sl, p) && !online_back(sl, p) && !online_front(sl, p);
  }
  /**
   * 两条直线的交点
   * 需确保两条直线不平行
   */
  point intersection(line a, line b) {
    assert(!parallel(a, b));
    vtyp x = det(a.p1 - b.p1, b.p2 - b.p1);
    vtyp y = det(b.p2 - b.p1, a.p2 - b.p1);
    return a.p1 + (a.p2 - a.p1) * x / (x + y);
  }
  /**
   * 判断两个线段是否相交（含边界）
   */
  bool check_segment_intersection(segment a, segment b) {
    if (cg::coincident(a, b)) {
      if (on_segment(a, b.p1) || on_segment(a, b.p2) || on_segment(b, a.p1) ||
          on_segment(b, a.p2))
        return true;
      else return false;
    } else if (cg::parallel(a, b)) {
      return false;
    } else {
      point o = cg::intersection(a, b);
      if (cg::on_segment(a, o) && cg::on_segment(b, o)) return true;
      else return false;
    }
  }
  /**
   * 两个点的距离
   */
  vtyp distance(point a, point b) { return (b - a).length(); }
  /**
   * 点到直线的距离
   */
  vtyp distance(line L, point p) { return (p - projection(L, p)).length(); }
  /**
   * 两个线段的距离
   */
  vtyp distance(segment a, segment b) {
    if (check_segment_intersection(a, b)) return 0;
    vtyp res = distance(a.p1, b.p1);
    res = min(res, distance(a.p1, b.p2));
    res = min(res, distance(a.p2, b.p1));
    res = min(res, distance(a.p2, b.p2));
    point o;
    if (o = projection(b, a.p1), on_segment(b, o)) res = min(res, distance(a.p1, o));
    if (o = projection(b, a.p2), on_segment(b, o)) res = min(res, distance(a.p2, o));
    if (o = projection(a, b.p1), on_segment(a, o)) res = min(res, distance(b.p1, o));
    if (o = projection(a, b.p2), on_segment(a, o)) res = min(res, distance(b.p2, o));
    return res;
  }
  /**
   * 求简单多边形面积
   * @param g 多边形顶点集
   */
  vtyp area(const vector<point> &g) {
    vtyp res = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      res += det(g[i], g[(i + 1) % g.size()]);
    }
    res /= 2;
    return abs(res);
  }
  /**
   * 判断是否是凸包
   * @param g 多边形顶点集
   */
  bool is_convex(const vector<point> &g) {
    if (g.size() < 3) return true;
    int flag = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      int j = (i + 1) % g.size(), k = (i + 2) % g.size();
      vtyp sig = det(g[j] - g[i], g[k] - g[j]);
      if (lt(sig, 0)) {
        if (flag == 1) return false;
        else flag = -1;
      }
      if (gt(sig, 0)) {
        if (flag == -1) return false;
        else flag = 1;
      }
    }
    return true;
  }
  /**
   * 求凸包
   * @param g 多边形顶点集
   */
  vector<point> convex(vector<point> g) {
    sort(g.begin(), g.end());
    if (g.size() < 3) return g;

    vector<bool> vis(g.size(), false);
    vector<int> s(g.size() + 1, 0);
    int ls = 0;

    for (unsigned i = 0; i < g.size(); i++) {
      while (ls > 1 && lt(det(g[s[ls - 1]] - g[s[ls - 2]], g[i] - g[s[ls - 1]]), 0))
        --ls;
      s[ls] = i, ++ls;
    }
    FOR(i, 0, ls - 1) vis[s[i]] = true;
    vis[0] = false;
    for (int i = g.size() - 1; i >= 0; i--)
      if (!vis[i]) {
        while (ls > 1 && lt(det(g[s[ls - 1]] - g[s[ls - 2]], g[i] - g[s[ls - 1]]), 0))
          --ls;
        s[ls] = i, ++ls;
      }
    assert(s[0] == s[ls - 1]);

    vector<point> cvx;
    FOR(i, 0, ls - 2) cvx.pb(g[s[i]]);
    return cvx;
  }
  /**
   * 求点集的最远点对距离（正确性还不太懂，也许有锅）
   * @param v 点集
   */
  vtyp diameter(const vector<point> &v) {
    vector<point> g = convex(v);
    vtyp dist = 0;
    unsigned pos = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      while (pos + 1 < g.size() && distance(g[i], g[pos]) < distance(g[i], g[pos + 1]))
        ++pos;
      dist = max(dist, distance(g[i], g[pos]));
    }
    return dist;
  }
  /**
   * 判断点p与多边形的包含关系
   * @param g 多边形顶点集
   * @return 0 表示在多边形外，1 表示在边上，2表示在多边形内
   */
  int polygon_point_containment(vector<point> g, point p) {
    line L(vec(p.x - 1, p.y), p); // 水平方向的射线
    int cnt = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      int j = (i + 1) % g.size();
      line e(g[i], g[j]);
      if (on_segment(e, p)) return 1;
      if (parallel(L, e)) {
        // do nothing.
      } else if (online_front(L, g[i])) {
        if (g[i].y > g[j].y) ++cnt;
      } else if (online_front(L, g[j])) {
        if (g[j].y > g[i].y) ++cnt;
      } else {
        point o = intersection(L, e);
        if (on_segment(e, o) && online_front(L, o)) ++cnt;
      }
    }
    if (cnt % 2) return 2;
    return 0;
  }

  struct circle {
    point o;
    vtyp r;
    circle() { r = 0; }
    circle(point _o, vtyp _r) { o = _o, r = _r; }
  };
  /**
   * 判断两个圆的位置关系（切线数量）
   * @param a 第一个圆
   * @param b 第二个圆
   * @return 0 表示包含，1 表示内切，2 表示相交，3 表示外切，4 表示相离
   */
  int check_circle_intersection(circle a, circle b) {
    vtyp d = distance(a.o, b.o);
    if (gt(d, a.r + b.r)) return 4;
    if (eq(d, a.r + b.r)) return 3;
    if (gt(d, abs(a.r - b.r))) return 2;
    if (eq(d, abs(a.r - b.r))) return 1;
    return 0;
  }
  /**
   * 判断圆和点的位置关系
   * @return 0 表示包含，1 表示在圆上，2 表示在圆外
   */
  int check_circle_point_containment(circle c, point p) {
    vtyp d = distance(c.o, p);
    if (lt(d, c.r)) return 0;
    if (eq(d, c.r)) return 1;
    return 2;
  }
  /**
   * 求三角形内切圆
   * @param a 三角形第一个顶点
   * @param b 三角形第二个顶点
   * @param c 三角形第三个顶点
   * @return 一个 circle 表示内切圆
   */
  circle incircle(point a, point b, point c) {
    vtyp r =
        abs(det(a - b, a - c)) / (distance(a, b) + distance(a, c) + distance(b, c));
    line C(a, b), B(a, c);
    vec shiftC = (c - projection(C, c)).dir() * r;
    vec shiftB = (b - projection(B, b)).dir() * r;
    point o = intersection(C + shiftC, B + shiftB);
    return circle(o, r);
  }
  /**
   * 求三角形外接圆
   * @param a 三角形第一个顶点
   * @param b 三角形第二个顶点
   * @param c 三角形第三个顶点
   * @return 一个 circle 表示外接圆
   */
  circle outcircle(point a, point b, point c) {
    vec vc = r90_clockwise(a - b), vb = r90_clockwise(a - c);
    point mc = (a + b) / vtyp(2), mb = (a + c) / vtyp(2);
    point o = intersection(line(mc, mc + vc), line(mb, mb + vb));
    vtyp r = (o - a).length();
    return circle(o, r);
  }
  /**
   * 圆点到直线的距离
   */
  vtyp distance(line L, circle c) { return distance(L, c.o); }
  /**
   * 求直线和圆的交点。如果相切那么返回两个相同的点
   * 不会检查是否有交点。要求你提前判定
   * @return 一个 pair 表示两个交点
   */
  pair<point, point> circle_line_intersection(line L, circle c) {
    vtyp d = distance(L, c);
    d = sqrt(max(vtyp(0), c.r * c.r - d * d));
    vec shift = L.dir() * d;
    point mid = projection(L, c.o);
    return make_pair(mid - shift, mid + shift);
  }
  /**
   * 求两圆的交点。如果相切那么返回两个相同的点
   * 不会检查是否有交点。要求你提前判定
   * @return 一个 pair 表示两个交点
   */
  pair<point, point> circle_intersection(circle c1, circle c2) {
    assert(check_circle_intersection(c1, c2) > 0);
    assert(check_circle_intersection(c1, c2) < 4);
    vec oo = c2.o - c1.o, ooo = r90_clockwise(oo);
    vtyp d = oo.length();
    vtyp cosT = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d);
    point p = c1.r * cosT * oo.dir() + c1.o;
    vec shift = c1.r * sqrt(1 - cosT * cosT) * ooo.dir();
    return make_pair(p + shift, p - shift);
  }
  /**
   * 求圆外或圆上一点到圆的切线。
   * 不会检查是否在圆外。要求你提前判定
   * @return 一个 pair 表示两个切点，如果是圆上的点那么返回两个相同的点
   */
  pair<point, point> circle_point_tangent(circle c, point p) {
    assert(check_circle_point_containment(c, p) != 0);
    vec op = p - c.o, oop = r90_clockwise(op);
    vtyp d = op.length();
    vtyp x = c.r * c.r / d;
    point mid = c.o + op.dir() * x;
    vec shift = oop.dir() * sqrt(c.r * c.r - x * x);
    return make_pair(mid + shift, mid - shift);
  }
  /**
   * 两个大小不同的圆的外位似中心
   * 若这两个圆不是包含关系，那么可以理解为是两条外公切线的交点
   */
  point circle_outer_homothetic_center(circle c1, circle c2) {
    assert(neq(c1.r, c2.r));
    if (gt(c1.r, c2.r)) swap(c1, c2);
    point p = (c1.o - c2.o) * c1.r / (c2.r - c1.r) + c1.o;
    return p;
  }
  /**
   * 两个大小不同的圆的内位似中心
   * 若这两个圆是相离或者外切关系，那么可以理解为是两条内公切线的交点
   */
  point circle_inner_homothetic_center(circle c1, circle c2) {
    point p = (c2.o - c1.o) * c1.r / (c2.r + c1.r) + c1.o;
    return p;
  }
  /**
   * 求两圆外公切线
   * 要求两圆不能是包含关系。
   * 如果是内切的话那么返回两条相同的线（指line的两个点分别相同）
   */
  pair<line, line> circle_outer_common_tangent(circle c1, circle c2) {
    assert(check_circle_intersection(c1, c2) != 0);
    if (neq(c1.r, c2.r)) {
      point p = circle_outer_homothetic_center(c1, c2);
      auto pt = circle_point_tangent(c1, p);
      if (pt.first == pt.second) {
        vec oo = r90_clockwise(c1.o - c2.o);
        line t(p + oo, p);
        return make_pair(t, t);
      } else {
        return make_pair(line(p, pt.first), line(p, pt.second));
      }
    } else {
      vec oo = c1.o - c2.o, ooo = r90_clockwise(oo);
      vec shift = ooo.dir() * c1.r;
      line t(c2.o, c1.o);
      return make_pair(t + shift, t - shift);
    }
  }
  /**
   * 求两圆内公切线
   * 要求两圆要么相离要么外切。
   * 如果是外切的话那么返回两条相同的线（指line的两个点分别相同）
   */
  pair<line, line> circle_inner_common_tangent(circle c1, circle c2) {
    assert(check_circle_intersection(c1, c2) >= 3);
    point p = circle_inner_homothetic_center(c1, c2);
    auto pt = circle_point_tangent(c1, p);
    if (pt.first == pt.second) {
      vec oo = r90_clockwise(c1.o - c2.o);
      line t(p + oo, p);
      return make_pair(t, t);
    } else {
      return make_pair(line(p, pt.first), line(p, pt.second));
    }
  }
  /**
   * 求两圆所有公切线，去重
   */
  vector<line> circle_common_tangent(circle c1, circle c2) {
    vector<line> res;
    int typ = check_circle_intersection(c1, c2);
    if (typ > 0) {
      auto pt = circle_outer_common_tangent(c1, c2);
      res.pb(pt.first);
      if (pt.first.p2 != pt.second.p2) res.pb(pt.second);
    }
    if (typ >= 3) {
      auto pt = circle_inner_common_tangent(c1, c2);
      res.pb(pt.first);
      if (pt.first.p2 != pt.second.p2) res.pb(pt.second);
    }
    return res;
  }
  /**
   * 求弓形面积
   * @param r 半径
   * @param angle 弓形所对的圆心角，单位 rad
   */
  vtyp circular_segment_area(vtyp r, vtyp angle) {
    return r * r * (angle - sin(angle)) / vtyp(2);
  }
  /**
   * 求两个圆交面积
   */
  vtyp circle_intersection_area(circle c1, circle c2) {
    vtyp ans = 0;
    auto typ = check_circle_intersection(c1, c2);
    if (typ <= 1) {
      ans += PI * min(c1.r, c2.r) * min(c1.r, c2.r);
    } else if (check_circle_intersection(c1, c2) < 3) {
      auto pt = circle_intersection(c1, c2);
      auto t1 = angle(pt.first - c1.o, pt.second - c1.o);
      auto t2 = angle(pt.first - c2.o, pt.second - c2.o);
      point p = intersection(line(c1.o, c2.o), line(pt.first, pt.second));
      if (online_front(segment(c1.o, c2.o), p)) {
        ans += circular_segment_area(c2.r, 2 * PI - t2);
      } else {
        ans += circular_segment_area(c2.r, t2);
      }
      if (online_front(segment(c2.o, c1.o), p)) {
        ans += circular_segment_area(c1.r, 2 * PI - t1);
      } else {
        ans += circular_segment_area(c1.r, t1);
      }
    }
    return ans;
  }
} // namespace cg
using cg::circle;
using cg::line;
using cg::point;
using cg::segment;

// int main(){
//   circle c1, c2;
//   cin >> c1.o >> c1.r >> c2.o >> c2.r;
//   auto ans = cg::circle_intersection_area(c1, c2);
//   cout << setiosflags(ios::fixed) << setprecision(9) << ans << endl;
//   return 0;
// }
