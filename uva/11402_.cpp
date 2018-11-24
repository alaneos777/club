#include <bits/stdc++.h>
using namespace std;

inline short int newAction(int oldAction){
	if(oldAction == -1) return 2;
	if(oldAction == 0) return 1;
	if(oldAction == 1) return 0;
	if(oldAction == 2) return -1;
}

int cases;
int m, n, t, q, l, r;
char c;
char cad[60];
char str[1024010];

struct SegmentTree{
	int size;

	vector<int> sum;
	vector<short int> action;
 
	void SegmentTreeRec(int pos, int l, int r){
		if(l == r) sum[pos] = str[l]-'0';
		else{
			int half = l + ((r - l) >> 1);
			SegmentTreeRec(2*pos+1, l, half);
			SegmentTreeRec(2*pos+2, half+1, r);
			sum[pos] = sum[2*pos+1] + sum[2*pos+2];
		}
	}

	SegmentTree(int n): size(n){
		int h = ceil(log2(n));
		sum.resize((1 << (h + 1)) - 1);
		action.resize((1 << (h + 1)) - 1, -1);
		SegmentTreeRec(0, 0, n - 1);
	}
 
	void propagate(int pos, int l, int r, int toDo){
		if(toDo == 0 || toDo == 1){
			sum[pos] = toDo ? r-l+1 : 0;
			if(l != r){
				action[2*pos+1] = toDo;
				action[2*pos+2] = toDo;
			}
		}else if(toDo == 2){
			sum[pos] = r-l+1 - sum[pos];
			if(l != r){
				action[2*pos+1] = newAction(action[2*pos+1]);
				action[2*pos+2] = newAction(action[2*pos+2]);
			}
		}
	}
 
	int sum_query_rec(int start, int end, int pos, int l, int r){
		if(action[pos] != -1){
			propagate(pos, l, r, action[pos]);
			action[pos] = -1;
		}
		if(end < l || r < start) return 0;
		if(start <= l && r <= end) return sum[pos];
		else{
			int half = l + ((r - l) >> 1);
			return sum_query_rec(start, end, 2*pos+1, l, half) + sum_query_rec(start, end, 2*pos+2, half+1, r);
		}
	}

	int sum_query(int start, int end){
		return sum_query_rec(start, end, 0, 0, size - 1);
	}
 
	void update_range_rec(int start, int end, int pos, int l, int r, int toDo){
		if(action[pos] != -1){
			propagate(pos, l, r, action[pos]);
			action[pos] = -1;
		}
		if(end < l || r < start) return;
		if(start <= l && r <= end) propagate(pos, l, r, toDo);
		else{
			int half = l + ((r - l) >> 1);
			update_range_rec(start, end, 2*pos+1, l, half, toDo);
			update_range_rec(start, end, 2*pos+2, half+1, r, toDo);
			sum[pos] = sum[2*pos+1] + sum[2*pos+2];
		}
	}

	void update_range(int toDo, int start, int end){
		update_range_rec(start, end, 0, 0, size - 1, toDo);
	}
};

int main(){
	scanf("%d", &cases);
	for(int caso = 1; caso <= cases; ++caso){
		n = 0;
		scanf("%d", &m);
		while(m--){
			scanf("%d %s", &t, cad);
			while(t--){
				char* pos = cad;
				while(*pos != '\0'){
					str[n++] = *pos;
					++pos;
				}
			}
		}
		str[n] = '\0';
		SegmentTree T(n);
		scanf("%d", &q);
		printf("Case %d:\n", caso);
		int query = 1;
		while(q--){
			scanf(" %c %d %d", &c, &l, &r);
			if(c == 'F'){
				T.update_range(1, l, r); //set
			}else if(c == 'E'){
				T.update_range(0, l, r); //clear
			}else if(c == 'I'){
				T.update_range(2, l, r); //flip
			}else{
				printf("Q%d: %d\n", query++, T.sum_query(l, r));
			}
		}
	}
	return 0;
}