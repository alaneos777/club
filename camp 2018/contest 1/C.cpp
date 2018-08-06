#include <bits/stdc++.h>
 
using namespace std;
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define FOR(i,n) for (int i = 0; i < n; i++)

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

struct ST {
	ii st[40005];
	int lz[40005];

	void init (int i, int j, int pos) {
		st[pos].fi = lz[pos] = 0;
		st[pos].se = i;

		if (i != j) {
			int m = (i+j)/2;
			init(i, m, pos*2);
			init(m+1, j, pos*2+1);
		}
	}

	void update (int i, int j, int pos, int a, int b, int k) {
		if (lz[pos]) {
			st[pos].fi += lz[pos];
			if (i != j) {
				lz[pos*2] += lz[pos];
				lz[pos*2+1] += lz[pos];
			}
			lz[pos] = 0;
		}

		if (j < a || i > b)
			return;

		if (a <= i && j <= b) {
			st[pos].fi += k;

			if (i != j) {
				lz[pos*2] += k;
				lz[pos*2+1] += k;
			}

			return;
		}

		int m = (i+j)/2;
		update(i, m, pos*2, a, b, k);
		update(m+1, j, pos*2+1, a, b, k);

		if (st[pos*2].fi >= st[pos*2+1].fi)
			st[pos] = st[pos*2];
		else
			st[pos] = st[pos*2+1];
	}

	ii query () {
		return st[1];
	}
};

int n, k, x[50005], y[50005], q[50005];
ii res(0, 0);

ST st;

bool comp (const int a, const int b) {
	return x[a] < x[b];
} 

bool esPos (int m) {
	int i = 0, j = 0;

	st.init(1, 1e4, 1);

	for (int a = 1; a <= 1e4; a++) {

		while (i < n && a + m >= x[q[i]]) {
			st.update(1, 1e4, 1, max(1, y[q[i]]-m), y[q[i]], 1);
			i++;
		}

		while (j < n && x[q[j]] < a) {
			st.update(1, 1e4, 1, max(1, y[q[j]]-m), y[q[j]], -1);
			j++;
		}

		ii d = st.query();

		if (d.fi >= k) {
			res = ii(a, d.se);
			return 1;
		}
	}

	return 0;
}

int obtRes () {
	int i = 1, j = 1e4+5, m = (i+j)/2, rep = 18;

	while (rep--) {
		if (esPos(m))
			j = m;
		else
			i = m;
		m = (i+j)/2;
	}

	if (esPos(i))
		return i;

	assert(esPos(j));
	return j;
}

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    	cin >> x[i] >> y[i];

    for (int i = 0; i < n; i++)
    	q[i] = i;
    sort(q, q+n, comp);

    cout << obtRes () << endl;
    cout << res.fi << " " << res.se << endl;

    return 0;
}
