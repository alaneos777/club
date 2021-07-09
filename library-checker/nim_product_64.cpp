#include <bits/stdc++.h>
using namespace std;

int three[15];
int two_three[64];
int inv_two_three[800];
int lowest_2[800];

int getPosLowest2(int n){
	int i = 0;
	while(n){
		if(n % 3 == 2) return i;
		n /= 3;
		i++;
	}
	return -1;
}

int transform(int k){
	int ans = 0;
	int i = 0;
	while(k){
		if(k & 1) ans += three[i];
		k >>= 1;
		i++;
	}
	return ans;
}

auto getPos(uint64_t a){
	bitset<740> ans;
	int i = 0;
	while(a){
		if(a & 1) ans.flip(two_three[i]);
		a >>= 1;
		i++;
	}
	return ans;
}

uint64_t prod(uint64_t a, uint64_t b){
	auto P = getPos(a);
	bitset<740> prod;
	for(int i = 0; i < 64; ++i){
		if(b & (1llu << i)){
			prod ^= P << two_three[i];
		}
	}
	uint64_t ans = 0;
	for(int h = 739; h >= 0; --h){
		if(!prod[h]) continue;
		prod.flip(h);
		if(inv_two_three[h] != -1){
			ans ^= 1llu << inv_two_three[h];
		}else{
			int j = lowest_2[h];
			assert(j != -1);
			int u = h - three[j];
			int v = h - ((three[j+1] + 1) >> 1);
			prod.flip(u);
			prod.flip(v);
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	three[0] = 1;
	for(int i = 1; i < 15; ++i){
		three[i] = three[i-1] * 3;
	}
	memset(inv_two_three, -1, sizeof(inv_two_three));
	for(int i = 0; i < 64; ++i){
		two_three[i] = transform(i);
		inv_two_three[two_three[i]] = i;
	}
	for(int i = 0; i < 800; ++i){
		lowest_2[i] = getPosLowest2(i);
	}
	int t;
	cin >> t;
	while(t--){
		uint64_t a, b;
		cin >> a >> b;
		cout << prod(a, b) << "\n";
	}
	return 0;
}