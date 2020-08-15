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


# :heavy_check_mark: test/yosupo/range_kth_smallest.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0b58406058f6619a0f31a172defc0230">test/yosupo</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/range_kth_smallest.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-15 16:14:21+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_kth_smallest">https://judge.yosupo.jp/problem/range_kth_smallest</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/src/DataStructure/WaveletMatrix.hpp.html">src/DataStructure/WaveletMatrix.hpp</a>
* :heavy_check_mark: <a href="../../../library/src/Helper/Compressor.hpp.html">src/Helper/Compressor.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>  // clang-format off
using Int = long long;
#define REP_(i, a_, b_, a, b, ...) for (Int i = (a), lim##i = (b); i < lim##i; i++)
#define REP(i, ...) REP_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)
#define ALL(v) std::begin(v), std::end(v)
struct SetupIO { SetupIO() { std::cin.tie(nullptr), std::ios::sync_with_stdio(false), std::cout << std::fixed << std::setprecision(13); } } setup_io;
#ifndef dump
#define dump(...)
#endif  // clang-format on

/**
 *    author:  knshnb
 *    created: Sat Aug  8 21:10:39 JST 2020
 **/

#define CALL_FROM_TEST
#include "../../src/DataStructure/WaveletMatrix.hpp"
#include "../../src/Helper/Compressor.hpp"
#undef CALL_FROM_TEST

signed main() {
    Compressor<int> cmp;
    Int n, Q;
    std::cin >> n >> Q;
    std::vector<int> a(n);
    REP(i, n) std::cin >> a[i], cmp.insert(a[i]);
    cmp.build();
    REP(i, n) a[i] = cmp(a[i]);
    WaveletMatrix<int, 18, std::uint64_t> wm(a);
    REP(q, Q) {
        Int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << cmp[wm.quantile(l, r, k)] << "\n";
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yosupo/range_kth_smallest.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include <bits/stdc++.h>  // clang-format off
using Int = long long;
#define REP_(i, a_, b_, a, b, ...) for (Int i = (a), lim##i = (b); i < lim##i; i++)
#define REP(i, ...) REP_(i, __VA_ARGS__, __VA_ARGS__, 0, __VA_ARGS__)
#define ALL(v) std::begin(v), std::end(v)
struct SetupIO { SetupIO() { std::cin.tie(nullptr), std::ios::sync_with_stdio(false), std::cout << std::fixed << std::setprecision(13); } } setup_io;
#ifndef dump
#define dump(...)
#endif  // clang-format on

/**
 *    author:  knshnb
 *    created: Sat Aug  8 21:10:39 JST 2020
 **/

#define CALL_FROM_TEST
#line 1 "src/DataStructure/WaveletMatrix.hpp"
int popcount(std::uint32_t x) { return __builtin_popcount(x); }
int popcount(std::uint64_t x) { return __builtin_popcountll(x); }

template <class block_type = std::uint64_t> struct BitVector {
    static constexpr size_t b = sizeof(block_type) * CHAR_BIT;  // blockのサイズ
    int n;
    std::vector<block_type> bit;
    std::vector<int> acc;
    BitVector() {}
    BitVector(int n_) : n(n_), bit(n / b + 1), acc(n / b + 1) {}
    template <bool x = 1> void set(size_t i) {
        if (x)
            bit[i / b] |= (block_type)1 << (i % b);
        else
            bit[i / b] &= ~((block_type)1 << (i % b));
    }
    void build() {
        for (int i = 0; i < (int)acc.size() - 1; i++) {
            acc[i + 1] = acc[i] + popcount(bit[i]);
        }
    }
    // [0, i)内のxの個数
    template <bool x> int rank(size_t i) {
        if (x)
            return acc[i / b] + (i % b ? popcount(bit[i / b] << (b - i % b)) : 0);
        else
            return i - rank<1>(i);
    }
    // j番目のxのindex
    template <bool x> int select(size_t j) {
        int ok = n, ng = -1;
        while (std::abs(ok - ng) > 1) {
            int mid = (ok + ng) / 2;
            (rank<x>(mid + 1) > j ? ok : ng) = mid;
        }
        return ok;
    }
};

template <class T, int maxlog = 31, class block_type = std::uint64_t> struct WaveletMatrix {
    static_assert((T(1) << (maxlog - 1)) > 0);
    using bv_type = BitVector<block_type>;
    std::array<bv_type, maxlog> bvs;      // [maxlog, n]の01行列
    std::array<int, maxlog> offset = {};  // 各列でbitが0になっている要素の数

    WaveletMatrix(const std::vector<T>& a) {
        std::vector<T> cur_data = a;
        for (int k = maxlog - 1; k >= 0; k--) {  // 上位bitから見る
            std::vector<T> zero, one;
            bvs[k] = bv_type(a.size());
            for (int i = 0; i < a.size(); i++) {
                bool bit = cur_data[i] >> k & 1;
                if (bit)
                    one.push_back(cur_data[i]), bvs[k].template set<1>(i);
                else
                    zero.push_back(cur_data[i]);
            }
            offset[k] = zero.size();
            cur_data = std::move(zero);
            cur_data.insert(cur_data.end(), one.begin(), one.end());
            bvs[k].build();
        }
    }
    // [l, r)の{x未満の個数, xの個数, xより大の個数}
    std::array<int, 3> rank_3way(int l, int r, int x) {
        int lt = 0, eq = r - l, gt = 0;
        for (int k = maxlog - 1; k >= 0; k--) {
            int prv_num = r - l;
            if (x >> k & 1) {
                l = offset[k] + bvs[k].template rank<1>(l);
                r = offset[k] + bvs[k].template rank<1>(r);
                lt += prv_num - (r - l);
            } else {
                l = bvs[k].template rank<0>(l);
                r = bvs[k].template rank<0>(r);
                gt += prv_num - (r - l);
            }
            eq -= prv_num - (r - l);
        }
        return {lt, eq, gt};
    }
    // [l, r)内の(小さい方から)j番目(0-index)の数
    int quantile(int l, int r, int j) {
        assert(j < r - l);
        T ret = 0;
        for (int k = maxlog - 1; k >= 0; k--) {
            int zl = bvs[k].template rank<0>(l);
            int zr = bvs[k].template rank<0>(r);
            if (zr - zl > j) {  // kビット目は0
                l = zl;
                r = zr;
            } else {  // kビット目は1
                l = offset[k] + (l - zl);
                r = offset[k] + (r - zr);
                ret |= (T)1 << k;
                j -= zr - zl;
            }
        }
        return ret;
    }
};
#line 1 "src/Helper/Compressor.hpp"
template <class T> struct Compressor {
    std::vector<T> val;
    void insert(T x) { val.push_back(x); }
    void insert(const std::vector<T>& v) { val.insert(val.begin(), v.begin(), v.end()); }
    void build() {
        std::sort(val.begin(), val.end());
        val.erase(std::unique(val.begin(), val.end()), val.end());
    }
    int operator()(T x) { return std::lower_bound(val.begin(), val.end(), x) - val.begin(); }
    T operator[](int idx) { return val[idx]; }
    int size() { return val.size(); }
};
#line 21 "test/yosupo/range_kth_smallest.test.cpp"
#undef CALL_FROM_TEST

signed main() {
    Compressor<int> cmp;
    Int n, Q;
    std::cin >> n >> Q;
    std::vector<int> a(n);
    REP(i, n) std::cin >> a[i], cmp.insert(a[i]);
    cmp.build();
    REP(i, n) a[i] = cmp(a[i]);
    WaveletMatrix<int, 18, std::uint64_t> wm(a);
    REP(q, Q) {
        Int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << cmp[wm.quantile(l, r, k)] << "\n";
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
