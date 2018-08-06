#include <iostream>
#include <vector>

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	string n;
	cin >> n;
	int consecutivos = 0, ans = 0;
	vector<bool> bits(n.size() + 2, false);
	for(int i = 0; i < n.size(); ++i){
		bits[i] = (n[n.size() - i - 1] == '1');
	}
	for(int i = 0; i < bits.size(); ++i){
		if(bits[i]){
			++consecutivos;
		}else{
			if(consecutivos > 1){
				++ans;
				if(bits[i + 1]){
					consecutivos = 1;
				}else{
					++ans;
					consecutivos = 0;
				}
			}else if(consecutivos == 1){
				++ans;
				consecutivos = 0;
			}
		}
	}
	cout << ans;
	return 0;
}