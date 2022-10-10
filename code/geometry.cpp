/**
 * Computing Geometry Library
 * ref1: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all
 * ref2: https://darkbzoj.tk/problem/2178
 * @author Sshwy
 */
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fi first
#define se second
#define FOR(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

namespace cg {
  typedef long double Vt;
  const Vt eps = 1e-9;
  const Vt PI = 3.1415926535897932626;

  bool isZero(Vt x) { return -eps < x && x < eps; }
  bool eq(Vt x, Vt y) { return isZero(x - y); }
  bool lt(Vt x, Vt y) { return !eq(x, y) && x < y; }
  bool gt(Vt x, Vt y) { return !eq(x, y) && x > y; }

  struct Vec {
    Vt x, y;
    Vec() { x = y = 0; }
    Vec(Vt _x, Vt _y) { x = _x, y = _y; }

    Vec operator+(const Vec V) const { return Vec(x + V.x, y + V.y); }
    Vec operator-() const { return Vec(-x, -y); }
    Vec operator-(const Vec V) const { return *this + (-V); }
    Vec operator*(const Vt a) const { return Vec(x * a, y * a); }
    friend Vec operator*(const Vt a, const Vec v) { return v * a; }
    Vec operator/(const Vt a) const { return Vec(x / a, y / a); }
    operator bool() const { return !(isZero(x) && isZero(y)); }
    bool operator==(const Vec V) const { return bool(*this - V) == 0; }
    bool operator!=(const Vec V) const { return bool(*this - V) != 0; }
    bool operator<(const Vec V) const { return eq(x, V.x) ? lt(y, V.y) : lt(x, V.x); }
    bool operator>(const Vec V) const { return eq(x, V.x) ? gt(y, V.y) : gt(x, V.x); }

    Vt length() const { return sqrt(x * x + y * y); }
    // 方向角，单位 rad
    Vt ang() const { return atan2(y, x); }
    // 方向向量 @return 0向量或者一个单位向量
    Vec dir() const {
      if (*this) {
        Vt len = length();
        // Vt ang = atan2(y,x); return Vec(cos(ang), sin(ang));
        return Vec(x / len, y / len);
      } else return Vec(0, 0);
    }
  };
  typedef Vec Pt;

  // 顺时针旋转 90 度
  Vec r90_clockwise(const Vec v) { return Vec(v.y, -v.x); }

  struct Ln {
    Pt st, ed;
    Ln(Pt _p1, Pt _p2) { st = _p1, ed = _p2; }
    Ln operator+(Pt p) { return Ln(st + p, ed + p); } // shift
    Ln operator-(Pt p) { return Ln(st - p, ed - p); }
    Vec vec() const { return ed - st; }
    Vec dir() const { return vec().dir(); }
  };
  typedef Ln Seg;

  // 点积 a dot b == |a||b|cos theta
  Vt dot(const Vec a, const Vec b) { return a.x * b.x + a.y * b.y; }
  // 叉积 两个向量围成的有向面积
  Vt det(const Vec a, const Vec b) { return a.x * b.y - a.y * b.x; }
  // 向量夹角 @return 一个[0, PI) 内的数表示角度，单位 rad
  Vt angle(Vec a, Vec b) {
    if (det(a, b) < 0) swap(a, b);
    Vt res = b.ang() - a.ang();
    if (res < 0) res += 2 * PI;
    return res;
  }

  // 投影 @param L 直线  @param p 要求投影的点 @return p 在 L 上的投影坐标（即垂足）
  Pt proj(Ln L, Pt p) {
    Vec d = L.ed - L.st;
    return L.st + (dot(d, p - L.st) / d.length()) * d.dir();
  }
  // 对称点 @param L 直线 @param p 点 @return p 关于直线 L 的对称点
  Pt refl(Ln L, Pt p) { return Vt(2) * (proj(L, p) - p) + p; }
  // 判断向量是否平行
  bool parallel(Vec a, Vec b) { return isZero(det(a, b)); }
  // 判断直线是否平行
  bool parallel(Ln a, Ln b) { return parallel(a.ed - a.st, b.ed - b.st); }
  // 判断向量是否垂直
  bool orthogonal(Vec a, Vec b) { return isZero(dot(a, b)); }
  // 判断直线是否垂直
  bool orthogonal(Ln a, Ln b) { return orthogonal(a.ed - a.st, b.ed - b.st); }
  // 判断点 p 是否在直线L上
  bool on_ln(Ln L, Pt p) { return parallel(L.ed - L.st, p - L.st); }
  // 判断两直线是否重合
  bool coincident(Ln a, Ln b) { return on_ln(a, b.st) && on_ln(a, b.ed); }
  // 判断点 p 是否与有向线段共线且在反向延长线上
  bool on_ln_back(Seg sl, Pt p) {
    Vec a = sl.ed - sl.st, b = p - sl.st;
    return parallel(a, b) && lt(dot(a, b), 0);
  }
  // 判断点 p 是否与有向线段共线且在反向延长线上（含起点）
  bool on_ln_back_include(Seg sl, Pt p) {
    Vec a = sl.ed - sl.st, b = p - sl.st;
    return parallel(a, b) && !gt(dot(a, b), 0);
  }
  // 判断点 p 是否与有向线段共线且在正向延长线上
  bool on_ln_front(Seg sl, Pt p) {
    Vec a = sl.st - sl.ed, b = p - sl.ed; // 倒过来
    return parallel(a, b) && lt(dot(a, b), 0);
  }
  // 判断点 p 是否与有向线段共线且在正向延长线上（含终点）
  bool on_ln_front_include(Seg sl, Pt p) {
    Vec a = sl.st - sl.ed, b = p - sl.ed; // 倒过来
    return parallel(a, b) && !gt(dot(a, b), 0);
  }
  // 判断点 p 是否在线段上（含端点）
  bool on_seg(Seg sl, Pt p) {
    return on_ln(sl, p) && !on_ln_back(sl, p) && !on_ln_front(sl, p);
  }
  // 两条直线的交点。需确保两条直线不平行
  Pt inter(Ln a, Ln b) {
    if (parallel(a, b)) {
      printf("a: (%.2Lf, %.2Lf) -> (%.2Lf, %.2Lf), ang = %.2Lf\n", a.st.x, a.st.y,
        a.ed.x, a.ed.y, a.vec().ang());
      printf("b: (%.2Lf, %.2Lf) -> (%.2Lf, %.2Lf), ang = %.2Lf\n", b.st.x, b.st.y,
        b.ed.x, b.ed.y, b.vec().ang());
    }
    assert(!parallel(a, b));
    Vt x = det(a.st - b.st, b.ed - b.st), y = det(b.ed - b.st, a.ed - b.st);
    return a.st + (a.ed - a.st) * x / (x + y);
  }
  // 判断两个线段是否相交（含边界）
  bool check_seg_inter(Seg a, Seg b) {
    if (coincident(a, b)) {
      if (on_seg(a, b.st) || on_seg(a, b.ed) || on_seg(b, a.st) || on_seg(b, a.ed))
        return true;
      else return false;
    } else if (parallel(a, b)) {
      return false;
    } else {
      Pt o = inter(a, b);
      if (on_seg(a, o) && on_seg(b, o)) return true;
      else return false;
    }
  }
  // 两个点的距离
  Vt dst(Pt a, Pt b) { return (b - a).length(); }
  // 点到直线的距离
  Vt dst(Ln L, Pt p) { return (p - proj(L, p)).length(); }
  // 两个线段的距离
  Vt dst(Seg a, Seg b) {
    if (check_seg_inter(a, b)) return 0;
    Vt res = dst(a.st, b.st);
    res = min(res, dst(a.st, b.ed));
    res = min(res, dst(a.ed, b.st));
    res = min(res, dst(a.ed, b.ed));
    Pt o;
    if (o = proj(b, a.st), on_seg(b, o)) res = min(res, dst(a.st, o));
    if (o = proj(b, a.ed), on_seg(b, o)) res = min(res, dst(a.ed, o));
    if (o = proj(a, b.st), on_seg(a, o)) res = min(res, dst(b.st, o));
    if (o = proj(a, b.ed), on_seg(a, o)) res = min(res, dst(b.ed, o));
    return res;
  }
  // 求简单多边形面积 @param g 多边形顶点集
  Vt area(const vector<Pt> &g) {
    Vt res = 0;
    for (unsigned i = 0; i < g.size(); i++) res += det(g[i], g[(i + 1) % g.size()]);
    res /= 2;
    return abs(res);
  }
  // 判断是否是凸包 @param g 多边形顶点集
  bool is_convex(const vector<Pt> &g) {
    if (g.size() < 3) return true;
    int flag = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      int j = (i + 1) % g.size(), k = (i + 2) % g.size();
      Vt sig = det(g[j] - g[i], g[k] - g[j]);
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
  // 三个点两两之间的差向量是逆时针转动
  bool is_ctrclk(Pt a, Pt b, Pt c) { return gt(det(b - a, c - b), 0); }
  // 求凸包 @param g 多边形顶点集
  vector<Pt> convex(vector<Pt> g) {
    sort(g.begin(), g.end());
    if (g.size() < 3) return g;

    vector<bool> vis(g.size(), false);
    vector<int> s(g.size() + 1, 0);
    int ls = 0;

    for (unsigned i = 0; i < g.size(); i++) {
      while (ls > 1 && !is_ctrclk(g[s[ls - 2]], g[s[ls - 1]], g[i])) --ls;
      s[ls] = i, ++ls;
    }
    FOR(i, 0, ls - 1) vis[s[i]] = true;
    vis[0] = false;
    for (int i = g.size() - 1; i >= 0; i--)
      if (!vis[i]) {
        while (ls > 1 && !is_ctrclk(g[s[ls - 2]], g[s[ls - 1]], g[i])) --ls;
        s[ls] = i, ++ls;
      }
    assert(s[0] == s[ls - 1]);

    vector<Pt> cvx;
    FOR(i, 0, ls - 2) cvx.pb(g[s[i]]);
    return cvx;
  }
  // 求点集的最远点对距离（正确性还不太懂，也许有锅）@param v 点集
  Vt diameter(const vector<Pt> &v) {
    vector<Pt> g = convex(v);
    Vt dist = 0;
    unsigned pos = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      while (pos + 1 < g.size() && dst(g[i], g[pos]) < dst(g[i], g[pos + 1])) ++pos;
      dist = max(dist, dst(g[i], g[pos]));
    }
    return dist;
  }
  /**
   * 判断点p与多边形的包含关系
   * @param g 多边形顶点集
   * @return 0 表示在多边形外，1 表示在边上，2表示在多边形内
   */
  int polygon_pt_containment(vector<Pt> g, Pt p) {
    Ln L(Vec(p.x - 1, p.y), p); // 水平方向的射线
    int cnt = 0;
    for (unsigned i = 0; i < g.size(); i++) {
      int j = (i + 1) % g.size();
      Ln e(g[i], g[j]);
      if (on_seg(e, p)) return 1;
      if (parallel(L, e)) {
        // do nothing.
      } else if (on_ln_front(L, g[i])) {
        if (g[i].y > g[j].y) ++cnt;
      } else if (on_ln_front(L, g[j])) {
        if (g[j].y > g[i].y) ++cnt;
      } else {
        Pt o = inter(L, e);
        if (on_seg(e, o) && on_ln_front(L, o)) ++cnt;
      }
    }
    if (cnt % 2) return 2;
    return 0;
  }

  struct Cir {
    Pt o;
    Vt r;
    Cir() { r = 0; }
    Cir(Pt _o, Vt _r) { o = _o, r = _r; }
  };
  /**
   * 判断两个圆的位置关系（切线数量）
   * @param a 第一个圆
   * @param b 第二个圆
   * @return 0 表示包含，1 表示内切，2 表示相交，3 表示外切，4 表示相离
   */
  int check_cir_inter(Cir a, Cir b) {
    Vt d = dst(a.o, b.o);
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
  int check_cir_point_containment(Cir c, Pt p) {
    Vt d = dst(c.o, p);
    if (lt(d, c.r)) return 0;
    if (eq(d, c.r)) return 1;
    return 2;
  }
  // 求三角形内切圆
  Cir incircle(Pt a, Pt b, Pt c) {
    Vt r = abs(det(a - b, a - c)) / (dst(a, b) + dst(a, c) + dst(b, c));
    Ln C(a, b), B(a, c);
    Vec shiftC = (c - proj(C, c)).dir() * r;
    Vec shiftB = (b - proj(B, b)).dir() * r;
    Pt o = inter(C + shiftC, B + shiftB);
    return Cir(o, r);
  }
  // 求三角形外接圆
  Cir outcircle(Pt a, Pt b, Pt c) {
    Vec vc = r90_clockwise(a - b), vb = r90_clockwise(a - c);
    Pt mc = (a + b) / Vt(2), mb = (a + c) / Vt(2);
    Pt o = inter(Ln(mc, mc + vc), Ln(mb, mb + vb));
    Vt r = (o - a).length();
    return Cir(o, r);
  }
  // 圆点到直线的距离
  Vt dst(Ln L, Cir c) { return dst(L, c.o); }
  /**
   * 求直线和圆的交点。如果相切那么返回两个相同的点
   * 不会检查是否有交点。要求你提前判定
   * @return 一个 pair 表示两个交点
   */
  pair<Pt, Pt> cir_line_inter(Ln L, Cir c) {
    Vt d = dst(L, c);
    Vec shift = L.dir() * Vt(sqrt(max(Vt(0), c.r * c.r - d * d)));
    Pt mid = proj(L, c.o);
    return make_pair(mid - shift, mid + shift);
  }
  /**
   * 求两圆的交点。如果相切那么返回两个相同的点
   * 不会检查是否有交点。要求你提前判定
   * @return 一个 pair 表示两个交点
   */
  pair<Pt, Pt> cir_inter(Cir c1, Cir c2) {
    assert(check_cir_inter(c1, c2) > 0);
    assert(check_cir_inter(c1, c2) < 4);
    Vec oo = c2.o - c1.o, ooo = r90_clockwise(oo);
    Vt d = oo.length();
    Vt cosT = (c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d);
    Pt p = c1.r * cosT * oo.dir() + c1.o;
    Vec shift = c1.r * sqrt(1 - cosT * cosT) * ooo.dir();
    return make_pair(p + shift, p - shift);
  }
  /**
   * 求圆外或圆上一点到圆的切线。
   * 不会检查是否在圆外。要求你提前判定
   * @return 一个 pair 表示两个切点，如果是圆上的点那么返回两个相同的点
   */
  pair<Pt, Pt> cir_point_tangent(Cir c, Pt p) {
    assert(check_cir_point_containment(c, p) != 0);
    Vec op = p - c.o, oop = r90_clockwise(op);
    Vt d = op.length();
    Vt x = c.r * c.r / d;
    Pt mid = c.o + op.dir() * x;
    Vec shift = oop.dir() * sqrt(c.r * c.r - x * x);
    return make_pair(mid + shift, mid - shift);
  }
  /**
   * 两个大小不同的圆的外位似中心
   * 若这两个圆不是包含关系，那么可以理解为是两条外公切线的交点
   */
  Pt cir_outer_homothetic_center(Cir c1, Cir c2) {
    assert(!eq(c1.r, c2.r));
    if (gt(c1.r, c2.r)) swap(c1, c2);
    Pt p = (c1.o - c2.o) * c1.r / (c2.r - c1.r) + c1.o;
    return p;
  }
  /**
   * 两个大小不同的圆的内位似中心
   * 若这两个圆是相离或者外切关系，那么可以理解为是两条内公切线的交点
   */
  Pt cir_inner_homothetic_center(Cir c1, Cir c2) {
    Pt p = (c2.o - c1.o) * c1.r / (c2.r + c1.r) + c1.o;
    return p;
  }
  /**
   * 求两圆外公切线
   * 要求两圆不能是包含关系。
   * 如果是内切的话那么返回两条相同的线（指line的两个点分别相同）
   */
  pair<Ln, Ln> cir_outer_common_tangent(Cir c1, Cir c2) {
    assert(check_cir_inter(c1, c2) != 0);
    if (!eq(c1.r, c2.r)) {
      Pt p = cir_outer_homothetic_center(c1, c2);
      auto pt = cir_point_tangent(c1, p);
      if (pt.fi == pt.se) {
        Vec oo = r90_clockwise(c1.o - c2.o);
        Ln t(p + oo, p);
        return make_pair(t, t);
      } else {
        return make_pair(Ln(p, pt.fi), Ln(p, pt.se));
      }
    } else {
      Vec oo = c1.o - c2.o, ooo = r90_clockwise(oo);
      Vec shift = ooo.dir() * c1.r;
      Ln t(c2.o, c1.o);
      return make_pair(t + shift, t - shift);
    }
  }
  /**
   * 求两圆内公切线
   * 要求两圆要么相离要么外切。
   * 如果是外切的话那么返回两条相同的线（指line的两个点分别相同）
   */
  pair<Ln, Ln> cir_inner_common_tangent(Cir c1, Cir c2) {
    assert(check_cir_inter(c1, c2) >= 3);
    Pt p = cir_inner_homothetic_center(c1, c2);
    auto pt = cir_point_tangent(c1, p);
    if (pt.fi == pt.se) {
      Vec oo = r90_clockwise(c1.o - c2.o);
      Ln t(p + oo, p);
      return make_pair(t, t);
    } else {
      return make_pair(Ln(p, pt.fi), Ln(p, pt.se));
    }
  }
  // 求两圆所有公切线，去重
  vector<Ln> cir_common_tangent(Cir c1, Cir c2) {
    vector<Ln> res;
    int typ = check_cir_inter(c1, c2);
    if (typ > 0) {
      auto pt = cir_outer_common_tangent(c1, c2);
      res.pb(pt.fi);
      if (pt.fi.ed != pt.se.ed) res.pb(pt.se);
    }
    if (typ >= 3) {
      auto pt = cir_inner_common_tangent(c1, c2);
      res.pb(pt.fi);
      if (pt.fi.ed != pt.se.ed) res.pb(pt.se);
    }
    return res;
  }
  // 求弓形面积 @param r 半径 @param angle 弓形所对的圆心角，单位 rad
  Vt cir_seg_area(Vt r, Vt angle) { return r * r * (angle - sin(angle)) / Vt(2); }
  // 求两个圆交面积
  Vt cir_intertion_area(Cir c1, Cir c2) {
    Vt ans = 0;
    auto typ = check_cir_inter(c1, c2);
    if (typ <= 1) {
      ans += PI * min(c1.r, c2.r) * min(c1.r, c2.r);
    } else if (check_cir_inter(c1, c2) < 3) {
      auto pt = cir_inter(c1, c2);
      Vt t1 = angle(pt.fi - c1.o, pt.se - c1.o),
         t2 = angle(pt.fi - c2.o, pt.se - c2.o);
      Pt p = inter(Ln(c1.o, c2.o), Ln(pt.fi, pt.se));
      if (on_ln_front(Seg(c1.o, c2.o), p)) ans += cir_seg_area(c2.r, 2 * PI - t2);
      else ans += cir_seg_area(c2.r, t2);
      if (on_ln_front(Seg(c2.o, c1.o), p)) ans += cir_seg_area(c1.r, 2 * PI - t1);
      else ans += cir_seg_area(c1.r, t1);
    }
    return ans;
  }

  // p 是否在 ln 左半平面内
  bool in_left(Ln ln, Pt p) { return gt(det(ln.vec(), p - ln.st), 0); }
  bool in_left_include(Ln ln, Pt p) { return in_left(ln, p) || on_ln(ln, p); }

  // 求半平面交（直线左边的半平面）
  // 交集为空则返回空集
  // 若为开放区域返回对应的直线（这种情况还未对拍充分验证）
  // 若区域封闭，保证求出来的半平面交中直线的两个点是凸多边形上的线段端点
  vector<Ln> half_planar_inter(vector<Ln> lns) {
    vector<pair<Vt, int>> vs(lns.size()); // sort by angle
    for (unsigned i = 0; i < lns.size(); i++) vs[i] = make_pair(lns[i].vec().ang(), i);
    sort(vs.begin(), vs.end());
    for (unsigned i = 1; i < vs.size(); i++) {
      if (gt(vs[i].fi - vs[i - 1].fi, PI)) {
        FOR(j, 0, i - 1) vs[j].fi += 2 * PI;
        rotate(vs.begin(), vs.begin() + i, vs.end());
      }
    }
    vector<Vt> qA(lns.size()); // angles
    vector<Ln> qL(lns.size(), Ln(Pt(), Pt())); // lines
    vector<Pt> qP(lns.size()); // cross points
    int ql = 0, qr = -1;
    for (unsigned i = 0; i < vs.size(); i++) {
      Vt ang = vs[i].fi;
      const Ln ln = lns[vs[i].se];
      assert(ln.vec());
      // 如果交点在 ln 右边，那么这个交点对应的线是无用的
      while (ql < qr && !in_left(ln, qP[qr])) --qr;
      while (ql < qr && !in_left(ln, qP[ql + 1])) ++ql;
      if (ql <= qr && eq(ang, qA[qr])) {
        if (!in_left(ln, qL[qr].st)) --qr;
        else continue;
      }
      // 已经封闭，这条没用
      if (ql < qr && gt(qA[qr] - PI, qA[ql]) &&
        in_left_include(ln, inter(qL[ql], qL[qr])))
        continue;
      ++qr, qA[qr] = ang, qL[qr] = ln;
      if (ql < qr) qP[qr] = inter(qL[qr - 1], qL[qr]);
    }
    qP[ql] = inter(qL[ql], qL[qr]);
    // 交为空
    FOR(j, ql, qr - 1) if (!lt(qA[j + 1] - qA[j], PI)) return vector<Ln>();
    vector<Ln> res(qL.begin() + ql, qL.begin() + qr + 1);
    // 开放空间
    if (!lt(qA[ql] + PI, qA[qr])) return res;
    for (unsigned i = 0; i < res.size(); i++)
      res[i].ed = res[(i + 1) % res.size()].st = qP[ql + i];
    // for (unsigned i = 0; i < res.size(); i++) assert(res[i].vec());
    return res;
  }
} // namespace cg