//{}[]
/*
	https://leduythuccs.github.io/2020-07-10-Binary-Search-on-Segment-Tree/
	Bai toan 2:
	Cho mot mang cac so nguyen a co n phan tu. Co q truy van co dang:
		1) (0 i x) : gan a [i] = x.
		2) (1 k): tim i nho nhat sao cho a [i] <= k
*/
#include <iostream>
#include <math.h>

using namespace std;

const int N = int(1e6);

int tree[N];

void update(int id, int l, int r, int idx, int key)
// xay dung cay phan doan min nhu binh thuong
{
	if (idx < l || r < idx) return;

	if (l==r) {
		tree[id] = key;
		return;
	} 

	int mid = (l + r) / 2;
	update(id * 2, l, mid, idx, key);
	update(id * 2 + 1, mid + 1, r, idx, key);

	tree[id] = min(tree[id * 2], tree[id * 2 + 1]);
}

int get (int id, int l, int r, int k)
// tim va tra ve vi tri *nho nhat* ma gia tri tai do <= k
{
	if (tree[id] > k) return -1;// min doan nay lon hon gia tri dang kiem tra => khong can di xuong tiep
	if (l == r) return l;// di den la => tra ve vi tri nay 

	//la doan giao => di xuong phia duoi de co nhieu thong tin hon

	int mid = (l + r) / 2;
	if (tree[id * 2] <= k) // doan duoi trai thoa yeu cau => xuong doan duoi trai de tim ket qua, co dau bang vi uu tien vi tri la nho nhat
		return get(id * 2, l, mid, k);
	
	return get(id * 2 + 1, mid + 1, r, k);// nguoc lai thi di sang phai
}

int main()
{
	int n, x;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		update(1, 1, n, i, x);
	} 
	
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int tt;
		cin >> tt;
		if (tt == 0) {
			int index, data;
			cin >> index >> data;
			update(1, 1, n, index, data);
		}else {
			int k;
			cin >> k;
			cout << get(1, 1, n, k) << endl;
		}
	} 

	return 0;
}