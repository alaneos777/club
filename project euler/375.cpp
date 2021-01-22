#include <bits/stdc++.h>
using namespace std;
using lli = long long int;

int main(){
	int n = 2e9;
	vector<int> arr(n), left(n), right(n);
	lli s = 290797;
	for(int i = 0; i < n; ++i){
		s = arr[i] = s*s % 50515093;
	}

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
		while(!aux.empty() && arr[i] < arr[aux.top()]){
			aux.pop();
		}
		if(aux.empty()){
			left[i] = 0;
		}else{
			left[i] = aux.top()+1;
		}
		aux.push(i);
	}

	lli sum = 0;
	for(int i = 0; i < n; ++i){
		sum += (lli)(i - left[i] + 1) * (right[i] - i + 1) * arr[i];
	}
	cout << sum << "\n";
	return 0;
}