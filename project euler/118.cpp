#include <bits/stdc++.h>
using namespace std;

auto sieve(int n){
	vector<int> primes;
	vector<bool> is(n+1, true);
	is[0] = is[1] = false;
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return is;
}

const int M = 987654321;
const auto is = sieve(M);

vector<vector<int>> partir(const vector<int> & a, int pos){
	vector<vector<int>> ans;
	if(pos == a.size()) return {{}};
	int num = 0;
	for(int i = pos; i < a.size(); ++i){
		num = num * 10 + a[i];
		if(is[num]){
			vector<vector<int>> rhs = partir(a, i+1);
			for(vector<int> st : rhs){
				st.insert(st.begin(), num);
				ans.emplace_back(st);
			}
		}
	}
	return ans;
}

int main(){
	vector<int> pi(9);
	iota(pi.begin(), pi.end(), 1);
	set<vector<int>> st;
	do{
		auto conjs = partir(pi, 0);
		for(auto & conj : conjs){
			sort(conj.begin(), conj.end());
			st.insert(conj);
		}
	}while(next_permutation(pi.begin(), pi.end()));
	cout << st.size() << "\n";
	return 0;
}