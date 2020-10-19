#include <bits/stdc++.h>
using namespace std;

uint64_t maxi = 1e18;
const int rdx = 18;
const size_t sz = 730;

struct lli{
	uint64_t d[sz];
	lli(){
		memset(d, 0, sizeof(d));
	}
	lli(uint64_t x){
		memset(d, 0, sizeof(d));
		d[0] = x;
	}
	lli operator+(const lli & p) const{
		lli res;
		uint64_t carry = 0;
		for(int i = 0; i < sz; ++i){
			res.d[i] = d[i] + p.d[i] + carry;
			carry = 0;
			while(res.d[i] >= maxi){
				res.d[i] -= maxi;
				carry++;
			}
		}
		return res;
	}
	bool operator<(const lli & p) const{
		for(int i = sz-1; i >= 0; --i){
			if(d[i] < p.d[i]) return true;
			if(d[i] > p.d[i]) return false;
		}
		return false;
	}
};

ostream &operator<<(ostream & os, const lli & n){
	int idx = 0;
	for(int i = sz-1; i >= 0; --i){
		if(n.d[i]){
			idx = i;
			break;
		}
	}
	for(int i = idx; i >= 0; --i){
		if(i != idx) os << setfill('0') << setw(rdx) << n.d[i];
		else os << n.d[i];
	}
	return os;
}

istream &operator>>(istream & is, lli & n){
	string tmp;
	is >> tmp;
	uint64_t ten = 1, acum = 0;
	int pot = 0, j = 0;
	for(int i = tmp.size()-1; i >= 0; --i){
		int d = tmp[i] - '0';
		acum += d * ten;
		ten *= 10;
		pot++;
		if(pot == rdx){
			n.d[j++] = acum;
			acum = 0;
			ten = 1;
			pot = 0;
		}
	}
	if(acum){
		n.d[j++] = acum;
	}
	return is;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<lli> fibo = {0, 1};
	for(int i = 2; i <= 60100; ++i){
		fibo.push_back(fibo[i-1] + fibo[i-2]);
	}
	int t;
	cin >> t;
	while(t--){
		lli a, b;
		cin >> a >> b;
		int x = lower_bound(fibo.begin(), fibo.end(), a) - fibo.begin();
		int y = lower_bound(fibo.begin(), fibo.end(), b) - fibo.begin();
		cout << fibo[__gcd(x, y)] << "\n";
	}
	return 0;
}