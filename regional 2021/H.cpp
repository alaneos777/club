#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
 
#define SET(p,n) memset(p, n, sizeof (p))
 
const int INF = INT_MAX;
const int MN = 105, ME = 4 * MN * MN;
 
int src, snk, nno, ned;
int q[MN], fin[MN], pro[MN], dist[MN];
int flow[2*ME], cap[2*ME];
int sig[2*ME], to[2*ME];
 
inline void init (int _src, int _snk, int _n) {
	src = _src, snk = _snk, nno = _n, ned = 0;
	SET(fin, -1);
}
 
inline void add (int u, int v, int c) {
	to[ned] = v, cap[ned] = c, flow[ned] = 0, sig[ned] = fin[u], fin[u] = ned++;
	to[ned] = u, cap[ned] = 0, flow[ned] = 0, sig[ned] = fin[v], fin[v] = ned++;
}
 
inline void reset (int _src, int _snk) {
    src = _src, snk = _snk;
    for (int i = 0; i < ned; i++)
        flow[i] = 0;
}
 
bool bfs () {
	int st, en, u, v;
	SET(dist, -1);
 
	dist[src] = st = en = 0;
	q[en++] = src;
 
	while (st < en) {
		u = q[st++];
 
		for (int e = fin[u]; e >= 0; e = sig[e]) {
			v = to[e];
 
			if (flow[e] < cap[e] && dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q[en++] = v;
			}
		}
	}
 
	return dist[snk] != -1;
}
 
int dfs (int u, int mn) {
	if (u == snk)
		return mn;
 
	int au, v;
	for (int &e = pro[u]; e >= 0; e = sig[e]) {
		v = to[e];
 
		if (flow[e] < cap[e] && dist[v] == dist[u]+1)
			if (au = dfs(v, min(mn, cap[e] - flow[e]))) {
                flow[e] += au;
                flow[e^1] -= au;
                return au;
            }
	}
 
	return 0;
}
 
ll dinitz () {
	ll f = 0;
	int au;
 
	while (bfs()) {
		for (int i = 0; i <= nno; i++)
			pro[i] = fin[i];
 
		while (au = dfs(src, INF))
			f += au;
	}
 
	return f;
}
 
const int MX = 105;
int n, l[MX][MX * MX], k[MX];
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	int s = 1, t = 0;
	init(s, t, n + 3);
	
	for (int i = 1; i <= n; i++) {
		string in;
		cin >> in;
		
		if (in == "*") {
			k[i] = 1;
			cin >> l[i][0];
			
			if (l[i][0] == s) add(i, t, ME);
			else add(i, l[i][0], ME);
		} else {
			k[i] = stoi(in);
			
			forn (j, k[i]) {
				cin >> l[i][j];
				
				if (l[i][j] == s) add(i, t, 1);
				else add(i, l[i][j], 1);
			}
		}
	}
	
	int res = dinitz();
	
	if (res >= ME) cout << "*" << endl;
	else cout << res + 1 << endl;
	
	return 0;
}