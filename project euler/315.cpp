#include <iostream>
#include <vector>
#include <algorithm>

auto sieve(int n){
	std::vector<int> primes;
	std::vector<bool> is(n+1, true);
	for(int i = 2; i <= n; ++i){
		if(is[i]) primes.push_back(i);
		for(int p : primes){
			int d = i * p;
			if(d > n) break;
			is[d] = false;
			if(i % p == 0) break;
		}
	}
	return primes;
}

const int M = 2e7;
const auto primes = sieve(M);

const int display[10][7] = {
	{1, 1, 1, 1, 1, 1, 0},
	{0, 1, 1, 0, 0, 0, 0},
	{1, 1, 0, 1, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 1},
	{0, 1, 1, 0, 0, 1, 1},
	{1, 0, 1, 1, 0, 1, 1},
	{1, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1}
};

int next[M+1], digitSize[10], numberSize[M+1], difs[10][10];

int getDigitSum(int n){
	int ans = 0;
	while(n){
		ans += n % 10;
		n /= 10;
	}
	return ans;
}

int getLength(int n){
	int ans = 0;
	while(n){
		ans += digitSize[n % 10];
		n /= 10;
	}
	return ans;
}

int getDif(int u, int v){
	int ans = 0;
	while(u || v){
		if(v == 0){
			ans += digitSize[u % 10];
		}else{
			ans += difs[u % 10][v % 10];
		}
		u /= 10, v /= 10;
	}
	return ans;
}

int sam(int n){
	int ans = numberSize[n] * 2;
	while(n > 9){
		n = next[n];
		ans += numberSize[n] * 2;
	}
	return ans;
}

int max(int n){
	int ans = numberSize[n];
	while(n > 9){
		ans += getDif(n, next[n]);
		n = next[n];
	}
	ans += digitSize[n];
	return ans;
}

int main(){
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 7; ++j){
			digitSize[i] += display[i][j];
		}
		for(int j = 0; j < 10; ++j){
			for(int k = 0; k < 7; ++k){
				difs[i][j] += display[i][k] ^ display[j][k];
			}
		}
	}
	for(int i = 0; i <= M; ++i){
		next[i] = getDigitSum(i);
		numberSize[i] = getLength(i);
	}
	int pos = lower_bound(primes.begin(), primes.end(), (int)1e7) - primes.begin();
	int ans = 0;
	for(int i = pos; i < primes.size(); ++i){
		ans += sam(primes[i]) - max(primes[i]);
	}
	std::cout << ans << "\n";
	return 0;
}