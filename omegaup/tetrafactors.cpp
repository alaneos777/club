#include <bits/stdc++.h>
using namespace std;

const int N = 5111443;

int divs[N + 1];
void sieve(int n){
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; j += i)
			divs[j]++;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	sieve(N);
	int n;
	cin >> n;
	int cnt = 0, idx = -1;
	for(int i = 1; i <= N; ++i){
		if(divs[i] == 4) ++cnt;
		if(cnt == n){
			idx = i;
			break;
		}
	}
	cout << idx << "\n";
	return 0;
}