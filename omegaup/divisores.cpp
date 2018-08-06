#include <bits/stdc++.h>
using namespace std;
typedef long long int ull;

int main(){
	ios_base::sync_with_stdio(0);
	ull x;
	vector<ull> primos = {2, 3, 5, 7};
	while(cin >> x){
		for(ull & p : primos){
			if(x % p == 0){
				cout << p << " ";
			}
		}
		cout << "\n";
	}
	return 0;
}