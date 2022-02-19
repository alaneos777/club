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
 
const int MX = 8008;
int n, a[MX], to[MX];
ll dp1[2][MX], dp2[2][MX], mx[MX], mn[MX];
 
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		
		for (int j = i - 1; j >= 1; j--)
			if (a[j] > a[i]) {
				to[i] = j;
				break;
			}
	}
	
	int x = 0, y = 1 - x, maxi = 0;
	for (int i = 1; i <= n; i++) {
		maxi = max(maxi, a[i]);
		dp1[y][i] = dp2[y][i] = maxi;
	}
	
	cout << maxi << " " << maxi << endl;
	
	forn (j, n - 1) {
		for (int i = 1; i <= n; i++) {
			mn[i] = 1e18;
			mx[i] = -1e18;
		}
		
		for (int i = 1; i <= n; i++) {
			dp1[x][i] = 1e18;
			dp2[x][i] = -1e18;
			
			int t = to[i];
			for (int k = t ? t : 1; k < i; k += k & -k) {
				if (dp1[x][i] > mn[k]) dp1[x][i] = mn[k];
				if (dp2[x][i] < mx[k]) dp2[x][i] = mx[k];
			}
			
			dp1[x][i] += a[i];
			dp2[x][i] += a[i];
			
			if (t) {
				if (dp1[x][i] > dp1[x][t]) dp1[x][i] = dp1[x][t];
				if (dp2[x][i] < dp2[x][t]) dp2[x][i] = dp2[x][t];
			}
			
			for (int k = i; k > 0; k -= k & -k) {
				if (mn[k] > dp1[y][i]) mn[k] = dp1[y][i];
				if (mx[k] < dp2[y][i]) mx[k] = dp2[y][i];
			}
		}
		
		cout << dp1[x][n] << " " << dp2[x][n] << endl;
		swap(x, y);
	}
	
	return 0;
}