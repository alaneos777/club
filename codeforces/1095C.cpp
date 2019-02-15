#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<int> freq(32);
	int ones = 0;
	for(int i = 0; i < 31; ++i){
		if(n & (1 << i)){
			freq[i]++;
			ones++;
		}
	}
	if(ones > k){
		cout << "NO\n";
	}else{
		for(int i = 30; i >= 1; --i){
			int miss = k - ones;
			int a = freq[i];
			int delta = min(a, miss);
			int b = a - delta;
			int c = 2*(a-b);
			freq[i] = b;
			freq[i-1] += c;
			ones += delta;
			if(k == ones) break;
		}
		if(ones < k){
			cout << "NO\n";
		}else{
			cout << "YES\n";
			for(int i = 0; i < 31; ++i){
				for(int j = 0; j < freq[i]; ++j){
					cout << (1<<i) << " ";
				}
			}
			cout << "\n";
		}
	}
	return 0;
}