#include <bits/stdc++.h>
using namespace std;

int main(){
	int tmp;
	string buses, str;
	cin >> tmp >> buses;
	stringstream ss(buses);
	int who = -1, ans = 1e9;
	while(getline(ss, str, ',')){
		if(str == "x") continue;
		int id = stoi(str);
		// id*t >= tmp
		// t >= ceil(tmp/id)
		int t = (tmp + id - 1) / id;
		int curr = id*t - tmp;
		if(curr < ans){
			ans = curr;
			who = id;
		}
	}
	cout << who*ans << endl;
	return 0;
}