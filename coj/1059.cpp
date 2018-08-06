#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	while(cin >> n && n){
		int n0 = n;
		int ones = 0;
		stringstream ss;
		do{
			if(n & 1) ++ones;
			ss << (n & 1);
			n >>= 1;
		}while(n);
		string bin = ss.str();
		reverse(bin.begin(), bin.end());
		cout << "The parity of " << bin << " is " << ones << " (mod 2).\n";
	}
	return 0;
}