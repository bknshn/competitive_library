/// @docs src/Graph/TwoEdgeConnectedComponents.md
struct TwoEdgeConnectedComponents {
    int n;
    std::vector<std::vector<int>> g;
    std::vector<std::pair<int, int>> bridges;  // 列挙された橋
    std::vector<int> belong_to;                // 各頂点の属する二重辺連結成分のindex
    int size = -1;                             // 二重辺連結成分の個数

    TwoEdgeConnectedComponents(int n_) : n(n_), g(n_) {}
    TwoEdgeConnectedComponents(const std::vector<std::vector<int>>& g_) : n(g_.size()), g(g_) {}
    void build() {
        // dfs木を作り、各辺が後退辺にはさまれているかどうかをimos法で判定
        std::vector<int> imos(n);  // imos[i] == 0なら(i, par)が橋になるように更新
        std::vector<int> flag(n);  // 0: unvisited, 1: ancestor of current v, 2: done(後退辺になりえない)
        auto dfs1 = [&](auto f, int v, int prv) -> void {
            flag[v] = 1;
            bool skipped_parent = false;
            for (int s : g[v]) {
                if (s == prv && !skipped_parent) {  // 多重辺に対応
                    skipped_parent = true;
                    continue;
                }
                if (flag[s] == 0) {
                    f(f, s, v);
                    if (imos[s] == 0) bridges.push_back({v, s});
                    imos[v] += imos[s];
                } else if (flag[s] == 1) {  // 後退辺
                    imos[v]++;
                    imos[s]--;
                }
            }
            flag[v] = 2;
        };
        for (int i = 0; i < n; i++) {
            if (flag[i] == 0) dfs1(dfs1, i, -1);
        }

        // 橋(imos[i] == 0となるような(i, par))で区切って二重編連結成分に分ける
        int cur_group = 0;
        belong_to.assign(n, -1);
        auto dfs2 = [&](auto f, int v) -> void {
            for (int s : g[v]) {
                if (belong_to[s] != -1) continue;
                belong_to[s] = imos[s] == 0 ? cur_group++ : belong_to[v];
                f(f, s);
            }
        };
        for (int i = 0; i < n; i++) {
            if (belong_to[i] == -1) {
                belong_to[i] = cur_group++;
                dfs2(dfs2, i);
            }
        }
        size = cur_group;
    }
};
