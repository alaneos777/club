#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef long double ld;
#define forn(i,n) for (int i = 0; i < int(n); ++i)

namespace MinCost {
const ll infc = 1e17;

struct Edge {
    int to;
    ll c, f, cost;

    Edge(int to, ll c, ll cost): to(to), c(c), f(0), cost(cost)
    {  }
};

int N, S, T;
int totalFlow;
ll totalCost;
const int maxn = 505;
vector<Edge> edge;
vector<int> g[maxn];

void addEdge(int u, int v, ll c, ll cost) {
    g[u].push_back(edge.size());
    edge.emplace_back(v, c, cost);
    g[v].push_back(edge.size());
    edge.emplace_back(u, 0, -cost);
}

ll dist[maxn];
int fromEdge[maxn];

bool inQueue[maxn];
bool fordBellman() {
    forn (i, N)
        dist[i] = infc;
    dist[S] = 0;
    inQueue[S] = true;
    vector<int> q;
    q.push_back(S);
    for (int ii = 0; ii < int(q.size()); ++ii) {
        int u = q[ii];
        inQueue[u] = false;
        for (int e: g[u]) {
            if (edge[e].f == edge[e].c)
                continue;
            int v = edge[e].to;
            ll nw = edge[e].cost + dist[u];
            if (nw >= dist[v])
                continue;
            dist[v] = nw;
            fromEdge[v] = e;
            if (!inQueue[v]) {
                inQueue[v] = true;
                q.push_back(v);
            }
        }
    }
    return dist[T] != infc;
}

bool push() {
    if (!fordBellman())
        return false;
    ++totalFlow;
    int u = T;
    while (u != S) {
        int e = fromEdge[u];
        totalCost += edge[e].cost;
        edge[e].f++;
        edge[e ^ 1].f--;
        u = edge[e ^ 1].to;
    }
    return true;
}

//min-cost-circulation
ll d[maxn][maxn];
int dfrom[maxn][maxn];
int level[maxn];
void circulation() {
    while (true) {
        int q = 0;
        fill(d[0], d[0] + N, 0);
        forn (iter, N) {
            fill(d[iter + 1], d[iter + 1] + N, infc);
            forn (u, N)
                for (int e: g[u]) {
                    if (edge[e].c == edge[e].f)
                        continue;
                    int v = edge[e].to;
                    ll ndist = d[iter][u] + edge[e].cost;
                    if (ndist >= d[iter + 1][v])
                        continue;
                    d[iter + 1][v] = ndist;
                    dfrom[iter + 1][v] = e;
                }
            q ^= 1;
        }
        int w = -1;
        ld mindmax = 1e17;
        forn (u, N) {
            ld dmax = -1e17;
            forn (iter, N)
                dmax = max(dmax,
                    (d[N][u] - d[iter][u]) / ld(N - iter));
            if (mindmax > dmax)
                mindmax = dmax, w = u;
        }
        if (mindmax >= 0)
            break;
        fill(level, level + N, -1);
        int k = N;
        while (level[w] == -1) {
            level[w] = k;
            w = edge[dfrom[k--][w] ^ 1].to;
        }
        int k2 = level[w];
        ll delta = infc;
        while (k2 > k) {
            int e = dfrom[k2--][w];
            delta = min(delta, edge[e].c - edge[e].f);
            w = edge[e ^ 1].to;
        }
        k2 = level[w];
        while (k2 > k) {
            int e = dfrom[k2--][w];
            totalCost += edge[e].cost * delta;
            edge[e].f += delta;
            edge[e ^ 1].f -= delta;
            w = edge[e ^ 1].to;
        }
    }
}
}

struct planet{
	ll x, y, z;
	int p, q;
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<planet> planets(n + 1);
	int c1 = 0, c2 = 0;
	for(int i = 1; i <= n; ++i){
		cin >> planets[i].x >> planets[i].y >> planets[i].z >> planets[i].p >> planets[i].q;
		c1 += planets[i].p;
		c2 += planets[i].q;
	}
	if(c1 != c2){
		cout << "Imposible";
		return 0;
	}
	MinCost::N = 2 * n + 2;
	MinCost::S = 0;
	MinCost::T = 2 * n + 1;
	for(int i = 1; i <= n; ++i)
		MinCost::addEdge(0, i, planets[i].p, 0);
	for(int a = 1; a <= n; ++a)
		for(int b = 1; b <= n; ++b)
			if(a != b)
				MinCost::addEdge(a, n + b, 1, planets[a].x * planets[b].z * planets[b].z + planets[a].y * planets[a].y * planets[b].y + planets[a].z * planets[b].x * planets[b].x);
	for(int i = 1; i <= n; ++i)
		MinCost::addEdge(n + i, 2 * n + 1, planets[i].q, 0);
	while (MinCost::push());
	if(MinCost::totalFlow != c1){
		cout << "Imposible";
		return 0;
	}
	ll ans = MinCost::totalCost;
	cout << ans << "\n";
	for(int u = 1; u <= n; ++u){
		for(int dest : MinCost::g[u]){
			MinCost::Edge v = MinCost::edge[dest];
			if(v.to > 0 && v.f == 1){
				cout << u << " " << (v.to - n) << " " << v.cost << "\n";
			}
		}
	}
	return 0;
}