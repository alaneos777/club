#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

int a[MAXN];
int g[MAXN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int k,n,q;
	cin>>k;
	forn(i, k) cin>>a[i];
	
	g[0] = 0;
	forn(i, MAXN) {
		if(!i) continue;
		int f = 0;
		forn(j, k)
			if(i - a[j] >= 0)
				f |= (g[i - a[j]] == 0);
		g[i] = f;
	}

	cin>>q;
	while(q--) {
		cin>>n;
		if(!g[n]) cout<<"Second"<<endl;
		else cout<<"First"<<endl;
	}
	return 0;
}
