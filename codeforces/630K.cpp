#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

ull gcd(ull a, ull b){
	ull r;
	while(b != 0){
		r = a % b;
		a = b, b = r;
	}
	return a;
}

ull mcm(ull a, ull b){
	if(a > b) return b * (a / gcd(a, b));
	else return a * (b / gcd(a, b));
}

int main(){
	ull n;
	cin >> n;
	vector<ull> divisores = {2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector< vector<ull> > power_set(1, vector<ull>());
	for(ull & divisor : divisores){
		size_t tam = power_set.size();
		for(size_t i = 0; i < tam; i++){
			vector<ull> tmp = power_set[i];
			tmp.push_back(divisor);
			power_set.push_back(tmp);
		}
	}
	ull ans = n;
	for(vector<ull> & conjunto : power_set){
		ull prod = 1;
		for(ull & v : conjunto){
			prod = mcm(prod, v);
		}
		if(conjunto.size() > 0){
			if(conjunto.size() % 2 == 1) ans -= n / prod;
			else ans += n / prod;
		}
	}
	cout << ans;
	return 0;
}