#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

const int M = 12;
map<lli, lli> mem[11];
lli fact[M+1], base[10];

inline lli get(lli msk, int i){
	return msk/base[i]%(M+1);
}

inline lli put(lli msk, int i, int v){
	return msk - get(msk, i)*base[i] + v*base[i];
}

lli comb(lli msk){
	int n = 0;
	for(int i = 0; i < 10; ++i){
		n += get(msk, i);
	}
	lli ans = fact[n];
	for(int i = 0; i < 10; ++i){
		ans /= fact[get(msk, i)];
	}
	return ans;
}

int tmp[M+1];
lli Sort(lli msk){
	memset(tmp, 0, sizeof(tmp));
	for(int i = 1; i < 10; ++i){
		tmp[get(msk, i)]++;
	}
	int pos = 0;
	lli ans = get(msk, pos++);
	for(int i = 0; i <= M; ++i){
		while(tmp[i]--){
			ans = put(ans, pos++, i);
		}
	}
	return ans;
}

lli S(int pos, lli freq, int sum_freq){
	lli sorted = Sort(freq);
	if(mem[pos].count(sorted)) return mem[pos][sorted];
	lli ans = 0;
	if(pos == 10){
		lli k = comb(freq);
		if(get(freq, 0) > 0){
			k -= comb(put(freq, 0, get(freq, 0) - 1));
		}
		ans = k*(k-1)/2;
	}else if(pos == 9){
		ans = S(pos+1, put(freq, pos, M-sum_freq), M);
	}else{
		for(int xi = 0; sum_freq + xi <= M; ++xi){
			ans += S(pos+1, put(freq, pos, xi), sum_freq+xi);
		}
	}
	return mem[pos][sorted] = ans;
}

int main(){
	fact[0] = 1, base[0] = 1;
	for(int i = 1; i <= M; ++i){
		fact[i] = i * fact[i-1];
	}
	for(int i = 1; i < 10; ++i){
		base[i] = (M+1) * base[i-1];
	}
	cout << S(0, 0, 0) << "\n";
	return 0;
}