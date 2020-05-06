#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define pb(x) push_back(x)
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

int n;
ll a[60], tot, suf[60];

bool f (ll a, ll b) {
	for (ll i = 0, ans = 1; i <= n; i++, ans *= 2) {
		ll x = a - a % ans;
		ll y = b - b % ans;

		if (suf[i] > x * y)
			return 0; 
	}

	return 1;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;

	for (ll i = 0, ans = 1; i <= n; i++, ans *= 2) {
		cin >> a[i];
		tot += a[i] * ans * ans;
		suf[i] = a[i] * ans * ans;
	}

	for (int i = n - 1; i >= 0; i--)
		suf[i] += suf[i + 1];

	for (ll i = 1; i * i <= tot; i++)
		if (tot % i == 0) {
			ll a = i;
			ll b = tot / i;

			if (f(a, b)) {
				cout << a << " " << b << endl;
				return 0;
			}
		}

	cout << "impossible" << endl;

	return 0;
}
