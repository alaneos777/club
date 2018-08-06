#include <bits/stdc++.h>
using namespace std;

int bs(vector<int> & marbles, int valor){
	int left = 0, right = marbles.size() - 1, mid;
	while(left <= right){
		mid = left + ((right - left) >> 1);
		if(marbles[mid] > valor){
			right = mid - 1;
		}else if(marbles[mid] < valor){
			left = mid + 1;
		}else if(left != mid){
			right = mid;
		}else{
			return mid;
		}
	}
	return -1;
}

int main(){
	ios_base::sync_with_stdio(0);
	int n, q, valor, caso = 1;
	while(cin >> n >> q){
		if(n == 0 && q == 0) break;
		vector<int> marbles(n);
		for(int i = 0; i < n; i++){
			cin >> marbles[i];
		}
		sort(marbles.begin(), marbles.end());
		cout << "CASE# " << caso << ":\n";
		for(int i = 1; i <= q; i++){
			cin >> valor;
			int index = bs(marbles, valor);
			if(index == -1){
				cout << valor << " not found\n";
			}else{
				cout << valor << " found at " << (index + 1) << "\n";
			}
		}
		caso++;
	}
	return 0;
}