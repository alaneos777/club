#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

vector<lli> primos;
void criba(lli n){
	vector<bool> esPrimo(n + 1, true);
	primos.push_back(2);
	lli limit = sqrt(n);
	for(lli i = 3; i <= n; i += 2){
		if(esPrimo[i]){
			primos.push_back(i);
			if(i <= limit){
				for(lli j = i * i; j <= n; j += 2 * i){
					esPrimo[j] = false;
				}
			}
		}
	}
}

int main(){
	lli m = 500500507;
	criba(7376507);
	lli ans = 1;
	set<lli> nums(primos.begin(), primos.end());
	for(int i = 1; i <= 500500; i++){
		lli p = *nums.begin();
		ans = (ans * p) % m;
		nums.erase(nums.begin());
		nums.insert(p * p);
	}
	cout << ans <<"\n";
	return 0;
}