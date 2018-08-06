#include <bits/stdc++.h>
using namespace std;

void criba(int n, vector<bool> & es_primo){
	es_primo.resize(n + 1, true);
	es_primo[0] = es_primo[1] = false;
	for(int i = 4; i <= n; i += 2){
		es_primo[i] = false;
	}
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2){
		if(es_primo[i]){
			for(int j = i * i; j <= n; j += 2*i){
				es_primo[j] = false;
			}
		}
	}
}

int str_to_int(string str){
	int ans;
	stringstream ss(str);
	ss >> ans;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	vector<bool> es_primo;
	criba(100000, es_primo);
	string str;
	while(true){
		cin >> str;
		if(str == "0") break;
		int ans = 0;
		int len = str.size();
		bool found = false;
		for(int i = 5; i >= 1; i--){
			if(found) break;
			for(int j = 0; j < (len - i + 1); j++){
				int tmp = str_to_int(str.substr(j, i));
				if(es_primo[tmp]){
					ans = max(ans, tmp);
					found = true;
				}
			}
		}
		cout << ans << "\n";
	}
	return 0;
}