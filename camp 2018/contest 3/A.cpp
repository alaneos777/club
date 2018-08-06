#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define fi first
#define se second

using namespace std;

const int inf = 1e9;
const int MAXN = 1001;

lli cont[MAXN];
lli fact[MAXN];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	string cad;

	fact[0] = 1;
	forn(i, MAXN)
		if(i) fact[i] = fact[i - 1] * (lli) i;

	cin>>cad;

	forn(i, cad.size()) cont[ cad[i] ]++;

	lli ans = fact[cad.size()];
	forn(i, MAXN)
		if(cont[i])
			ans /= fact[ cont[i] ];

	cout<<ans<<endl;
	return 0;
}
