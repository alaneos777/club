#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
 
const int MX = 100005;
int n, h[MX], res[MX];
vii v;
set<int> st;
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> h[i];
		v.pb({h[i], i});	
	}
	
	sort(all(v), greater<ii>());
	
	for (auto &[x, i] : v) {
		auto it = st.upper_bound(i);
		
		if (it != st.end()) {
			int j = (i + *it - 1) / 2;
			res[i + 1]++;
			res[j + 1]--;
		} else {
			res[i + 1]++;
		}
		
		if (it != st.begin()) {
			it--;
			
			int j = (i + *it + 2) / 2;
			res[j]++;
			res[i]--;
		} else {
			res[1]++;
			res[i]--;
		}
		
		st.insert(i);
	}
	
	for (int i = 1; i <= n; i++) {
		res[i] += res[i - 1];
		cout << res[i] << " ";
	}
	cout << endl;
	
	return 0;
}