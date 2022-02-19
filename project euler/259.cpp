#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

struct frac{
	lli x, y;
	frac(): x(0), y(1){}
	frac(lli a): x(a), y(1){}
	frac(lli a, lli b){
		if(b < 0) a = -a, b = -b;
		lli d = __gcd(abs(a), b);
		x = a/d, y = b/d;
	}
	frac operator+(const frac& f) const{
		lli d = __gcd(y, f.y);
		return frac(x*(f.y/d) + f.x*(y/d), y*(f.y/d));
	}
	frac operator-(const frac& f) const{
		lli d = __gcd(y, f.y);
		return frac(x*(f.y/d) - f.x*(y/d), y*(f.y/d));
	}
	frac operator-() const{
		return frac(-x, y);
	}
	frac operator*(const frac& f) const{
		return frac(x*f.x, y*f.y);
	}
	frac operator/(const frac& f) const{
		return frac(x*f.y, y*f.x);
	}
	bool operator<(const frac& f) const{
		lli d = __gcd(y, f.y);
		return x*(f.y/d) < (y/d)*f.x;
	}
	bool operator==(const frac& f) const{
		return x==f.x && y==f.y;
	}
	bool isPositiveInteger() const{
		return x > 0 && y == 1;
	}
};

stack<frac> st;
set<lli> valid;

frac apply_op(const frac& lhs, char op, const frac& rhs){
	if(op == '+') return lhs + rhs;
	if(op == '-') return lhs - rhs;
	if(op == '*') return lhs * rhs;
	if(op == '/') return lhs / rhs;
	return 0;
}

void f(int digit = 1, char prev = '-'){
	if(st.size() == 1 && digit > 9){
		frac res = st.top();
		if(res.isPositiveInteger()) valid.insert(res.x);
	}else{
		if(digit <= 9){
			if(prev == '#'){
				st.top() = st.top()*10 + digit;
				f(digit + 1, '#');
				st.top() = (st.top() - digit) / 10;

				st.push(digit);
				f(digit + 1, '#');
				st.pop();
			}else{
				st.push(digit);
				f(digit + 1, '#');
				st.pop();
			}
		}
		if(st.size() >= 2){
			frac rhs = st.top(); st.pop();
			frac lhs = st.top(); st.pop();
			for(char op : {'+', '-', '*', '/'}){
				if((prev == '+' || prev == '-') && (op == '+' || op == '-')) continue;
				if((prev == '*' || prev == '/') && (op == '*' || op == '/')) continue;
				if(!(rhs == 0)){
					st.push(apply_op(lhs, op, rhs));
					f(digit, op);
					st.pop();
				}
			}
			st.push(lhs);
			st.push(rhs);
		}
	}
}

int main(){
	f();
	lli sum = 0;
	for(lli x : valid){
		sum += x;
	}
	cout << sum << "\n";
	return 0;
}