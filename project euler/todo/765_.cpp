#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld eps = 1e-9;

const ld p = 0.6, q = 1-p;
const int N = 3;

bool check = false;
ld f(const vector<ld>& a, ld target){
	int n = a.size();
	map<ld, ld> F;
	for(int m = 0; m < (1<<n); ++m){
		ld pos = 0;
		ld prob = 1;
		for(int i = 0; i < n; ++i){
			if(m & (1<<i)){
				prob *= p;
				pos += log2l(1 + a[i]);
			}else{
				prob *= q;
				pos += log2l(1 - a[i]);
			}
		}
		F[pos] += prob;
	}
	ld ans = 0;
	for(auto[pos, prob] : F){
		if(check) cout << pos << "; " << prob << "\n";
		if(log2l(target) <= pos+eps){
			ans += prob;
		}
	}
	return ans;
}

vector<ld> arr(N), a;
ld maxi = 0;

void rec(ld target, int pos = 0){
	if(pos == N){
		ld ans = f(arr, target);
		if(ans > maxi + eps){
			maxi = ans;
			a = arr;
		}
	}else{
		for(int x = pos ? arr[pos-1]*(1<<N) : 0; x <= (1<<N); ++x){
			arr[pos] = ld(x) / ld(1<<N);
			rec(target, pos+1);
			arr[pos] = 0;
		}
	}
}

int main(){
	for(int t = 1; t <= (1<<N)+1; ++t){
		maxi = 0;
		rec(t);
		cout << t << ": max of " << maxi << " at: [";
		for(ld ai : a){
			cout << ai << " ";
		}
		cout << "]\n";
	}
	check = true;
	f({0, 0, 1}, 2);
	return 0;
}