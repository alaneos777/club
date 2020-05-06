#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int mex(const vector<int> & a){
	int n = a.size();
	vector<bool> is(n);
	for(int ai : a){
		if(ai < n){
			is[ai] = true;
		}
	}
	for(int i = 0; i < n; ++i){
		if(!is[i]) return i;
	}
	return n;
}

const int M = 1000;
int mem[M][M];

int g(int n, int maxi){
	if(mem[n][maxi] != -1) return mem[n][maxi];
	vector<int> st;
	for(int i = 1; i <= maxi; ++i){
		if(n - i >= 0){
			st.push_back(g(n - i, 2*i));
		}
	}
	return mem[n][maxi] = mex(st);
}

const lli limit = 23416728348467685ll;

int main(){
	/*memset(mem, -1, sizeof(mem));
	lli suma = 0;
	for(int n = 1; n <= 233; ++n){
		for(int q = 1; q <= n; ++q){
			if(g(n, q)){
				cout << n << " " << q << "\n";
				suma += q;
				if(n == q){
					cout << "Suma = " << suma << "\n\n";
				}
				break;
			}
		}
	}*/

	vector<lli> F;
	lli f0 = 0, f1 = 1, fi;
	while(f0 <= limit){
		F.push_back(f0);
		fi = f0 + f1, f0 = f1, f1 = fi;
	}

	lli ans = 0;
	for(int i = 2; i < F.size(); ++i){
		lli f = F[i];
		lli cnt = 1;
		if(i+3 < F.size()){
			cnt += F[F.size() - i - 1] - 1;
		}
		ans += f * cnt;
	}
	cout << ans << "\n";
	return 0;
}