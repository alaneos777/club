#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb(x) push_back(x)

using namespace std;

typedef __int128 ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

typedef vector<ll> vl;

vl x, y, z, c;
ll ini, fin;

void read (vl &v) {
	int n;
	cin >> n;
	while (n--) {
		int x;
		cin >> x;
		v.pb(x);
		ini = max(ini, ll(x) + 1);
	}
} 

ostream & operator << (ostream &out, ll x) {
	string res;
	while (x) {
		res.pb(x % 10 + '0');
		x /= 10;
	}
	if (res.empty()) res = "0";
	reverse(all(res));
	out << res;
	return out;
}

bool esPos (ll m, bool f = false) {
	vl res;

	reverse(all(c));

	for (ll i = 0, car = 0; i < c.size() || car; i++) {
		if (i < c.size()) car += c[i];
		res.pb(car % m);
		car /= m;
	}

	reverse(all(c));
	reverse(all(res));

	if (res.size() > z.size()) return 0;
	if (res.size() < z.size()) return 1;

	forn (i, c.size()) {
		if (res[i] > z[i]) return 0;
		if (res[i] < z[i]) return 1;
	}

	if (f) {
		cout << m << endl;
		exit(0);
	}

	return 1;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	read(x), read(y), read(z);

	c.resize((int)x.size() + (int)y.size() - 1);

	reverse(all(x));
	reverse(all(y));

	forn (i, x.size()) forn (j, y.size()) {
		c[i + j] += x[i] * y[j];
		fin = max(fin, c[i + j] + 1);
	}

	reverse(all(x));
	reverse(all(y));
	reverse(all(c));

	int rep = 75;
	while (rep--) {
		ll m = (ini + fin) / 2;
		if (esPos(m)) fin = m;
		else ini = m;
	}

	esPos(fin, 1);

	cout << "impossible" << endl;

	return 0;
}