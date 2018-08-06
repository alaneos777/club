#include <bits/stdc++.h>
using namespace std;

int suma(int n){
	int ans = 0;
	for(int i = 2; i <= sqrt(n); ++i){
		while(n % i == 0){
			++ans;
			n /= i;
		}
	}
	if(n > 1) ++ans;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	int maximo = 1e6;
	vector<int> sumas(maximo + 1, 0);
	for(int i = 1; i <= maximo; i++){
		sumas[i] = sumas[i - 1] + suma(i);
	}
	int n;
	while(cin >> n){
		cout << sumas[n] << "\n";
	}
	return 0;
}