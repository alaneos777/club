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

struct WaveletTree{
	int lo, hi;
	WaveletTree *left, *right;
	vector<int> freq;
	vector<ll> pref; //just use this if you want sums

	//queries indexed in base 1, complexity for all queries: O(log(max_element))
	//build from [from, to) with non-negative values in range [x, y]
	//you can use vector iterators or array pointers
	WaveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y): lo(x), hi(y){
		if(from >= to) return;
		int m = (lo + hi) / 2;
		auto f = [m](int x){return x <= m;};
		freq.reserve(to - from + 1);
		freq.push_back(0);
		pref.reserve(to - from + 1);
		pref.push_back(0);
		for(auto it = from; it != to; ++it){
			freq.push_back(freq.back() + f(*it));
			pref.push_back(pref.back() + *it);
		}
		if(hi != lo){
			auto pivot = stable_partition(from, to, f);
			left = new WaveletTree(from, pivot, lo, m);
			right = new WaveletTree(pivot, to, m + 1, hi);
		}
	}

	//kth element in [l, r]
	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = freq[l - 1], rb = freq[r];
		int inLeft = rb - lb;
		if(k <= inLeft) return left->kth(lb + 1, rb, k);
		else return right->kth(l - lb, r - rb, k - inLeft);
	}

	//number of elements less than or equal to k in [l, r]
	int lessThanOrEqual(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		return left->lessThanOrEqual(lb + 1, rb, k) + right->lessThanOrEqual(l - lb, r - rb, k);
	}

	//number of elements equal to k in [l, r]
	int equalTo(int l, int r, int k){
		if(l > r || k < lo || k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = freq[l - 1], rb = freq[r];
		int m = (lo + hi) / 2;
		if(k <= m) return left->equalTo(lb + 1, rb, k);
		else return right->equalTo(l - lb, r - rb, k);
	}

	//sum of elements less than or equal to k in [l, r]
	ll sum(int l, int r, int k){
		if(l > r || k < lo) return 0;
		if(hi <= k) return pref[r] - pref[l - 1];
		int lb = freq[l - 1], rb = freq[r];
		return left->sum(lb + 1, rb, k) + right->sum(l - lb, r - rb, k);
	}
}*g;

const int MX = 1000005;
int n, q;
ll acu[MX], mx = -1e18, mn = 1e18;
vector<int> v;

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> q;
	
	for (int i = 1; i <= n; i++) {
		cin >> acu[i];
		
		v.pb(acu[i]);
		mn = min(mn, acu[i]);
		mx = max(mx, acu[i]);
		
		acu[i] += acu[i - 1];
	}
	
	g = new WaveletTree(all(v), mn - 1, mx + 1);
	
	while (q--) {
		int l, r, k;
		cin >> l >> r >> k;
		
		int res = g->kth(l, r, k);
		ll s = acu[r] - acu[l - 1] - g->sum(l, r, res);
		
		cout << res << " " << s << endl;
	}
			
	return 0;
}