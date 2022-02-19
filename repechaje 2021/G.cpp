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

typedef unsigned long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

ll pot (ll b, ll p) {
	ll res = 1;
	while (p) {
		if (p & 1) res *= b;
		b *= b;
		p /= 2;
	}
	return res;
}

void main_() {
	ll x, y, res = 1;
	cin >> x >> y;
	
	for (ll i = 2; i * i <= y; i++) {
		ll a = 0, b = 0;
		
		while (y % i == 0) {
			y /= i;
			a++;
		}
		
		if (!a) continue;
		
		ll k = i;
		while (k <= x) {
			b += x / k;
			k *= i;
		}
		
		res *= pot(i, min(a, b));
	}
	
	if (y > 1) {
		if (y <= x)
			res *= y;
	}
	
	cout << res << endl;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t = 1;
	cin >> t;
	while (t--)
		main_();
	
	return 0;
}
