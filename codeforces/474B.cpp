#include <bits/stdc++.h>
using namespace std;

int bs(int pos, vector<int> & acum){
	int left = 0, right = acum.size() - 2, mid;
	while(left <= right){
		mid = left + ((right - left) >> 1);
		if(acum[mid] < pos && pos <= acum[mid + 1]){
			return mid + 1;
		}else if(pos > acum[mid + 1]){
			left = mid + 1;
		}else{
			right = mid - 1;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, m, ai, qi;
	cin >> n;
	vector<int> acum(n + 1, 0);
	for(int i = 1; i <= n; i++){
		cin >> ai;
		acum[i] = acum[i - 1] + ai;
	}
	cin >> m;
	for(int i = 0; i < m; i++){
		cin >> qi;
		cout << bs(qi, acum) << "\n";
	}
	return 0;
}