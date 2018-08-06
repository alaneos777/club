#include <bits/stdc++.h>
using namespace std;

int S;
vector<int> freq;
int current = 0;

void add(int x){
	current += (2 * freq[x] + 1) * x;
	++freq[x];
}

void remove(int x){
	current -= (2 * freq[x] - 1) * x;
	--freq[x];
}

struct MOquery{
	int l, r, index;
	bool operator<(const MOquery & q) const{
		int c_o = l / S, c_q = q.l / S;
		if(c_o == c_q)
			return r < q.r;
		return c_o < c_q;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	freq.assign(1e6+10, 0);
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
	}
	S = ceil(sqrt(n));

	vector<MOquery> queries(q);
	for(int i = 0; i < q; ++i){
		cin >> queries[i].l >> queries[i].r;
		--queries[i].l, --queries[i].r;
		queries[i].index = i;
	}

	sort(queries.begin(), queries.end());
	vector<int> ans(q);
	int prevL = 0, prevR = -1;
	int i, j;
	for(const MOquery & q : queries){
		for(i = prevL, j = min(prevR, q.l - 1); i <= j; ++i){
			remove(arr[i]);
		}
		for(i = q.l; i <= prevL - 1; ++i){
			add(arr[i]);
		}
		for(i = max(prevR + 1, q.l); i <= q.r; ++i){
			add(arr[i]);
		}
		for(i = q.r + 1; i <= prevR; ++i){
			remove(arr[i]);
		}
		prevL = q.l, prevR = q.r;
		ans[q.index] = current;
	}
	for(int & x : ans){
		cout << x << "\n";
	}
	return 0;
}