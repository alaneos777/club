#include <bits/stdc++.h>
using namespace std;

int power(int a, int b, int m){
	int ans = 1;
	while(b){
		if(b & 1) ans = ans * a % m;
		b >>= 1;
		a = a * a % m;
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string m, n;
	while(cin >> m >> n && !(m == "0" && n == "0")){
		if(n == "0"){
			cout << "1\n";
		}else{
			if(m == "0"){
				cout << "0\n";
			}else{
				int a = m.back()-'0';
				int x2 = a%2;
				n = string("0") + n;
				int b = stoi(n.substr(n.size()-2)) % 4;
				int x5 = a%5 == 0 ? 0 : power(a%5, b, 5);
				int ans = (5*x2 + 6*x5) % 10;
				cout << ans << "\n";
			}
		}
	}
	return 0;
}