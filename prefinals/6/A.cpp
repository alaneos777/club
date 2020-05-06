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

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 1005;
int n, a[MX];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n;
	
	a[0] = 1;
	a[1] = 1;

	for (int i = 2; i <= n; i++) {
		set<int> st;

		for (int k = 1; i - 2 * k >= 0; k++)
			st.insert(2 * a[i - k] - a[i - 2 * k]);

		for (int k = 1;; k++)
			if (!st.count(k)) {
				a[i] = k;
				break;
			}
	}

	cout << a[n] << endl;

	return 0;
}