#include <bits/stdc++.h>
using namespace std;

int lis(vector<int> & arr){
	if(arr.size() == 0) return 0;
	vector<int> aux(arr.size());
	int ans = 1;
	aux[0] = arr[0];
	for(int i = 1; i < arr.size(); ++i){
		if(arr[i] < aux[0])
			aux[0] = arr[i];
		else if(arr[i] > aux[ans - 1])
			aux[ans++] = arr[i];
		else
			aux[lower_bound(aux.begin(), aux.begin() + ans, arr[i]) - aux.begin()] = arr[i];
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	vector<int> arr(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
	}
	cout << lis(arr) << "\n";
	return 0;
}