#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct frac{
	lli x, y;
	frac(): x(0), y(1){}
	frac(lli a, lli b){
		lli d = __gcd(a, b);
		x = a, y = b;
	}
	frac operator+(const frac& q) const{
		return frac(x + q.x, y + q.y);
	}
	bool operator<(const frac& q) const{
		return x*q.y < q.x*y;
	}
};

string get(int p, int q){
	frac x = {p, q};
	frac l = {0, 1}, r = {1, 0};
	string s;
	while(true){
		frac m = l+r;
		if(x < m){ //left
			s += "1";
			r = m;
		}else if(m < x){ //right
			s += "0";
			l = m;
		}else{
			s += "1";
			break;
		}
	}
	reverse(s.begin(), s.end());
	return s;
}

int main(){
	string s = get(123456789, 987654321);
	int cnt = 0;
	char prev = '-';
	for(char c : s){
		if(c == prev){
			cnt++;
		}else{
			if(cnt) cout << cnt << ",";
			prev = c;
			cnt = 1;
		}
	}
	cout << cnt << "\n";
	return 0;
}