#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int pot(lli r){
	int ans = 0;
	while((1ll<<ans) <= r) ans++;
	return ans-1;
}

pair<int, int> query(lli n, lli k, lli pos){
	if(n <= 2*k+1){
		if(n%2 == 1){
			if(n != pos) return {pos%2, pos%2};
			else return {k - (n-1)/2, k - (n-1)/2};
		}else{
			if(n != pos) return {1 - pos%2, 1 - pos%2};
			else return {k - (n-2)/2, k - (n-2)/2};
		}
	}else{
		lli r = n - 2*k; //[2-3], [4-7], [8,15]
		if(r == 2){
			if(pos <= 2*k){
				if(pos%2 == 1) return {0, 0};
				else return {0, 1};
			}else{
				if(pos%2 == 1) return {0, 1};
				else return {0, 0};
			}
		}else if(r == 3){
			if(pos <= 2*k){
				if(pos%2 == 1) return {0, 0};
				else return {0, 1};
			}else if(pos == 2*k+1){
				return {0, 1};
			}else if(pos == 2*k+2){
				return {0, 0};
			}else{
				return {-1, -1};
			}
		}else{
			int x = pot(r);
			lli from = 1ll<<x, to = (1ll<<(x+1))-1;
			lli y = from/2 + 1, z = from;
			if(pos < 2*k + y){
				return {0, 1};
			}else if(2*k + y <= pos && pos <= 2*k + z){
				return {0, 0};
			}else{
				return {-1, -1};
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, m;
	cin >> n >> k >> m;
	while(m--){
		int pos;
		cin >> pos;
		auto ans = query(n, k, n+1-pos);
		cout << ans.first << " " << ans.second << "\n";
	}
	return 0;
}