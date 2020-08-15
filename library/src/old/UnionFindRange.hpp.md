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


# :warning: src/old/UnionFindRange.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ed8431f95262b19a48e972d3753d06d7">src/old</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/old/UnionFindRange.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-25 17:53:12+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 1次元上の要素のマージをしていくときに、各連結成分の[left, right)を更新
struct UnionFind {
    int cnt;                      // 集合の数
    vector<int> number;           // 0以上のとき親のindex, 負のときは集合サイズ
    vector<pair<int, int>> data;  // [left, right)
    UnionFind(int n) : cnt(n), number(n, -1), data(n) {
        for (int i = 0; i < n; i++) data[i] = {i, i + 1};
    }
    int root(int x) { return number[x] < 0 ? x : number[x] = root(number[x]); }
    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (number[y] < number[x]) swap(x, y);
        // yをxにマージ
        number[x] += number[y];
        number[y] = x;
        // dataのマージ方法に合わせて変える
        data[x] = {min(data[x].first, data[y].first), max(data[x].second, data[y].second)};
        cnt--;
    }
    bool is_same(int x, int y) { return root(x) == root(y); }
    int size(int x) { return -number[root(x)]; }
    int& left(int x) { return data[root(x)].first; }
    int& right(int x) { return data[root(x)].second; }
    pair<int, int>& ref(int x) { return data[root(x)]; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/old/UnionFindRange.hpp"
// 1次元上の要素のマージをしていくときに、各連結成分の[left, right)を更新
struct UnionFind {
    int cnt;                      // 集合の数
    vector<int> number;           // 0以上のとき親のindex, 負のときは集合サイズ
    vector<pair<int, int>> data;  // [left, right)
    UnionFind(int n) : cnt(n), number(n, -1), data(n) {
        for (int i = 0; i < n; i++) data[i] = {i, i + 1};
    }
    int root(int x) { return number[x] < 0 ? x : number[x] = root(number[x]); }
    void unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (number[y] < number[x]) swap(x, y);
        // yをxにマージ
        number[x] += number[y];
        number[y] = x;
        // dataのマージ方法に合わせて変える
        data[x] = {min(data[x].first, data[y].first), max(data[x].second, data[y].second)};
        cnt--;
    }
    bool is_same(int x, int y) { return root(x) == root(y); }
    int size(int x) { return -number[root(x)]; }
    int& left(int x) { return data[root(x)].first; }
    int& right(int x) { return data[root(x)].second; }
    pair<int, int>& ref(int x) { return data[root(x)]; }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
