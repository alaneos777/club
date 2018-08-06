#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int,int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >

using namespace std;

const int MAXN = 1001;

vi A,B;
int M[MAXN];
int vis[MAXN];
vi lista[MAXN];
vi graph[MAXN];
int cannot[MAXN];

void add(int u,int v) {
	lista[u].pb(v);
	lista[v].pb(u);
}

int tryKuhn(int a) {
	if(vis[a]) return 0;
	vis[a] = 1;
	forn(i, lista[a].size()) {
		int b = lista[a][i];
		if(M[b] == -1 || tryKuhn(M[b])) {
			M[b] = a;
			M[a] = b;
			return 1;
		}
	}
	return 0;
}

int maxMatching() {
	forn(i, B.size()) M[ B[i] ] = -1;
	forn(i, A.size()) M[ A[i] ] = -1;

	int ans = 0;
	forn(i, A.size()) {
		forn(j, A.size()) vis[ A[j] ] = 0;
		ans += tryKuhn(A[i]);
	}
	return ans;
}

void dfs(int u,int a,int b) {
	vis[u] = 1;
	if(a <= u && u <= b) cannot[u] = 1;
	forn(i, graph[u].size()) {
		int v = graph[u][i];
		if(vis[v]) continue;
		dfs(v, a, b);
	}
}

int go(int u,int a,int b) {
	if(a <= u && u <= b && M[u] == -1) return 1;
	vis[u] = 1;
	int ans = 0;
	forn(i, graph[u].size()) {
		int v = graph[u][i];
		if(vis[v]) continue;
		ans |= go(v, a, b);
	}
	return ans;
}

// чтение и перевод это будет пустой тратой времени
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m,q,a,b;
	cin>>n>>m>>q;

	forn(i, n) A.pb(i);
	forn(i, m) B.pb(i + n);

	vector<pii> aristas;
	while(q--) {
		cin>>a>>b;
		a--,b--;
		add(a, b + n);
		aristas.pb(pii(a, b + n));
	}

	int ans = maxMatching();

	forn(i, aristas.size()) {
		a = aristas[i].fi;
		b = aristas[i].se;
		if(M[b] == a) graph[a].pb(b);
		else graph[b].pb(a);
	}

	forn(i, A.size()) {
		if(M[ A[i] ] == -1) {
			fill(vis, vis + A.size() + B.size(), 0);
			dfs(A[i], 0, n - 1);
		} else {
			fill(vis, vis + A.size() + B.size(), 0);
			if(go(A[i], 0, n - 1)) cannot[A[i]] = 1;
		}
	}

	forn(i, B.size()) {
		if(M[ B[i] ] == -1) {
			fill(vis, vis + A.size() + B.size(), 0);
			dfs(B[i], n, n + m - 1);
		} else {
			fill(vis, vis + A.size() + B.size(), 0);
			if(go(B[i], n, n + m - 1)) cannot[B[i]] = 1;
		}
	}
	
	forn(i, n)
		if(cannot[i]) cout<<"P";
		else cout<<"N";
	cout<<endl;
	forn(i, m)
		if(cannot[i + n]) cout<<"P";
		else cout<<"N";
	return 0;
}
