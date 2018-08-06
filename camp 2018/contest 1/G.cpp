#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int
#define forn(i, n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define psi pair<int,pii>
#define abierto first
#define cerrado second.first
#define completo second.second

using namespace std;

const int inf = 1e9;
const int MAXN = 1000001;

string s;

struct Segment {
	int l,r;
	psi ans; // abierto, cerrado, completo
	Segment *left, *right;

	Segment(int a,int b): l(a), r(b), left('\0'), right('\0'), ans(psi(0, pii(0, 0))) {}

	psi combina(psi uno, psi dos) {
		int a = uno.abierto + dos.abierto - min(uno.abierto, dos.cerrado);
		int b = uno.cerrado + dos.cerrado - min(uno.abierto, dos.cerrado);
		int c = uno.completo + dos.completo + min(uno.abierto, dos.cerrado);
		return psi(a, pii(b, c));
	}

	void build() {
		if(l == r) {
			int a = (s[l] == '(');
			int b = (s[l] == ')');
			int c = 0;
			ans = psi(a, pii(b, c));
			return;
		}
		int med = (l + r) / 2;
		left = new Segment(l, med);
		right = new Segment(med + 1, r);

		left->build();
		right->build();

		ans = combina(left->ans, right->ans);
	}

	psi query(int a,int b) {
		if(b < l || a > r) return psi(0, pii(0, 0));
		if(a <= l && r <= b) return ans;
		return combina(left->query(a, b), right->query(a, b));
	}
};

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin>>s;
	Segment *tree = new Segment(0, s.size() - 1);
	tree->build();

	int q,a,b;
	cin>>q;

	while(q--) {
		cin>>a>>b;
		a--,b--;

		cout<<tree->query(a, b).completo * 2<<endl;
	}
	return 0;
}
