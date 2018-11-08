#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct state{
	int sumDigits = 0, modulo = 0, digit = -1;
	state() {}
	state(int a, int b, int c): sumDigits(a), modulo(b), digit(c) {}
};

bool visited[5001][501];
state parent[5001][501];

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int d, s;
	cin >> d >> s;
	queue<state> Q;
	for(int i = 1; i <= 9; ++i){
		state init(i, i % d, i);
		Q.push(init);
		parent[i][i % d] = state(-1, -1, -1);
		visited[i][i % d] = true;
	}
	bool found = false;
	state last(-1, -1, -1);
	while(!Q.empty()){
		auto curr = Q.front(); Q.pop();
		if(curr.sumDigits == s && curr.modulo == 0){
			found = true;
			last = curr;
			break;
		}
		for(int i = 0; i <= 9; ++i){
			state New(curr.sumDigits + i, (curr.modulo * 10 + i) % d, i);
			if(New.sumDigits <= s && !visited[New.sumDigits][New.modulo]){
				Q.push(New);
				visited[New.sumDigits][New.modulo] = true;
				parent[New.sumDigits][New.modulo] = curr;
			}
		}
	}
	if(found){
		string ans = "";
		for(auto curr = last; curr.digit != -1; curr = parent[curr.sumDigits][curr.modulo]){
			ans = to_string(curr.digit) + ans;
		}
		cout << ans << "\n";
	}else{
		cout << "-1\n";
	}
	return 0;
}