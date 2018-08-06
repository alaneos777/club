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

const int MX = 500005;

struct ST {
	int v[MX], a, b, op, x;
	
	int st[4*MX];
	int dif[4*MX];
	int _and[4*MX], _or[4*MX];

	int lz[4*MX];
	int cero[4*MX];
	int uno[4*MX];

	void build (int i, int j, int pos) {
		cero[pos] = 0;
		uno[pos] = 0;
		dif[pos] = 0;
		lz[pos] = 0;

		if (i == j) {
			st[pos] = v[i];
			_and[pos] = v[i];
			_or[pos] = v[i];
			return;
		}

		int m = (i+j)/2;
		build(i, m, pos*2);
		build(m+1, j, pos*2+1);
		_and[pos] = _and[pos*2] & _and[pos*2+1];
		_or[pos] = _or[pos*2] | _or[pos*2+1];

		st[pos] = min(st[pos*2], st[pos*2+1]);
		dif[pos] = _and[pos] ^ _or[pos];
		return;
	}

	void lazy (int i, int jj, int pos) {
		st[pos] |= uno[pos];
		st[pos] &= ~cero[pos];

		if (i != jj) {
			lz[pos*2] = lz[pos*2+1] = lz[pos];

			uno[pos*2] &= ~cero[pos];
			cero[pos*2] &= ~uno[pos];
			uno[pos*2] |= uno[pos];
			cero[pos*2] |= cero[pos];

			uno[pos*2+1] &= ~cero[pos];
			cero[pos*2+1] &= ~uno[pos];
			uno[pos*2+1] |= uno[pos];
			cero[pos*2+1] |= cero[pos];
		}

		_and[pos] = st[pos];
		_or[pos] = st[pos];
		dif[pos] = 0;
		lz[pos] = 0;
		cero[pos] = 0;
		uno[pos] = 0;	
	}

	void update (int i, int j, int pos) {
		if (lz[pos])
			lazy(i, j, pos);

		if (i > b || j < a)
			return;

		if (a <= i && j <= b && !dif[pos]) {
			lz[pos] = op;

			if (op == 1)
				uno[pos] = x;
			else
				cero[pos] = ~x;

			lazy(i, j, pos);
			return;
		}

		int m = (i+j)/2;
		update(i, m, pos*2);
		update(m+1, j, pos*2+1);
		_and[pos] = _and[pos*2] & _and[pos*2+1];
		_or[pos] = _or[pos*2] | _or[pos*2+1];

		st[pos] = min(st[pos*2], st[pos*2+1]);
		dif[pos] = _and[pos] ^ _or[pos];
		return;
	}

	int query (int i, int j, int pos) {
		if (lz[pos])
			lazy(i, j, pos);

		if (i > b || j < a)
			return 2e9;

		if (a <= i && j <= b)
			return st[pos];

		int m = (i+j)/2;
		return min(query(i, m, pos*2), query(m+1, j, pos*2+1));
	}
};

int n, q, l, r, x;
char op;

ST st;

int main () {
    //ios_base::sync_with_stdio(0); cin.tie(0);
    
    scanf (" %d ", &n);
    for (int i = 1; i <= n; i++)
    	scanf(" %d ", &st.v[i]);
    st.build(1, n, 1);

    scanf(" %d ", &q);
    while (q--) {
    	scanf(" %c %d %d ", &op, &l, &r);

    	if (op == '?') {
    		st.a = l, st.b = r;
    		printf("%d\n", st.query(1, n, 1));
    	} else {
    		scanf(" %d ", &x);
    		st.a = l, st.b = r, st.op = int(op == '&') + 1, st.x = x;
    		st.update(1, n, 1);
    	}
    }

    return 0;
}
