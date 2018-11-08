#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

lli gcd(lli a, lli b){
	lli r;
	while(b) r = a % b, a = b, b = r;
	return a;
}

pair<lli, lli> simplify(lli x){
	if(x == 0) return {0, 1};
	lli a = 1, b = x;
	for(lli p = 2; p <= sqrt(x); ++p){
		int pot = 0;
		while(x % p == 0){
			++pot;
			if(pot == 2){
				a *= p;
				b /= p * p;
				pot = 0;
			}
			x /= p;
		}
	}
	return {a, b};
}

struct frac{
	lli num, den;

	frac(): num(0), den(1) {}

	frac(lli x, lli y){
		lli d = abs(gcd(x, y));
		x /= d, y /= d;
		if(y < 0) x *= -1, y *= -1;
		num = x, den = y;
	}

	frac(lli x){
		num = x, den = 1;
	}

	frac operator+(const frac & f) const{
		lli d = den * (f.den/gcd(den, f.den));
		return frac(d/den*num + d/f.den*f.num, d);
	}

	frac operator-(const frac & f) const{
		lli d = den * (f.den/gcd(den, f.den));
		return frac(d/den*num - d/f.den*f.num, d);
	}

	frac operator*(const frac & f) const{
		return frac(num * f.num, den * f.den);
	}

	frac operator/(const frac & f) const{
		return frac(num * f.den, den * f.num);
	}

	pair<frac, lli> sqrt() const{
		lli a, b, c, d;
		tie(a, c) = simplify(num);
		tie(b, d) = simplify(den);
		return {frac(a, b * d), c * d};
	}
};

ostream &operator<<(ostream & os, const frac & f){
	os << f.num;
	if(f.den > 1) os << "/" << f.den;
	return os;
}

struct sqint{
	map<lli, frac> terms;

	sqint(){
		terms.clear();
	}

	sqint(const frac & q, lli r){
		if(q.num != 0) terms[r] = q;
	}

	void clean(){
		for(auto it = terms.begin(); it != terms.end(); ){
			if(it->second.num == 0) it = terms.erase(it);
			else ++it;
		}
	}

	sqint operator+(const sqint & sq) const{
		sqint New;
		New.terms = terms;
		for(auto & term : sq.terms){
			New.terms[term.first] = New.terms[term.first] + term.second;
		}
		New.clean();
		return New;
	}

	sqint operator-(const sqint & sq) const{
		sqint New;
		New.terms = terms;
		for(auto & term : sq.terms){
			New.terms[term.first] = New.terms[term.first] - term.second;
		}
		New.clean();
		return New;
	}

	sqint operator*(const sqint & sq) const{
		sqint New;
		for(auto & term1 : sq.terms){
			for(auto & term2 : terms){
				frac a = term1.second * term2.second;
				lli b = term1.first * term2.first;
				lli c, d;
				tie(c, d) = simplify(b);
				a = a * frac(c, 1);
				New.terms[d] = New.terms[d] + a;
			}
		}
		New.clean();
		return New;
	}

	sqint operator/(const sqint & sq) const{
		sqint New;
		frac a = sq.terms.begin()->second;
		lli b = sq.terms.begin()->first;
		for(auto & term : terms){
			frac c = term.second;
			lli d = term.first;
			frac e = c / a;
			frac f; lli g;
			tie(f, g) = frac(d, b).sqrt();
			New.terms[g] = New.terms[g] + e * f;
		}
		New.clean();
		return New;
	}

	sqint sqrt(){
		auto & f = terms[1];
		frac a; lli b;
		tie(a, b) = f.sqrt();
		return sqint(a, b);
	}
};

ostream &operator<<(ostream & os, const sqint & sq){
	int i = 0;
	for(auto & term : sq.terms){
		auto & f = term.second;
		if(i) os << " + ";
		if(term.first == 1){
			os << f;
		}else{
			if(f.num == 1 && f.den == 1) os << "sqrt(";
			else if(f.num == -1 && f.den == 1) os << "-sqrt(";
			else os << f << "*sqrt(";
			os << term.first << ")";
		}
		i++;
	}
	if(i == 0) os << "0";
	return os;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string ins;
	lli n;
	stack<sqint> S;
	while(cin >> ins && ins != "stop"){
		if(ins == "push"){
			cin >> n;
			S.emplace(n, 1);
		}else if(ins == "add"){
			auto x1 = S.top(); S.pop();
			auto x2 = S.top(); S.pop();
			S.push(x2 + x1);
		}else if(ins == "sub"){
			auto x1 = S.top(); S.pop();
			auto x2 = S.top(); S.pop();
			S.push(x2 - x1);
		}else if(ins == "mul"){
			auto x1 = S.top(); S.pop();
			auto x2 = S.top(); S.pop();
			S.push(x2 * x1);
		}else if(ins == "div"){
			auto x1 = S.top(); S.pop();
			auto x2 = S.top(); S.pop();
			S.push(x2 / x1);
		}else if(ins == "sqrt"){
			auto x = S.top(); S.pop();
			S.push(x.sqrt());
		}else if(ins == "disp"){
			auto x = S.top(); S.pop();
			cout << x << "\n";
		}
	}
	return 0;
}