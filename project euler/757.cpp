#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const lli M = 1e14;

int main(){
	vector<lli> st;
	for(lli i = 1; i*(i+1) <= M; ++i){
		lli lhs = i*(i+1);
		for(lli j = i; j*(j+1) <= M/lhs; ++j){
			st.push_back(lhs*j*(j+1));
		}
	}
	sort(st.begin(), st.end());
	st.erase(unique(st.begin(), st.end()), st.end());
	cout << st.size() << "\n";
	return 0;
}