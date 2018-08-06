#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second
#define pb(a) push_back(a)

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

int vis[MAXN];
int mex[MAXN];
int grundy[MAXN];
vector<int> orden;
vector<int> lista[MAXN];

void dfs(int u) {
	vis[u] = 1;
	forn(i, lista[u].size()) {
		int v = lista[u][i];
		if(!vis[v]) dfs(v);
	}
	orden.pb(u);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n,m,a,b;
	cin>>n>>m;
	while(m--) {
		cin>>a>>b;
		a--,b--;
		lista[a].pb(b);
	}

	forn(i, n) 
		if(!vis[i])
			dfs(i);
	
	forn(i, n) {
		int u = orden[i];
		forn(j, lista[u].size()) {
			int v = lista[u][j];
			mex[ grundy[v] ] = 1;
		}

		forn(i, MAXN)
			if(!mex[i]) {
				grundy[u] = i;
				break;
			}

		forn(j, lista[u].size()) {
			int v = lista[u][j];
			mex[ grundy[v] ] = 0;
		}
	}

	forn(i, n)
		cout<<grundy[i]<<endl;
	return 0;
}
