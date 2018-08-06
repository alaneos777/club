#include <bits/stdc++.h>
using namespace std;

int S;
unordered_map<int, int> freq;
int current = 0;

void add(int x){
	++freq[x];
	if(freq[x] == x + 1)
		--current;
	else if(freq[x] == x)
		++current;
}

void remove(int x){
	--freq[x];
	if(freq[x] == x)
		++current;
	else if(freq[x] == x - 1)
		--current;
}

struct MOquery{
	int l, r, index;
	bool operator<(const MOquery & q) const{
		if(l / S == q.l / S)
			return r < q.r;
		return l / S < q.l / S;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
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