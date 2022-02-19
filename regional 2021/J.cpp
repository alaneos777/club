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
 
const int MX = 100005;
int n, k, res[MX];
vi to[MX];
map<vi, int> mp;
 
void pre () {
	int mx = 0;
	forn (a, 8 + 1)
	forn (b, 8 + 1) if (a + b <= 8)
	forn (c, 8 + 1) if (a + b + c <= 8)
	forn (d, 8 + 1) if (a + b + c + d <= 8)
	forn (e, 8 + 1) if (a + b + c + d + e <= 8)
	forn (f, 8 + 1) if (a + b + c + d + e + f <= 8)
	forn (g, 8 + 1) if (a + b + c + d + e + f + g <= 8)
	forn (h, 8 + 1) if (a + b + c + d + e + f + g + h <= 8) {
		vi v = {a, b, c, d, e, f, g, h};
		int sz = mp.size();
		mp[v] = sz;
		
		forn (aa, a + 1)
		forn (bb, b + 1)
		forn (cc, c + 1)
		forn (dd, d + 1)
		forn (ee, e + 1)
		forn (ff, f + 1)
		forn (gg, g + 1)
		forn (hh, h + 1) {
			vi w = {aa, bb, cc, dd, ee, ff, gg, hh};
			to[mp[v]].pb(mp[w]);
		}
	}
}
 
vi v[MX];
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	pre();
	
	cin >> n >> k;
	
	int ind = 1;
	while (n--) {
		char op;
		cin >> op;
		
		if (op == 'C') {
			int r;
			cin >> r;
			v[ind].resize(8);
			
			while (r--) {
				int x;
				cin >> x;
				v[ind][x - 1]++;
			}
			
			for (int u : to[mp[v[ind]]])
				res[u]++;
			
			ind++;
		} else if (op == 'D') {
			int x;
			cin >> x;
			
			for (int u : to[mp[v[x]]])
				res[u]--;
		} else {
			int r;
			cin >> r;
			vi w(8);
			
			while (r--) {
				int x;
				cin >> x;
				w[x - 1]++;
			}
			
			cout << res[mp[w]] << endl;
		}
	}
	
	return 0;
}
