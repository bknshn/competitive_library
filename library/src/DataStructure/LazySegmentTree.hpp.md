---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: src/DataStructure/LazySegmentTree.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#e73c6b5872115ad0f2896f8e8476ef39">src/DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/DataStructure/LazySegmentTree.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-03 22:30:09+09:00




## 概要
区間更新区間取得セグメント木。

参考
- http://tsutaj.hatenablog.com/entry/2017/03/30/224339
- https://beet-aizu.hatenablog.com/entry/2017/12/01/225955

## 使い方
### 変数
- `f0(T0, T0) -> T0`: 取得クエリのモノイド
- `f1(T1, T1) -> T1`: 作用素同士のモノイド
- `g(T0, T1) -> T0`: $\mathrm{T0}$に対する$\mathrm{T1}$の作用(更新クエリ)
- `p(T1 x, int len) -> T1`: 長さ$\mathrm{len}$の区間に$x$を作用させたとき、$\mathrm{f0}$による区間合成がどう変わるか

### メソッド
- `query(int l, int r) -> T`: $\[l, r)$の範囲のモノイドの合成を返す
- `update(int l, int t, T1 x)`: $\[l, r)$の範囲に$x$を作用

## 初期化例
- `Int`に対するAdd & Max
```cpp
constexpr Int INF = 1e18;
auto seg = make_lazy_segment_tree<Int, Int>(
    [](Int x, Int y) { return max(x, y); }, -INF, [](Int x, Int y) { return x + y; }, 0,
    [](Int x, Int y) { return x == -INF ? x : x + y; }, [](Int x, int len) { return x; });
```

- `mint`に対するAffine & Sum
```cpp
auto seg = make_lazy_segment_tree<mint, pmm>(
    std::plus<mint>(), 0,
    [](pmm x, pmm y) -> pmm {
        return {x.first * y.first, x.second * y.first + y.second};
    },
    {1, 0}, [](mint x, pmm y) { return y.first * x + y.second; },
    [](pmm x, int len) -> pmm {
        return {x.first, x.second * len};
    });
```


## Verified with

* :heavy_check_mark: <a href="../../../verify/test/aoj/DSL_2_H.test.cpp.html">test/aoj/DSL_2_H.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/test/yosupo/range_affine_range_sum.test.cpp.html">test/yosupo/range_affine_range_sum.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/// @docs src/DataStructure/LazySegmentTree.md
template <class T0, class T1, class F0, class F1, class G, class P> class LazySegmentTree {
    // k番目のノードにのlazyを伝搬
    void eval(int k, int len) {
        // 定数倍高速化
        if (lazy[k] == u1) return;
        // len個分のlazy[k]を評価
        node[k] = g(node[k], p(lazy[k], len));
        if (k < N - 1) {
            // 最下段でなければ下のlazyに伝搬
            lazy[2 * k + 1] = f1(lazy[2 * k + 1], lazy[k]);
            lazy[2 * k + 2] = f1(lazy[2 * k + 2], lazy[k]);
        }
        lazy[k] = u1;
    }
    // k番目のノード[l, r)について、[a, b)の範囲内にxを作用
    void update(int a, int b, T1 x, int k, int l, int r) {
        eval(k, r - l);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[k] = f1(lazy[k], x);
            eval(k, r - l);
        } else {
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = f0(node[2 * k + 1], node[2 * k + 2]);
        }
    }
    // k番目のノード[l, r)について、[a, b)のクエリを求める
    T0 query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return u0;
        eval(k, r - l);
        if (a <= l && r <= b) return node[k];
        T0 vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T0 vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f0(vl, vr);
    }

public:
    int sz;  // 元の配列のサイズ
    int N;
    std::vector<T0> node;
    std::vector<T1> lazy;
    // T0上の演算、単位元
    const F0 f0;
    const T0 u0;
    // T1上の演算、単位元
    const F1 f1;
    const T1 u1;
    // T0に対するT1の作用
    const G g;
    // 多数のt1(T1)に対するf1の合成
    const P p;

    LazySegmentTree(F0 f0_, T0 u0_, F1 f1_, T1 u1_, G g_, P p_) : f0(f0_), u0(u0_), f1(f1_), u1(u1_), g(g_), p(p_) {}
    void set_by_vector(const std::vector<T0>& a) {
        sz = a.size();
        for (N = 1; N < sz; N *= 2)
            ;
        node.resize(2 * N - 1, u0);
        lazy.resize(2 * N - 1, u1);
        for (int i = 0; i < sz; i++) node[N - 1 + i] = a[i];
        for (int i = N - 2; i >= 0; i--) node[i] = f0(node[2 * i + 1], node[2 * i + 2]);
    }
    void set_by_unit(int n) {
        sz = n;
        for (N = 1; N < sz; N *= 2)
            ;
        node.resize(2 * N - 1, u0);
        lazy.resize(2 * N - 1, u1);
    }
    // [a, b)にxを作用
    void update(int a, int b, T1 x) {
        assert(0 <= a && a < b && b <= sz);
        update(a, b, x, 0, 0, N);
    }
    void update(int a, T1 x) { update(a, a + 1, x); }
    // [a, b)
    T0 query(int a, int b) { return query(a, b, 0, 0, N); }
    T0 query(int a) { return query(a, a + 1); }
    friend std::string to_string(LazySegmentTree<T0, T1, F0, F1, G, P>& seg) {
        for (int i = 0; i < seg.sz; i++) seg.query(i);
        return to_string(std::vector<T0>(seg.node.begin() + (seg.N - 1), seg.node.begin() + (seg.N - 1 + seg.sz)));
    }
};
template <class T0, class T1, class F0, class F1, class G, class P>
auto make_lazy_segment_tree(F0 f0, T0 u0, F1 f1, T1 u1, G g, P p) {
    return LazySegmentTree<T0, T1, F0, F1, G, P>(f0, u0, f1, u1, g, p);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/DataStructure/LazySegmentTree.hpp"
/// @docs src/DataStructure/LazySegmentTree.md
template <class T0, class T1, class F0, class F1, class G, class P> class LazySegmentTree {
    // k番目のノードにのlazyを伝搬
    void eval(int k, int len) {
        // 定数倍高速化
        if (lazy[k] == u1) return;
        // len個分のlazy[k]を評価
        node[k] = g(node[k], p(lazy[k], len));
        if (k < N - 1) {
            // 最下段でなければ下のlazyに伝搬
            lazy[2 * k + 1] = f1(lazy[2 * k + 1], lazy[k]);
            lazy[2 * k + 2] = f1(lazy[2 * k + 2], lazy[k]);
        }
        lazy[k] = u1;
    }
    // k番目のノード[l, r)について、[a, b)の範囲内にxを作用
    void update(int a, int b, T1 x, int k, int l, int r) {
        eval(k, r - l);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[k] = f1(lazy[k], x);
            eval(k, r - l);
        } else {
            update(a, b, x, 2 * k + 1, l, (l + r) / 2);
            update(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = f0(node[2 * k + 1], node[2 * k + 2]);
        }
    }
    // k番目のノード[l, r)について、[a, b)のクエリを求める
    T0 query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l) return u0;
        eval(k, r - l);
        if (a <= l && r <= b) return node[k];
        T0 vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
        T0 vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
        return f0(vl, vr);
    }

public:
    int sz;  // 元の配列のサイズ
    int N;
    std::vector<T0> node;
    std::vector<T1> lazy;
    // T0上の演算、単位元
    const F0 f0;
    const T0 u0;
    // T1上の演算、単位元
    const F1 f1;
    const T1 u1;
    // T0に対するT1の作用
    const G g;
    // 多数のt1(T1)に対するf1の合成
    const P p;

    LazySegmentTree(F0 f0_, T0 u0_, F1 f1_, T1 u1_, G g_, P p_) : f0(f0_), u0(u0_), f1(f1_), u1(u1_), g(g_), p(p_) {}
    void set_by_vector(const std::vector<T0>& a) {
        sz = a.size();
        for (N = 1; N < sz; N *= 2)
            ;
        node.resize(2 * N - 1, u0);
        lazy.resize(2 * N - 1, u1);
        for (int i = 0; i < sz; i++) node[N - 1 + i] = a[i];
        for (int i = N - 2; i >= 0; i--) node[i] = f0(node[2 * i + 1], node[2 * i + 2]);
    }
    void set_by_unit(int n) {
        sz = n;
        for (N = 1; N < sz; N *= 2)
            ;
        node.resize(2 * N - 1, u0);
        lazy.resize(2 * N - 1, u1);
    }
    // [a, b)にxを作用
    void update(int a, int b, T1 x) {
        assert(0 <= a && a < b && b <= sz);
        update(a, b, x, 0, 0, N);
    }
    void update(int a, T1 x) { update(a, a + 1, x); }
    // [a, b)
    T0 query(int a, int b) { return query(a, b, 0, 0, N); }
    T0 query(int a) { return query(a, a + 1); }
    friend std::string to_string(LazySegmentTree<T0, T1, F0, F1, G, P>& seg) {
        for (int i = 0; i < seg.sz; i++) seg.query(i);
        return to_string(std::vector<T0>(seg.node.begin() + (seg.N - 1), seg.node.begin() + (seg.N - 1 + seg.sz)));
    }
};
template <class T0, class T1, class F0, class F1, class G, class P>
auto make_lazy_segment_tree(F0 f0, T0 u0, F1 f1, T1 u1, G g, P p) {
    return LazySegmentTree<T0, T1, F0, F1, G, P>(f0, u0, f1, u1, g, p);
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
