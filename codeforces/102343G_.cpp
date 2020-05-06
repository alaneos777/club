// 20
/****************************************************
https://searleser97.gitlab.io/algorithms/template.cpp
****************************************************/

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define forr(_, x, n) for (int _ = x; _ > n; _--)
#define fos(_, x, n, s) for (int _ = x; _ < n; _ += s)
#define forn(_, x, n) fos(_, x, n, 1)
#define rep(_, n) forn(_, 0, n)
#define fi first
#define se second
#define pb push_back
#define pairii pair<int, int>
#define all(x) x.begin(), x.end()
#define cerr(s) cerr << "\033[48;5;196m\033[38;5;15m" << s << "\033[0m"
// typedef __int128_t lli;
typedef long long int li;
typedef long double ld;
// 12
// 5
// cap[a][b] = Capacity left from a to b
// icost = initial cost, icap = initial capacity
// pathMinCap = capacity bottleneck for a path (s->t)
// 4
typedef int T;
vector<vector<int>> adj, cap, cost;
const T inf = 1 << 30;
// 4
void init(int N) {
  adj.assign(N, vector<int>());
  cap.assign(N, vector<int>(N));
  cost.assign(N, vector<int>(N));
}
// 6
void addEdge(int u, int v, T icap, T icost) {
  // if (!cap[u][v])
  adj[u].push_back(v), adj[v].push_back(u);
  cap[u][v] = icap;
  cost[u][v] = icost;
  // cap[v][u] = cap[u][v]; // if graph is undirected
  // cost[v][u] = cost[u][v]; // if graph is undirected
}
// 19
// O(N)
void bellmanFordFast(int s, vector<int> &dad,
                     vector<T> &dist) {
  dad.assign(adj.size(), -1);
  dist.assign(adj.size(), inf);
  vector<int> its(adj.size()), inqueue(adj.size());
  queue<int> q;
  q.push(s), dist[s] = 0, its[s] = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop(), inqueue[u] = 0;
    for (auto &v : adj[u]) {
      T d = dist[u] + cost[u][v];
      if (d < dist[v] && cap[u][v] > 0) {
        dist[v] = d, dad[v] = u;
        if (!inqueue[v]++) q.push(v), its[v]++;
        if (its[v] == adj.size()) return;
      }
    }
  }
}
// 20
// O(E^2 * V)
pair<T, T> minCostFlow(int s, int t, int k = inf) {
  T flow = 0, cost = 0;
  vector<int> dad;
  vector<T> dist;
  while (flow < k) {
    bellmanFordFast(s, dad, dist);
    if (dist[t] == inf) break;
    T f = k - flow;
    int u = t;
    while (u != s)
      f = min(f, cap[dad[u]][u]), u = dad[u];
    flow += f, cost += f * dist[t], u = t;
    while (u != s) {
      cerr(u) << endl;
      cap[dad[u]][u] -= flow, cap[u][dad[u]] += flow;
      u = dad[u];
    }
    cerr(u) << endl;
    cerr("++++++") << endl;
  }
  return {cost, flow};
}

bool isOutOfBounds(int i, int j, int r, int c) {
  if (i < 0 or i >= r or j < 0 or j >= c) return true;
  return false;
}

struct Node {
  int in, out;
  char symbol;
};

void _main(int tc) {
  int r, c, offset = 1;
  cin >> r >> c;
  vector<vector<Node>> mat(r, vector<Node>(c));
  init(offset + 2 * r * c);
  Node bonnie, clyde, ford;
  int id = offset;
  rep(i, r) {
    rep(j, c) {
      char x;
      cin >> x;
      mat[i][j] = {id, id + 1, x};
      id += 2;
      // cerr(mat[i][j].in << " " << mat[i][j].out) << endl;
      if (x == '.')
        addEdge(mat[i][j].in, mat[i][j].out, 1, 0);
      else if (x == 'F')
        addEdge(mat[i][j].in, mat[i][j].out, 2, 0);
      
      if (x == 'B') {
        bonnie = mat[i][j];
      } else if (x == 'C') {
        clyde = mat[i][j];
      } else if (x == 'F') {
        ford = mat[i][j];
      }
    }
  }
  
  vector<vector<int>> movs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  rep(i, r) {
    rep(j, c) {
      for (auto &mov : movs) {
        int newI = i + mov[0];
        int newJ = j + mov[1];
        if (!isOutOfBounds(newI, newJ, r, c) && mat[newI][newJ].symbol != 'x') {
          addEdge(mat[i][j].out, mat[newI][newJ].in, 1, 1);
        }
      }
    }
  }

  int source = 0;
  addEdge(source, bonnie.out, 1 , 0);
  addEdge(source, clyde.out, 1, 0);
  auto ans = minCostFlow(0, ford.out, 2);
  if (ans.second < 2) cout << -1 << endl;
  else cout << ans.first << endl;
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  _main(0); return 0;
  int tc;
  cin >> tc;
  rep(i, tc) _main(i + 1);
}
