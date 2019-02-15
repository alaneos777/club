#include <bits/stdc++.h>
using namespace std;

const int M = 1e4;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, ai;
	cin >> n;
	int x = 0, y = 0;
	vector<int> freq(M+1);
	for(int i = 0; i < n; ++i){
		cin >> ai;
		freq[ai]++;
		x = max(x, ai);
	}
	for(int d = 1; d*d <= x; ++d){
		if(x % d != 0) continue;
		int dd = x / d;
		freq[d]--;
		if(dd != d) freq[dd]--;
	}
	for(int i = M; i >= 1; --i){
		if(freq[i]){
			y = i;
			break;
		}
	}
	cout << x << " " << y << "\n";
	return 0;
}