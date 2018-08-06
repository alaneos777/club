#include <bits/stdc++.h>
#define endl '\n'
#define forn(i, n) for(int i=0;i<n;i++)
#define lli long long int
#define pii pair<int, int>
#define fi first
#define se second
#define psi pair<int,pii>
#define pb push_back
#define vi vector<int>
#define vii vector< vi >
#define dato pii
#define left(a) (a << 1)
#define right(a) ((a << 1) + 1)

using namespace std;

const int inf = 1e9 + 7;
const int MAXV = 1000001;

lli ans;

struct node {
	dato x;
	int y;
	lli total;
	node *l, *r;
	node(dato a) : x(a), y(rand()), l(r=NULL), total(x.se) {}
};

lli valor(node *t) {
	return !t ? 0 : t->total;
}

void update(node *t) {
	if(!t) return;
	t->total = (lli) (t->x.se) + valor(t->l) + valor(t->r);
}

void split(node *t, node *&l, node *&r, dato x) {
	if (!t) return (void)(l=r=NULL);
	if (x <= t->x) {
		split(t->l, l, t->l, x), r = t;
	} else {
		split(t->r, t->r, r, x), l = t;
	}
	update(t);
}

node *merge(node *l, node *r) {
	if (!l) return r;
	if (!r) return l;
	if (l->y > r->y) {
		l->r = merge(l->r, r);
		update(l);
		return l;
	} else {
		r->l = merge(l, r->l);
		update(r);
		return r;
	}
}

node *insert(node *t, node *n) {
	node *l, *r;
	split(t, l, r, n->x);
	return merge(l, merge(n, r));
}

node *remove(node *t, dato x) {
	node *l, *r;
	x.se++;
	split(t, l, r, x);

	x.se--;
	node *p, *q;
	split(l, p, q, x);

	if(q) delete q;

	return merge(p, r);
}

node *insert(node *t, dato x) {
	return insert(t, new node(x));
}

node *suma(node *t, lli x) {
	node *l, *r;
	split(t, l, r, dato(x + 1, -inf));
	ans += valor(r);
	return merge(l, r);
}

node *root[4 * MAXV];

void clear() {
	forn(i, 4 * MAXV) {
		root[i] = '\0';
	}
}

void update(int node, int l, int r, int a, int b, dato v, int op) {
	if(b < l || a > r) return;
	if(op) root[node] = remove(root[node], v);
	else root[node] = insert(root[node], v);
	if(a <= l && r <= b) return;
	int med = (l + r) >> 1;
	update(left(node), l, med, a, b, v, op);
	update(right(node), med + 1, r, a, b, v, op);
}

void query(int node, int l, int r, int a,int b) {
	if(b < l || a > r) return;
	if(a <= l && r <= b) {
		root[node] = suma(root[node], b);
		return;
	}
	int med = (l + r) >> 1;
	query(left(node), l, med, a, b);
	query(right(node), med + 1, r, a, b);
}

int cont;
int num[MAXV];
int values[MAXV];
set<int> lista[MAXV];

int mapea(int x) {
	return lower_bound(values, values + cont, x) - values;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	srand(time(0));
	int n,a,b;
	char op;
	cin>>n;

	forn(i, n) {
		cin>>num[i];
		values[cont++] = num[i];
	}

	vector<psi> queries;
	int q;
	cin>>q;
	forn(i, q) {
		cin>>op>>a>>b;
		queries.pb(psi(op, pii(a, b)));
		if(op == 'U') 
			values[cont++] = b;
	}
	sort(values, values + cont);

	forn(i, n)
		lista[ mapea( num[i] ) ].insert(i);

	forn(i, cont) {
		lista[ mapea( values[i] ) ].insert(inf);
		lista[ mapea( values[i] ) ].insert(-inf);
	}

	forn(i, n) {
		int next = *lista[ mapea( num[i] ) ].upper_bound(i);
		update(1, 0, n - 1, i, i, dato(next, num[i]), 0);
	}
	set<int> :: iterator viejo, nuevo;

	forn(i, q) {
		op = queries[i].fi;
		a = queries[i].se.fi;
		b = queries[i].se.se;

		if(op == 'Q') {
			a--,b--;
			ans = 0;
			query(1, 0, n - 1, a, b);
			cout<<ans<<endl;
		} else {
			a--;
			if(num[a] == b) continue;

			nuevo = lista[ mapea(b) ].upper_bound(a);
			int nuevoNext = *nuevo;
			nuevo--;
			int nuevoPrev = *nuevo;

			viejo  = lista[ mapea( num[a] ) ].upper_bound(a);
			int viejoNext = *viejo;
			viejo--; viejo--;
			int viejoPrev = *viejo;
			update(1, 0, n - 1, a, a, dato(viejoNext, num[a]), 1);
			update(1, 0, n - 1, nuevoPrev, nuevoPrev, dato(nuevoNext, b), 1);
			update(1, 0, n - 1, viejoPrev, viejoPrev, dato(a, num[a]), 1);

			update(1, 0, n - 1, a, a, dato(nuevoNext, b), 0);
			if(nuevoPrev != -inf) 
				update(1, 0, n - 1, nuevoPrev, nuevoPrev, dato(a, b), 0);
			if(viejoPrev != -inf)
				update(1, 0, n - 1, viejoPrev, viejoPrev, dato(viejoNext, num[a]), 0);

			assert(lista[ mapea(num[a]) ].find(a) != lista[ mapea(num[a]) ].end());
			lista[ mapea(num[a]) ].erase(a);
			num[a] = b;
			lista[ mapea(num[a]) ].insert(a);
		}
	}
	return 0;
}

