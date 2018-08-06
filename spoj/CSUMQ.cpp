#include <iostream>
#include <vector>

using namespace std;

struct SegmentTree{
	SegmentTree * left, * right;
	int start, end;
	int value;

	SegmentTree(int s, int e){
		start = s;
		end = e;
		left = right = NULL;
		value = 0;
	}
};

void construir(SegmentTree *& ST, vector<int> & A, int start, int end){
	if(start == end){
		ST = new SegmentTree(start, start);
		ST->value = A[start];
	}else{
		int mitad = (start + end) / 2;
		ST = new SegmentTree(start, end);
		construir(ST->left, A, start, mitad);
		construir(ST->right, A, mitad + 1, end);
		ST->value = ST->left->value + ST->right->value;
	}
}

int query(SegmentTree * ST, int start, int end){
	if(end < ST->start || ST->end < start){
		return 0;
	}else if(start <= ST->start && ST->end <= end){
		return ST->value;
	}else{
		return query(ST->left, start, end) + query(ST->right, start, end);
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	int N, Q;
	int start, end;
	cin >> N;
	vector<int> A(N);
	for(int i = 0; i < N; ++i){
		cin >> A[i];
	}
	SegmentTree * ST = NULL;
	construir(ST, A, 0, N - 1);
	cin >> Q;
	for(int i = 0; i < Q; ++i){
		cin >> start >> end;
		cout << query(ST, start, end) << "\n";
	}
	return 0;
}