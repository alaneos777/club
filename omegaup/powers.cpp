#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
using namespace std;
typedef __int128 lli;
 
ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}
 
istream &operator>>(istream &is, __int128 & value){
	char buffer[64];
	is >> buffer;
	char *pos = begin(buffer);
	int sgn = 1;
	value = 0;
	if(*pos == '-'){
		sgn = -1;
		++pos;
	}else if(*pos == '+'){
		++pos;
	}
	while(*pos != '\0'){
		value = value * 10 + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
}

lli expBin(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli raiz(lli n, lli p){
	lli l = max((lli)floor(pow(1.0*n, 1.0 / p)) - 2, (lli)0);
	lli r = l + 4;
	cout << "(" << l << ", " << r << ")\n";
	for(lli i = l; i <= r; ++i){
		lli t = expBin(i, p);
		if(t == n) return i;
		else if(t > n) return i-1;
	}
}

lli abs(lli n){
	return (n < 0 ? -n : n);
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	vector<lli> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
	lli n;
	cin >> n;
	int p = log2(n) + 2;
	int pos = lower_bound(primes.begin(), primes.end(), p) - primes.begin();
	lli ans = 1;
	vector<lli> prods = {-1};
	for(int i = 0; i <= pos; ++i){
		int sz = prods.size();
		for(int j = 0; j < sz; ++j){
			lli nuevo = -prods[j] * primes[i];
			if(abs(nuevo) <= p){
				prods.push_back(nuevo);
			}
		}
	}
	for(int i = 1; i < prods.size(); ++i){
		lli r = raiz(n, abs(prods[i]));
		cout << " r" << abs(prods[i]) << " = " << r << "\n";
		ans = ans + (r - 1) * (prods[i] >=0 ? 1 : -1);
	}
	cout << ans << "\n";
	return 0;
}