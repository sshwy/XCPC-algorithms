#include "head.h"
struct Interval {
  int l, r, w, t; // a[l..r] = w, assigned time
  bool operator<(Interval a) const { return l < a.l; }
};
set<Interval> s;

void mergeInterval(Interval cur, int t) { // [cur.l, cur.r] 是我们要合并的区间
  auto st = s.upper_bound({cur.l}); // 因为 l 是 struct 里第一个参数所以这里可以这么写
  --st;
  auto ed = s.upper_bound({cur.r});
  vector<Interval> v(st, ed); // 拿出所有与之相交的区间
  s.erase(st, ed);
  auto &vst = v[0], &ved = v[v.size() - 1];
  if (vst.l < cur.l) { // 把不在 [cur.l, cur.r] 里的区间塞回去
    s.insert({vst.l, cur.l - 1, vst.w, vst.t});
    vst.l = cur.l;
  }
  if (cur.r < ved.r) { // 把不在 [cur.l, cur.r] 里的区间塞回去
    s.insert({cur.r + 1, ved.r, ved.w, ved.t});
    ved.r = cur.r;
  }
  for (auto i : v) { // 处理被删掉的区间
    // do something about i
  }
  s.insert({cur.l, cur.r, cur.w, t}); // 插入 [cur.l, cur.r]
}
