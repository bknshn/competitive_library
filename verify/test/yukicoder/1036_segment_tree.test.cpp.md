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


# :heavy_check_mark: test/yukicoder/1036_segment_tree.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#de60e5ba474ac43bf7562c10f5977e2d">test/yukicoder</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yukicoder/1036_segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-27 22:57:41+09:00


* see: <a href="https://yukicoder.me/problems/no/1036">https://yukicoder.me/problems/no/1036</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/src/DataStructure/SegmentTree.hpp.html">src/DataStructure/SegmentTree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <bits/stdc++.h>  // clang-format off
using Int = long long;
#define REP_(i, a_, b_, a, b, ...) for (Int i = (a), lim##i = (b); i < lim##i; i++)
#define REP(i, ...) REP_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)
struct SetupIO { SetupIO() { std::cin.tie(nullptr), std::ios::sync_with_stdio(false), std::cout << std::fixed << std::setprecision(13); } } setup_io;
#ifndef _MY_DEBUG
#define dump(...)
#endif  // clang-format on

/**
 *    author:  knshnb
 *    created: Sat Apr 25 22:22:21 JST 2020
 **/

#define CALL_FROM_TEST
#include "../../src/DataStructure/SegmentTree.hpp"
#undef CALL_FROM_TEST

signed main() {
    Int n;
    std::cin >> n;
    std::vector<Int> a(n);
    REP(i, n) std::cin >> a[i];
    auto seg = make_segment_tree<Int>([](Int x, Int y) { return std::gcd(x, y); }, 0);
    seg.set_by_vector(a);
    Int ans = 0, j = 0;
    REP(i, n) {
        j = std::max(i, j);
        Int acc = seg.query(i, j);
        while (j < n && (acc = std::gcd(acc, a[j])) != 1) {
            j++;
        }
        ans += n - j;
    }
    std::cout << ans << std::endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yukicoder/1036_segment_tree.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <bits/stdc++.h>  // clang-format off
using Int = long long;
#define REP_(i, a_, b_, a, b, ...) for (Int i = (a), lim##i = (b); i < lim##i; i++)
#define REP(i, ...) REP_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)
struct SetupIO { SetupIO() { std::cin.tie(nullptr), std::ios::sync_with_stdio(false), std::cout << std::fixed << std::setprecision(13); } } setup_io;
#ifndef _MY_DEBUG
#define dump(...)
#endif  // clang-format on

/**
 *    author:  knshnb
 *    created: Sat Apr 25 22:22:21 JST 2020
 **/

#define CALL_FROM_TEST
#line 1 "src/DataStructure/SegmentTree.hpp"
/// @docs src/DataStructure/SegmentTree.md
template <class T, class F> struct SegmentTree {
    const F op;
    const T e;
    SegmentTree(F op_, T e_) : op(op_), e(e_) {}
    int n;
    std::vector<T> t;
    void set_by_identity(int n_) {
        n = n_;
        t.clear(), t.resize(2 * n, e);
    }
    void set_by_vector(const std::vector<T>& a) {
        n = a.size();
        t.clear(), t.resize(2 * n, e);
        for (int i = 0; i < n; i++) t[i + n] = a[i];
        build();
    }
    void build() {
        for (int i = n - 1; i; --i) t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    T& operator[](int i) { return t[i + n]; }
    // [l, r)
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        T resl = e, resr = e;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = op(resl, t[l++]);
            if (r & 1) resr = op(t[--r], resr);
        }
        return op(resl, resr);
    }
    // i番目をxに変更
    void update(int i, const T& x) {
        assert(0 <= i && i < n);
        t[i += n] = x;
        while (i >>= 1) t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    // i番目にxを作用 (a[i] = op(a[i], x))
    void operate(int i, const T& x) {
        assert(0 <= i && i < n);
        i += n;
        t[i] = op(t[i], x);
        while (i >>= 1) t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    friend std::string to_string(const SegmentTree<T, F>& seg) {
        return to_string(std::vector<T>(seg.t.begin() + seg.n, seg.t.end()));
    }
};
template <class T, class F> auto make_segment_tree(F op, T e) { return SegmentTree<T, F>(op, e); }
#line 19 "test/yukicoder/1036_segment_tree.test.cpp"
#undef CALL_FROM_TEST

signed main() {
    Int n;
    std::cin >> n;
    std::vector<Int> a(n);
    REP(i, n) std::cin >> a[i];
    auto seg = make_segment_tree<Int>([](Int x, Int y) { return std::gcd(x, y); }, 0);
    seg.set_by_vector(a);
    Int ans = 0, j = 0;
    REP(i, n) {
        j = std::max(i, j);
        Int acc = seg.query(i, j);
        while (j < n && (acc = std::gcd(acc, a[j])) != 1) {
            j++;
        }
        ans += n - j;
    }
    std::cout << ans << std::endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
