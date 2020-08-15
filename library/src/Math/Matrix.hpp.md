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


# :heavy_check_mark: src/Math/Matrix.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#64f6d80a21cfb0c7e1026d02dde4f7fa">src/Math</a>
* <a href="{{ site.github.repository_url }}/blob/master/src/Math/Matrix.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-06 02:12:18+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/yukicoder/1073.test.cpp.html">test/yukicoder/1073.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <class T> struct Matrix {
    std::vector<std::vector<T>> A;
    Matrix() {}
    Matrix(int n) : A(n, std::vector<T>(n, 0)) {}
    Matrix(const std::vector<std::vector<T>> &A_) : A(A_) {}
    static Matrix eye(int n) {
        Matrix mat(n);
        for (int i = 0; i < n; i++) mat[i][i] = 1;
        return mat;
    }
    int height() const { return (A.size()); }
    int width() const { return (A[0].size()); }
    std::vector<T> &operator[](int k) { return A[k]; }
    const std::vector<T> &operator[](int k) const { return (A[k]); }
    Matrix &operator+=(const Matrix &B) {
        assert(A.size() == B.A.size() && A[0].size() == B.A[0].size());
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < A[0].size(); j++) A[i][j] += B[i][j];
        return *this;
    }
    Matrix &operator-=(const Matrix &B) {
        assert(A.size() == B.A.size() && A[0].size() == B.A[0].size());
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < A[0].size(); j++) A[i][j] -= B[i][j];
        return *this;
    }
    Matrix &operator*=(const Matrix &B) {
        int n = height(), m = B.width(), p = width();
        assert(p == B.height());
        std::vector<std::vector<T>> C(n, std::vector<T>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < p; k++) C[i][j] += A[i][k] * B[k][j];
        std::swap(A, C);
        return *this;
    }
    Matrix operator+(const Matrix &B) const { return Matrix(*this) += B; }
    Matrix operator-(const Matrix &B) const { return Matrix(*this) -= B; }
    Matrix operator*(const Matrix &B) const { return Matrix(*this) *= B; }
    std::vector<T> operator*(const std::vector<T> &x) const {
        int n = height(), m = width();
        assert(m == x.size());
        std::vector<T> ret(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) ret[i] += A[i][j] * x[j];
        return ret;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "src/Math/Matrix.hpp"
template <class T> struct Matrix {
    std::vector<std::vector<T>> A;
    Matrix() {}
    Matrix(int n) : A(n, std::vector<T>(n, 0)) {}
    Matrix(const std::vector<std::vector<T>> &A_) : A(A_) {}
    static Matrix eye(int n) {
        Matrix mat(n);
        for (int i = 0; i < n; i++) mat[i][i] = 1;
        return mat;
    }
    int height() const { return (A.size()); }
    int width() const { return (A[0].size()); }
    std::vector<T> &operator[](int k) { return A[k]; }
    const std::vector<T> &operator[](int k) const { return (A[k]); }
    Matrix &operator+=(const Matrix &B) {
        assert(A.size() == B.A.size() && A[0].size() == B.A[0].size());
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < A[0].size(); j++) A[i][j] += B[i][j];
        return *this;
    }
    Matrix &operator-=(const Matrix &B) {
        assert(A.size() == B.A.size() && A[0].size() == B.A[0].size());
        for (int i = 0; i < A.size(); i++)
            for (int j = 0; j < A[0].size(); j++) A[i][j] -= B[i][j];
        return *this;
    }
    Matrix &operator*=(const Matrix &B) {
        int n = height(), m = B.width(), p = width();
        assert(p == B.height());
        std::vector<std::vector<T>> C(n, std::vector<T>(m, 0));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < p; k++) C[i][j] += A[i][k] * B[k][j];
        std::swap(A, C);
        return *this;
    }
    Matrix operator+(const Matrix &B) const { return Matrix(*this) += B; }
    Matrix operator-(const Matrix &B) const { return Matrix(*this) -= B; }
    Matrix operator*(const Matrix &B) const { return Matrix(*this) *= B; }
    std::vector<T> operator*(const std::vector<T> &x) const {
        int n = height(), m = width();
        assert(m == x.size());
        std::vector<T> ret(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) ret[i] += A[i][j] * x[j];
        return ret;
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
