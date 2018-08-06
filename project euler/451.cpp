#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

lli mod(lli a, lli b){
	lli r = a % b;
	if(r < 0) r += b;
	return r;
}

lli inv(lli a, lli n){
	lli r0 = a, r1 = n, ri, s0 = 1, s1 = 0, si;
	while(r1 != 0){
		si = s0 - s1 * (r0 / r1), s0 = s1, s1 = si;
		ri = r0 % r1, r0 = r1, r1 = ri;
	}
	if(s0 < 0) s0 += n;
	return s0;
}

lli exp(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli maxSum(vector<lli> & nums, lli m){
	lli sum = 0;
	lli limit = ((lli)1) << nums.size();
	for(lli i = 0; i < limit; i++){
		lli tmp = 0;
		for(int j = 0; j < nums.size(); j++){
			if((i >> j) & 1){
				tmp = mod(tmp + nums[j], m);
			}else{
				tmp = mod(tmp - nums[j], m);
			}
		}
		if(tmp != m-1) sum = max(sum, tmp);
	}
	return sum;
}

vector<lli> primos;

void criba(lli n){
	vector<bool> es_primo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(es_primo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2*i){
					es_primo[j] = false;
				}
			}
		}
	}
}

map<lli, lli> factorizar(lli n){
	map<lli, lli> f;
	for(lli & p : primos){
		if(p * p > n) break;
		if(n % p == 0){
			lli pot = 0;
			while(n % p == 0){
				n /= p;
				pot++;
			}
			f[p] = pot;
		}
	}
	if(n > 1) f[n] = 1;
	return f;
}

lli M(lli n){
	map<lli, lli> f = factorizar(n);
	vector<lli> nums, nums2;
	bool flag = false;
	for(auto & factor : f){
		lli den = exp(factor.first, factor.second);
		lli div = n / den;
		lli sum = mod(div * inv(div, den), n);
		nums.push_back(sum);
		if(factor.first == 2 && factor.second >= 3){
			nums2.push_back(mod((1 + den / 2) * sum, n));
			flag = true;
		}else{
			nums2.push_back(sum);
		}
	}
	if(flag){
		return max(maxSum(nums, n), maxSum(nums2, n));
	}
	return maxSum(nums, n);
}

int main(){
	cout << "hola\n";
	lli upper = 20000000;
	criba(sqrt(upper));
	lli sum = 0;
	lli limit;
	cin >> limit;
	for(lli n = 3; n <= limit; n++){
		sum += M(n);
	}
	cout << sum << "\n";
	return 0;
}