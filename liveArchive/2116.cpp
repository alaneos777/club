#include <bits/stdc++.h>
using namespace std;

vector<int> Mu;
void muSieve(int n){
	Mu.resize(n + 1, -1);
	Mu[0] = 0, Mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(Mu[i])
			for(int j = 2*i; j <= n; j += i)
				Mu[j] -= Mu[i];
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	muSieve(10000);
	int n;
	vector<int> queries;
	while(cin >> n && n != -1) queries.push_back(n);
	for(int i = 0; i < queries.size(); ++i){
		cout << "M(" << queries[i] << ") = " << Mu[queries[i]] << "\n";
		if(i != (int)queries.size()-1) cout << "\n";
	}
	return 0;
}