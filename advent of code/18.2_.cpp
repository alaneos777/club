#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	lli sum = 0;
	string expr;
	while(getline(cin, expr)){
		int pos = 0, n = expr.size();

		auto match = [&](char c){
			bool ans = (expr[pos++] == c);
			while(pos < n && expr[pos] == ' ') pos++;
			return ans;
		};

		function<lli()> E, T, F;

		E = [&](){
			lli ans = T();
			while(pos < n){
				if(expr[pos] == '*'){
					match('*');
					ans *= T();
				}else{
					break;
				}
			}
			return ans;
		};

		T = [&](){
			lli ans = F();
			while(pos < n){
				if(expr[pos] == '+'){
					match('+');
					ans += F();
				}else{
					break;
				}
			}
			return ans;
		};

		F = [&](){
			if(expr[pos] == '('){
				match('(');
				lli ans = E();
				match(')');
				return ans;
			}else if('0' <= expr[pos] && expr[pos] <= '9'){
				lli d = expr[pos]-'0';
				match(expr[pos]);
				return d;
			}
		};

		lli eval = E();
		sum += eval;
	}
	cout << sum << endl;
	return 0;
}