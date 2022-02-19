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

const int MX = 500005;
int n, q, res[MX];
string name[MX], birth[MX];
map<string, int> mp;

void main_() {
	cin >> n;
	
	forn (i, n) {
		cin >> name[i] >> birth[i];
		
		while (mp.size() && mp.rbegin()->fi >= birth[i])
			mp.erase(mp.rbegin()->fi);
		
		if (mp.size())
			res[i] = mp.rbegin()->se;
		else
			res[i] = -1;
		
		mp[birth[i]] = i;
	}
	
	cin >> q;
	while (q--) {
		int r;
		cin >> r;
		r--;
		
		cout << "At place #" << r + 1 << ", ";
		
		if (res[r] == -1) {
			cout << "no one younger arrived before " << name[r] << endl;
		} else {
			cout << "the last younger person to arrive before " << name[r]
				 << " is " << name[res[r]] << "(#" << res[r] + 1 << ")" << endl;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	int t = 1;
	// cin >> t;
	while (t--)
		main_();
	
	return 0;
}
