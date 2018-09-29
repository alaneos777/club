#include <bits/stdc++.h>
using namespace std;

vector<int> lw;
void sieve(int n){
	lw.resize(n + 1, 1);
	lw[0] = lw[1] = 0;
	for(int i = 2; i <= n; ++i) lw[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lw[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lw[j] == j) lw[j] = i;
}

bool test(int n){
	int ans = 0;
	while(n > 1){
		n /= lw[n];
		ans++;
		if(ans == 3) return false;
	}
	return ans == 2;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	sieve(n);
	int ans = 0;
	for(int i = 1; i < n; ++i){
		ans += test(i);
	}
	cout << ans << "\n";
	return 0;
}