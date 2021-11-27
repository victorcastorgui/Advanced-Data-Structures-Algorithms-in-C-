
#ifndef Header_h
#define Header_h

#include "Graph.h"
#include <cfloat>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

class Gx {
private:
  struct NW {
    int node, pred;
    float weight;
    NW(int n, int m, float wt) : node(n), pred(m), weight(wt) {}
    bool operator<(const NW &that) const { return this->weight > that.weight; }
    bool operator>(const NW &that) const { return this->weight < that.weight; }
  };

  static float _get_capacity_of_this_path(const Graph &g,
                                          const vector<int> &path) {
    return 0.0;
  };
  static float _get_max_capacity_path(const Graph &g, int src, int dst,
                                      vector<int> &path) {
    return 0.0;
  };
  static bool _is_cyclic(const Graph &g, size_t node, vector<bool> seen,
                         vector<bool> &cycle_free) {
    if (cycle_free[node])
      return false;
    if (seen[node])
      return true;
    seen[node] = true;
    for (auto &e : g._nodes[node])
      if (_is_cyclic(g, e.dst, seen, cycle_free))
        return true;
    cycle_free[node] = true;
    return false;
  }

public:
  static bool is_cyclic(const Graph &g) {
    int n = g.get_num_nodes();
    vector<bool> seen(n), cf(n);
    for (int i = 0; i < n; i++)
      if (_is_cyclic(g, i, seen, cf))
        return true;
    return false;
  };
  static bool prune_unreachables(Graph &g, int src) {
    int n = g.get_num_nodes();
    if (src < 0 || src >= n)
      return false;

    vector<bool> vis(n);

    queue<int> q;
    q.emplace(src);
    while (!q.empty()) {
      int cur = q.front();
      q.pop();
      if (vis[cur])
        continue;
      vis[cur] = true;
      for (auto &e : g._nodes[cur])
        q.emplace(e.dst);
    }

    for (int i = 0; i < n; i++) {
      auto &edges = g._nodes[i];
      edges.erase(
          remove_if(edges.begin(), edges.end(),
                    [&](Graph::Edge &e) { return !vis[i] || !vis[e.dst]; }),
          edges.end());
    }
    return true;
  }
  static size_t get_shortest_unweighted_path(const Graph &g, int src, int dst,
                                             vector<int> &path) {
    int n = g.get_num_nodes();
    if (src < 0 || src >= n)
      return false;

    const int nan = -1000;
    vector<int> pred(n, nan);
    queue<NW> q;
    q.emplace(src, -1, 0);
    while (!q.empty()) {
      NW front = q.front();
      q.pop();
      int v = front.node, p = front.pred;
      if (pred[v] != nan)
        continue;
      pred[v] = p;
      if (v == dst)
        break;
      for (auto &e : g._nodes[v])
        q.emplace(e.dst, v, 0);
    }

    if (pred[dst] == nan) {
      path.clear();
      return string::npos;
    }

    path.clear();
    for (int cur = dst; cur != -1; cur = pred[cur])
      path.push_back(cur);
    reverse(path.begin(), path.end());
    return path.size();
  }

  static size_t get_shortest_weighted_path(const Graph &g, int src, int dst,
                                           vector<int> &path) {
    int n = g.get_num_nodes();
    if (src < 0 || src >= n)
      return false;

    const int nan = -1000;
    vector<int> pred(n, nan);
    priority_queue<NW> q;
    q.emplace(src, -1, 0);
    while (!q.empty()) {
      NW front = q.top();
      q.pop();
      int v = front.node, p = front.pred;
      float w = front.weight;
      if (pred[v] != nan)
        continue;
      pred[v] = p;
      if (v == dst)
        break;
      for (auto &e : g._nodes[v])
        q.emplace(e.dst, v, w + e.wt);
    }

    if (pred[dst] == nan) {
      path.clear();
      return string::npos;
    }

    path.clear();
    for (int cur = dst; cur != -1; cur = pred[cur])
      path.push_back(cur);
    reverse(path.begin(), path.end());
    return path.size();
  }

  static float get_max_flow(const Graph &g, int src, int dst) {
    Graph fg = g;
    float flow = 0.0;
    int n = fg.get_num_nodes();
    vector<int> par(n);
    while (true) {
      fill(par.begin(), par.end(), -1);
      par[src] = 0;
      queue<int> q;
      q.emplace(src);
      // find augmenting path
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto e : fg._nodes[v]) {
          if (par[e.dst] == -1 && e.wt > 0) {
            par[e.dst] = v;
            q.emplace(e.dst);
            if (e.dst == dst)
              goto out;
          }
        }
      }
      return flow;
    out:
      // implement path
      float inc = 1.0 / 0.0; // put +inf.
      for (int y = dst; y != src; y = par[y])
        inc = min(inc, fg.find_edge_weight(par[y], y));
      flow += inc;
      for (int y = dst; y != src; y = par[y]) {
        int p = par[y];
        fg.add_edge(p, y, -inc, false);
        fg.add_edge(y, p, inc, false);
      }
    }
  };
  friend class Tests;
};


#endif /* Header_h */
