 #include <bits/stdc++.h>
 using namespace std;

 int main(){
 	ios_base::sync_with_stdio(0);
 	cin.tie(0);
 	int n;
 	cin >> n;
 	if(n){
 		while((n & 1) == 0) n >>= 1;
	 	int ans = 1;
	 	for(int p = 2; p <= sqrt(n); p++){
	 		int pot = 0;
	 		while(n % p == 0){
	 			pot++;
	 			n /= p;
	 		}
	 		ans *= pot + 1;
	 	}
	 	if(n > 1) ans *= 2;
	 	cout << ans << "\n";
	 }else{
	 	cout << "0\n";
	 }
	return 0;
 }