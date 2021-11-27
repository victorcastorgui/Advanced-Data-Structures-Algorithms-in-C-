#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#pragma once
using namespace std;

class Graph {
public:
  struct Edge {
    int dst;
    float wt;

    Edge(int tgt = -1, float w = 0) : dst(tgt), wt(w) {}
    bool operator==(const Edge &that) const {
      return dst == that.dst && wt == that.wt;
    }

    bool operator!=(const Edge &that) const {
      return dst != that.dst || wt != that.wt;
    }
  };

protected:
  static double constexpr FLOOR = 1e-6;
  vector<vector<Edge>> _nodes;

public:
  size_t get_num_nodes() const { return _nodes.size(); }
  bool is_empty() const { return _nodes.empty(); }
  void clear() { _nodes.clear(); }
  string to_string() const {
    int n = get_num_nodes();
    stringstream buf;
    buf << "# Graph - " << n << " nodes." << endl;
    buf << "# Edge lists:" << endl;
    for (int i = 0; i < n; i++) {
      if (_nodes[i].empty())
        continue;
      buf << i << " : ";
      for (auto e : _nodes[i])
        buf << "(" << e.dst << "," << e.wt << ") ";
      buf << endl;
    }
    buf << "# End of Graph" << endl;
    return buf.str();
  };
  Graph &add_edge(int src, int tgt, float wt, bool replace = true) {
    _nodes.resize(max((int)_nodes.size(), max(src + 1, tgt + 1)));
    if (src == tgt)
      return *this;

    vector<Edge> &edges = _nodes[src];
    auto it = find_if(edges.begin(), edges.end(),
                      [=](Edge e) { return e.dst == tgt; });
    if (it == edges.end()) {
      edges.emplace_back(tgt, wt);
      return *this;
    }

    it->wt = replace ? wt : it->wt + wt;
    return *this;
  }

  float find_edge_weight(int src, int tgt) const {
    if (src >= (int)_nodes.size())
      return Graph::FLOOR;
    auto &edges = _nodes[src];
    auto it = find_if(edges.begin(), edges.end(),
                      [=](Edge e) { return e.dst == tgt; });
    return it == edges.end() ? Graph::FLOOR : it->wt;
  }

  friend class Gx;
  friend class Tests;
};
