#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	string str[2] = {"1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679", "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"};
	vector<lli> fib = {str[0].size(), str[1].size()};
	while(fib.back() <= 1e18){
		int n = fib.size();
		fib.push_back(fib[n-1] + fib[n-2]);
	}
	fib.pop_back();

	function<lli(lli, int)> f = [&](lli pos, int n) -> int{
		if(n <= 1) return str[n][pos]-'0';
		if(pos < fib[n-2]) return f(pos, n-2);
		return f(pos-fib[n-2], n-1);
	};

	auto D = [&](lli pos) -> int{
		int n = 0;
		while(fib[n]-1 < pos) n++;
		return f(pos, n);
	};

	lli ans = 0;
	lli ten = 1, seven = 1;
	for(int n = 0; n <= 17; ++n){
		ans += ten*D((127+19*n)*seven - 1);
		ten *= 10;
		seven *= 7;
	}

	cout << ans << "\n";

	return 0;
}