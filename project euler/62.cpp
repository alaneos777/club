#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	map<string, vector<lli>> mapa;
	for(lli i = 1; ;++i){
		string str = to_string(i*i*i);
		sort(str.begin(), str.end());
		mapa[str].push_back(i);
		if(mapa[str].size() == 5){
			lli n = mapa[str].front();
			cout << n*n*n << "\n";
			break;
		}
	}
	return 0;
}