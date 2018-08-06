#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef __int128 lli;

//cout for __int128
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

//cin for __int128
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
		value = (value << 3) + (value << 1) + (*pos - '0');
		++pos;
	}
	value *= sgn;
	return is;
}

vector<int> lp;
void sieve(int n){
	lp.resize(n + 1, 1);
	lp[0] = lp[1] = 0;
	for(int i = 2; i <= n; i++) lp[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(lp[i] == i){
			for(int j = i * i; j <= n; j += 2 * i){
				if(lp[j] == j) lp[j] = i;
			}
		}
	}
}

lli Exp(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

lli S(lli n){
	lli ans = 1;
	while(n > 1){
		int a = 0;
		int p = lp[n];
		while(n % p == 0){
			n /= p;
			a++;
		}
		ans *= (1+Exp(p, 2*a+1))/(1+p);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	sieve(1e7+20);
	int t; lli n;
	cin >> t;
	while(t--){
		cin >>n;
		cout << S(n) << "\n";
	}
	return 0;
}