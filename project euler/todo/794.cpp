#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct SegmentTree{
	int N;
	vector<int> ST;

	SegmentTree(int N): N(N){
		ST.resize(N << 1);
	}

	void update(int i, int value){
		ST[i += N] += value;
		while(i >>= 1){
			ST[i] = ST[i << 1] + ST[i << 1 | 1];
		}
	}

	int query(int l, int r){
		int res = 0;
		for(l += N, r += N; l <= r; l >>= 1, r >>= 1){
			if(l & 1) res += ST[l++];
			if(!(r & 1)) res += ST[r--];
		}
		return res;
	}
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int aleatorio(int a, int b){
	uniform_int_distribution<int> dist(a, b);
	return dist(rng);
}

int lcm(int a, int b){
	return a / __gcd(a, b) * b;
}

bool check(vector<int> a){
	int n = a.size();
	for(int i = 1; i <= n; ++i){
		sort(a.begin(), a.begin()+i);
		for(int j = 1; j <= i; ++j){
			if(!((j-1)*n <= i*a[j-1] && i*a[j-1] < j*n)){
				cout << "!" << i << " " << j << "\n";
				return false;
			}
		}
	}
	return true;
}

int main(){
	int N;
	cin >> N;
	vector<int> a(N);

	/*iota(a.begin(), a.end(), 0);
	do{
		if(check(a)){
			for(int ai : a){
				cout << ai << " ";
			}
			cout << "\n";
			break;
		}
	}while(next_permutation(a.begin(), a.end()));
	return 0;*/

	/*for(int& ai : a){
		cin >> ai;
	}
	cout << check(a) << "\n";
	return 0;*/

	int sz = 1;
	for(int i = 1; i <= N; ++i){
		sz = lcm(sz, i);
	}

	vector<int> vals;
	for(int i = 1; i <= N; ++i){
		for(int j = 0; j < i; ++j){
			if(__gcd(i, j) == 1){
				vals.push_back(sz/i*j);
			}
		}
	}
	sort(vals.begin(), vals.end());

	lli res = 1e18;
	vector<int> x_res;
	for(int step = 1; step <= 1e7; ++step){
		SegmentTree st(sz);
		bool valid = true;
		vector<int> x(N);
		st.update(0, 1);
		for(int i = 2; i <= N; ++i){
			vector<int> options;
			int len = sz/i;
			for(int start = 0; start < sz; start += len){
				int cnt = st.query(start, start+len-1);
				if(cnt == 0){
					for(auto it = lower_bound(vals.begin(), vals.end(), start), end = upper_bound(vals.begin(), vals.end(), start+len-1); it != end; ++it){
						options.push_back(*it);
					}
				}else if(cnt > 1){
					valid = false;
					break;
				}
			}
			if(options.size() == 0){
				valid = false;
				break;
			}
			int xi = options[aleatorio(0, options.size()-1)];
			x[i-1] = xi;
			st.update(xi, 1);
		}
		if(valid){
			lli sum = 0;
			for(int xi : x){
				sum += xi;
			}
			if(sum < res){
				res = sum;
				x_res = x;
			}else if(sum == res && x < x_res){
				x_res = x;
			}
		}
	}
	cout << res << " " << res/double(sz) << "\n";
	for(int xi : x_res){
		cout << xi << " ";
	}
	cout << "\n";
	for(int xi : x_res){
		cout << xi/__gcd(xi,sz) << "/" << sz/__gcd(xi,sz) << " ";
	}
	cout << "\n";
	return 0;
}