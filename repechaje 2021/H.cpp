#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = int(a); i <= int(b); i++)
#define all(v) v.begin(), v.end()
#define pb push_back

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 105, SIG = 26, mod = 1000000007;
int nex[MX][SIG], fail[MX], out[MX], finish[MX], cnt[MX], sz = 1;

void insert (string &s, int ind) {
	int u = 0;

	for (char c : s) {
		c -= 'a';

		if (!nex[u][c]) {
			nex[u][c] = sz;
			finish[sz] = -1;
			sz++;
		}

		u = nex[u][c];
	}

	finish[u] = ind;
	cnt[u]++;
}

int getFail (int u, int c) {
	while (u && !nex[u][c])
		u = fail[u];
	return nex[u][c];
}

void build () {
	queue<int> q;
	
	for (int i = 0; i < SIG; i++)
		if (nex[0][i])
			q.push(nex[0][i]);

	while (q.size()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < SIG; i++) {
			int v = nex[u][i];

			if (v) {
				fail[v] = getFail(fail[u], i);
				cnt[v] += cnt[fail[v]];
				q.push(v);

				out[v] = fail[v];
				while (finish[out[v]] == -1)
					out[v] = fail[out[v]];
			}
		}
	}
}

vvi operator * (const vvi &a, const vvi &b) {
	vvi res(sz, vi(sz));
	
	forn (i, sz)
		forn (j, sz)
			forn (k, sz)
				res[i][j] = (0ll + res[i][j] + 1ll * a[i][k] * b[k][j]) % mod;
	
	return res;
}

ll pot (ll b, int p) {
	ll res = 1;
	while (p) {
		if (p & 1) (res *= b) %= mod;
		(b *= b) %= mod;
		p /= 2;
	}
	return res;
}

void main_() {
	int n, M;
	cin >> n >> M;
	
	forn (i, M) {
		string s;
		cin >> s;
		
		insert(s, i + 1);
	}
	
	build();
	
	vvi m(sz, vi(sz));
	forn (u, sz) {
		if (cnt[u]) continue;
		
		forn (c, SIG) {
			int v = getFail(u, c);
			if (cnt[v]) continue;
			
			m[u][v]++;
		}
	}
	
	vvi res(sz, vi(sz));
	forn (i, sz)
		res[i][i] = 1;
	
	int p = n;
	while (p) {
		if (p & 1) res = res * m;
		m = m * m;
		p /= 2;
	}
	
	ll s = 0;
	forn (i, sz)
		(s += res[0][i]) %= mod;
	cout << MOD(pot(26, n) - s, mod) << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t = 1;
	// cin >> t;
	while (t--)
		main_();
	
	return 0;
}
