#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> arr(n), left(n), right(n);
	for(int i = 0; i < n; ++i){
		cin >> arr[i];
	}
	lli sum = 0;

	stack<int> aux;
	aux.push(n-1);
	right[n-1] = n-1;
	for(int i = n-2; i >= 0; --i){
		while(!aux.empty() && arr[i] <= arr[aux.top()]){
			aux.pop();
		}
		if(aux.empty()){
			right[i] = n-1;
		}else{
			right[i] = aux.top()-1;
		}
		aux.push(i);
	}

	aux = stack<int>();
	aux.push(0);
	left[0] = 0;
	for(int i = 1; i < n; ++i){
		while(!aux.empty() && arr[i] <= arr[aux.top()]){
			aux.pop();
		}
		if(aux.empty()){
			left[i] = 0;
		}else{
			left[i] = aux.top()+1;
		}
		aux.push(i);
	}

	for(int i = 0; i < n; ++i){
		sum += (lli)(i - left[i] + 1) * (right[i] - i + 1) * arr[i];
	}
	cout << sum << "\n";
	return 0;
}