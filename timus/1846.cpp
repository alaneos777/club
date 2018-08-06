#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n = 1e5;
int ST[2 * N];

int gcd(int a, int b){
	int r;
	while(b){
		r = a % b, a = b, b = r;
	}
	return a;
}

int query(int l, int r){
	int res = 0;
	r++;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = gcd(res, ST[l++]);
		if (r & 1) res = gcd(res, ST[--r]);
	}
	return res;
}

int update(int x, int pos){
	for (ST[pos += n] = x; pos > 1; pos >>= 1) ST[pos >> 1] = gcd(ST[pos], ST[pos ^ 1]);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int q, x, del;
	cin >> q;
	char op;
	unordered_map<int, stack<int>> positions;
	int pos = -1, count = 0;
	for(int i = 1; i <= q; i++){
		cin >> op;
		if(op == '+'){
			cin >> x;
			positions[x].push(++pos);
			update(x, pos);
			count++;
			cout << query(0, pos) << "\n";
		}else{
			cin >> x;
			update(0, positions[x].top());
			positions[x].pop();
			count--;
			if(count == 0){
				cout << "1\n";
			}else{
				cout << query(0, pos) << "\n";
			}
		}
	}
	return 0;
}