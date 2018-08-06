#include <iostream>
#include <cmath>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	int ans = 1;
	for(int i = 2; i <= sqrt(n); ++i){
		int pot = 0;
		while(n % i == 0){
			n /= i;
			pot += 2;
		}
		ans *= pot + 1;
	}
	if(n > 1) ans *= 3;
	cout << ans << "\n";
}