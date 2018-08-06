#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	int n, m;
	cin >> n;
	cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
	string str;
	while(n--){
		vector<int> numeros;
		int ans = 0;
		getline(cin, str);
		stringstream ss;
		ss << str;
		while(ss >> m) numeros.push_back(m);
		for(int i = 0; i < numeros.size() - 1; i++){
			for(int j = i + 1; j < numeros.size(); j++){
				ans = max(ans, __gcd(numeros[i], numeros[j]));
			}
		}
		cout << ans << "\n";
	}
	return 0;
}