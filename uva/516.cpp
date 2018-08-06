#include <bits/stdc++.h>
using namespace std;

typedef long long int ull;

ull exp_bin(ull a, ull b){
	ull ans = 1;
	while(b){
		if(b & 1) ans *= a;
		b >>= 1;
		a *= a;
	}
	return ans;
}

string to_str(ull n){
	stringstream ss;
	ss << n;
	return ss.str();
}

void factorizar(ull n){
	stack<string> pila;
	for(ull i = 2; i <= sqrt(n); ++i){
		if(n % i == 0){
			ull pot = 0;
			while(n % i == 0){
				n /= i;
				++pot;
			}
			pila.push(to_str(i) + " " + to_str(pot));
		}
	}
	if(n > 1){
		pila.push(to_str(n) + " 1");
	}
	bool primero = true;
	while(!pila.empty()){
		if(primero){
			primero = false;
		}else{
			cout << " ";
		}
		cout << pila.top();
		pila.pop();
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	string linea;
	ull pi, ei;
	while(getline(cin, linea) && linea != "0"){
		stringstream ss;
		ss << linea;
		ull x = 1;
		while(ss >> pi >> ei){
			x *= exp_bin(pi, ei);
		}
		factorizar(x - 1);
		cout << "\n";
	}
	return 0;
}