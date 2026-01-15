
// Algorithms for XCPC (Typst rewrite of main.tex)

#set page(
  paper: "a4",
  margin: (left: 0.5in, right: 0.5in, top: 1in, bottom: 1in),
  footer: context align(center)[
    第 #counter(page).display() 页，共 #numbering("1", counter(page).final().at(0)) 页
  ],
)

#set text(size: 12pt)

// Number headings (clean, consistent with outline).
#set heading(numbering: "1.")

// Read a text file and render it as a code block, skipping the first line by default
// (equivalent to LaTeX lstinputlisting firstline=2).
#let code_block(
  path,
  lang: "cpp",
  firstline: 2,
  line_numbers: true,
) = {
  let src = read(path)
  let lines = src.split("\n")
  let start = calc.max(firstline - 1, 0)
  let body_lines = lines.slice(start)

  if not line_numbers {
    return raw(body_lines.join("\n"), lang: lang)
  }

  // Fallback line numbers: render two columns (line # + code text).
  let width = calc.max(2, str(body_lines.len()).len())
  table(
    columns: (auto, 1fr),
    inset: (x: 0.5em, y: 0.4em),
    stroke: luma(80%),
    // fill: luma(99%),
    [
      #text(fill: gray, font: "mononoki", size: 0.8em)[
        #body_lines.enumerate().map(((i, _)) => {
          let n = str(i + firstline)
          let pad = " " * (width - n.len())
          pad + n
        }).join("\n")
      ]
    ],
    [
      #show raw: set text(font: "mononoki")
      #raw(body_lines.join("\n"), lang: lang)
    ],
  )
}

// --- Title page (simple, clean) ---
#align(center)[
  #text(size: 24pt, weight: "bold")[Algorithms for XCPC]
  #v(0.8em)
  Sshwy
  #v(0.8em)
  #datetime.today().display()
]

#pagebreak()

// --- TOC in roman numerals ---
#set page(numbering: "i")
#outline()

#pagebreak()

// --- Main content in arabic numerals ---
#set page(numbering: "1")
#counter(page).update(1)

= 提醒事项

- 位运算会保留符号位，所以最好使用 unsigned
- 左移右移如果超过（含） 64 位会 UB
- 注意题目中对误差的描述，如果是相对误差那么输出的精度会影响正确性

= 代码头

#code_block("code/head.h")

= 字符串

== 哈希
#code_block("code/str_hash.cpp")

== KMP 算法
#code_block("code/kmp.cpp")

== Manacher 算法
#code_block("code/manacher.cpp")

== Z Function
#code_block("code/z_func.cpp")

== 后缀数组
#code_block("code/sa.cpp")

== 后缀自动机
#code_block("code/sam.cpp")

== 广义后缀自动机
#code_block("code/general_sam.cpp")

== AC 自动机
#code_block("code/ac.cpp")

== 回文自动机
#code_block("code/pam.cpp")

= 数论与线性代数

== EX-BSGS算法
#code_block("code/exbsgs.cpp")

== Pollard-Rho和Miller
#code_block("code/math.cpp")

== 线性基
#code_block("code/linear_basis2.cpp")
#code_block("code/linear_basis3.cpp")

== 杜教筛
#code_block("code/du_sieve.cpp")

== Min 25
#code_block("code/min_25.cpp")

== Min 25 杰哥
#code_block("code/min_25_jie.cpp")

== 二次剩余 Cipolla
#code_block("code/cipolla.cpp")

== 特征多项式
#code_block("code/characteristic_polynomial.cpp")

== 中国剩余定理 & exgcd
#code_block("code/crt.cpp")

== 类欧几里得算法
#code_block("code/euclideanoid.cpp")

== 自然数幂和
#code_block("code/faulhaber.cpp")

= 多项式相关

== FFT
#code_block("code/fft.cpp")

== NTT
#code_block("code/ntt.cpp")

== FWT
#code_block("code/fwt.cpp")

== 全家桶
#code_block("code/poly.cpp")

== BM 算法
#code_block("code/bm.cpp")

= 图论

== EK 费用流
#code_block("code/mcmf.cpp")

== Dinic 费用流
#code_block("code/mcmf_dinic.cpp")

== Dinic 算法求最大流
#code_block("code/dinic.cpp")

== 朱刘算法
#code_block("code/dmst.cpp")

== KM 算法
#code_block("code/km.cpp")

== Tarjan SCC
#code_block("code/tarjan_scc.cpp")

== 圆方树
#code_block("code/circle_block_tree.cpp")

== 三元环、四元环计数
#code_block("code/tri_cycle.cpp")

== 欧拉回路
#code_block("code/eular_tour.cpp")

= 数据结构

== 左偏树
#code_block("code/leftist.cpp")

== Splay
#code_block("code/splay.cpp")

== 非旋转Treap
#code_block("code/FHQ_treap.cpp")

== LCT
#code_block("code/lct.cpp")
#code_block("code/lct_jie.cpp")

== 点分治
#code_block("code/centroid_decomposition.cpp")

== 笛卡尔树
#code_block("code/cartesian_tree.cpp")

== 树链剖分
#code_block("code/heavy_light_decomposition.cpp")

== 长链剖分 & K 级祖先
#code_block("code/kth_ancestor.cpp")

== 虚树
#code_block("code/virtual_tree.cpp")

= 其他

== 单纯型
#code_block("code/simplex.cpp")

== 计算几何
#code_block("code/geometry.cpp")

== 欧拉序求LCA
#code_block("code/euler_lca.cpp")

== 保序回归
#code_block("code/isot_reg.cpp")

== IO优化
#code_block("code/io.cpp")

== Set 维护连续段
#code_block("code/set_seg.cpp")

== 高精度（二进制压位）
#code_block("code/bigint.cpp")

== 日期
#code_block("code/date.cpp")
