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
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 200005;
int n, fi[MX], se[MX], f[MX], x[MX], p[MX], mn[MX];
queue<int> q;

int parent (int a) {
	return a == p[a] ? a : p[a] = parent(p[a]);
}

void join (int a, int b) {
	a = parent(a), b = parent(b);

	if (a == b) return;

	mn[a] = min(mn[a], mn[b]);
	p[b] = a;
}

bool valid (int &a, int &b, int x) {
	if ((x + 1) % n == a) {
		a = x;
		return 1;
	}

	if ((b + 1) % n == x) {
		b = x;
		return 1;
	}

	return 0;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	iota(p, p + MX, 0);
	iota(mn, mn + MX, 0);

	cin >> n;
	
	forn (i, n) {
		cin >> fi[i];
		fi[i]--;
	}

	forn (i, n) {
		cin >> se[i];
		se[i]--;
		f[se[i]] = i;
	}

	forn (i, n) {
		x[i] = f[fi[i]];
		x[i + n] = x[i];
	}

	int l = 0, r = 0;
	while (r < 2 * n) {
		l = r;
		while (q.size()) q.pop();
		
		int a = x[l], b = x[r];
		q.push(l);

		while (r - l + 1 < n) {
			if (r + 1 < 2 * n && valid(a, b, x[r + 1])) {
				r++;
				q.push(r);
			} else if (l && valid(a, b, x[l - 1])) {
				join(l, l - 1);
				l = mn[parent(l)];
				q.push(l);
			} else {
				break;
			}
		}

		if (r - l + 1 >= n) {
			vi res;

			int l = q.front(), r = l;
			q.pop();

			res.pb(l);

			while (q.size()) {
				int sig = q.front();
				q.pop();

				while (r < sig) {
					r++;
					res.pb(r);
				}

				while (sig < l) {
					l--;
					res.pb(l);
				}
			}

			forn (i, n)
				cout << fi[res[i] % n] + 1 << " ";
			cout << endl;

			return 0;
		}

		r++;
	}

	cout << -1 << endl;

	return 0;
}
