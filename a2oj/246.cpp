#include <iostream>
#include <set>

using namespace std;

int main(){
	int t, actual;
	cin >> t;
	for(int i = 0; i < t; i++){
		set<int> S;
		for(int j = 1; j <= 10; j++){
			cin >> actual;
			S.insert(actual % 42);
		}
		cout << S.size() << "\n";
	}
	return 0;
}