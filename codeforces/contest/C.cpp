#include <bits/stdc++.h>
using namespace std;

void rotate(string & str, int a, int b){
	int sum = 0;
	for(int i = a; i <= b; i++){
		sum += str[i] - 'A';
	}
	for(int i = a; i <= b; i++){
		str[i] = (str[i] - 'A' + sum) % 26 + 'A';
	}
}

void merge(string & str, int n){
	for(int i = 0; i < n / 2; i++){
		str[i] = (str[i] + str[i + n / 2] - 2 * 'A') % 26 + 'A';
	}
}

int main(){
	string str;
	cin >> str;
	int n = str.size();
	rotate(str, 0, n / 2 - 1);
	rotate(str, n / 2, n - 1);
	merge(str, n);
	for(int i = 0; i < n / 2; i++){
		cout << str[i];
	}
	cout << "\n";
	return 0;
}