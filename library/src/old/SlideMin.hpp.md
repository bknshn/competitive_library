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


# :warning: src/old/SlideMin.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ed8431f95262b19a48e972d3753d06d7">src/old</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/old/SlideMin.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-25 17:31:02+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// 自分を含んだK個前までの中での最小値のindexの配列を返す
// 最小(最大)値のindexを返すことに注意!
template <class T = int> vector<int> slide_min(const vector<T>& a, int w, function<bool(T, T)> cmp = less<T>()) {
    int n = a.size();
    vector<int> ret(n);
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && !cmp(a[dq.back()], a[i])) {
            dq.pop_back();
        }
        dq.push_back(i);
        while (dq.front() <= i - w) {
            dq.pop_front();
        }
        ret[i] = dq.front();
    }
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/old/SlideMin.hpp"
// 自分を含んだK個前までの中での最小値のindexの配列を返す
// 最小(最大)値のindexを返すことに注意!
template <class T = int> vector<int> slide_min(const vector<T>& a, int w, function<bool(T, T)> cmp = less<T>()) {
    int n = a.size();
    vector<int> ret(n);
    deque<int> dq;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && !cmp(a[dq.back()], a[i])) {
            dq.pop_back();
        }
        dq.push_back(i);
        while (dq.front() <= i - w) {
            dq.pop_front();
        }
        ret[i] = dq.front();
    }
    return ret;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
