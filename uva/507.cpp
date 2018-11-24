#include <iostream>
#include <vector>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	for(int caso = 1; caso <= t; ++caso){
		int n;
		cin >> n;
		vector<int> arr(n - 1);
		for(int & a : arr){
			cin >> a;
		}
		int max_sum = arr[0], curr_sum = arr[0];
		int curr_start = 0, curr_end = 0;
		int start = 0, end = 0;
		for(int i = 1; i < arr.size(); ++i){
			if(curr_sum + arr[i] >= arr[i]){
				++curr_end;
				curr_sum += arr[i];
			}else{
				curr_start = curr_end = i;
				curr_sum = arr[i];
			}
			if(curr_sum > max_sum){
				max_sum = curr_sum;
				start = curr_start;
				end = curr_end;
			}else if(curr_sum == max_sum){
				if(curr_end - curr_start > end - start){
					start = curr_start;
					end = curr_end;
				}else if(curr_end - curr_start == end - start){
					if(curr_start < start){
						start = curr_start;
						end = curr_end;
					}
				}
			}
		}
		if(max_sum > 0){
			cout<< "The nicest part of route " << caso << " is between stops " << start+1 << " and " << end+2 << "\n";
		}else{
			cout << "Route " << caso << " has no nice parts\n";
		}
	}
	return 0;
}