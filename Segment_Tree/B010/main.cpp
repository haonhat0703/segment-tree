/*
	DE BAI:
	Cho day so a gom n phan tu (phan tu dau tien a1). Chung ta co 2 thao tac tren day:
		1) (0 u x): Thay doi a[u] = x.
		2) (1 u v): Tim mot cap chi so phan biet trong doan [u, v] thoa man tong 2 so tai 2 vi tri do lon nhat.

							INPUT							OUTPUT
							5								7
							1 2 3 4 5						9
							6								11
							1 2 4							12
							1 2 5
							0 1 6
							1 1 5
							0 1 7
							1 1 5 
*/

#include <iostream>
#include <math.h>

const int N = int(1e6);// so phan tu cua mang (toi da)
const int MIN_INT = -99999999;// gia tri am vo cung (ta mac dinh nhu vay)
typedef long long ll;// dinh nghia lai long long cho ngan

ll treeM[N], treem[N], t1, t2;
// treeM quan li thong tin so lon nhat cua doan dang quan li, treem quan li so lon thu hai cua doan
// t1 la ket qua khi tim so lon nhat cua doan, t2 la so lon thu hai cua doan khi thuc hien ham get => kq la t2 + t1   

using namespace std;

void update(int id, int l, int r, int idx, ll key)
// ham gan gia tri cua a[idx] = key, tu do cap nhat lai treeM va treem
{
	if (idx < l || r < idx) return;// idx khong nam trong doan [l, r] => thoat 
	if (l == r) {// neu da den la => l == r == idx
		treeM[id] = key; // vi la la nen chi co mot gia tri => treeM se la gia tri nay luon 
		treem[id] = MIN_INT;// vi la la nen chi co mot gia tri duy nhat => khong tim duoc so lon thu hai, ta mac dinh la -oo de thao tac tinh lai khong bi loi  
		return;// thoat
	}

	//chua den la => ta di xuong phia con duoi

	int mid = (l + r) / 2;
	update(id * 2, l, mid, idx, key);// trai
	update(id * 2 + 1, mid + 1, r, idx, key);// phai

	// tinh treeM va treem theo hai con trai phai vua tinh truoc do, khi nay node nay chua nhan gia tri gi ca!!! 

	if (treeM[id * 2] >= treeM[id * 2 + 1]) {//neu node trai la max
		treeM[id] = treeM[id * 2];// gan lai max la gia tri node trai
		treem[id] = max(treem[id * 2], treeM[id * 2 + 1]);// tinh max2 dua vao max (max2 trai, max phai)
	}
	else {// tuong tu nhu tren nhung voi node phai
		treeM[id] = treeM[id * 2 + 1];
		treem[id] = max(treem[id * 2 + 1], treeM[id * 2]);
	}
}

void get(int id, int l, int r, int u, int v)
// ham lay ra gia tri lon nhat va lon thu hai cua doan u->v, kq tra ve ll la t1 va t2  
{
	if (v < l || r < u) return;// doan dang xet khong giao voi [u, v] => khong lam gi ca
	if (treeM[id] <= t2) return;// max cua doan dang xet lai be hon t2 => co di xuong cung khong tim duoc gi ca => thoat
	//day la dieu kien tang toc do cho bai toan

	if (u <= l && r <= v) {// doan dang xet la con cua [u, v] => ta tinh lai t1 va t2
		if (treeM[id] >= t1) {
			t2 = max(t2, max(t1, treem[id]));
			t1 = treeM[id];
		}
		else t2 = max(t2, treeM[id]);
		return;// thoat
	}

	// la doan giao => di xuong con duoi de tim tiep

	int mid = (l + r) / 2;
	get(id * 2, l, mid, u, v);// trai
	get(id * 2 + 1, mid + 1, r, u, v);// phai
}

int main()
{
	int n;
	ll x;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		update(1, 1, n, i, x);
	}

	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int tt, u, v;
		cin >> tt >> u >> v;
		if (tt == 0)
			update(1, 1, n, u, v);
		else {
			t1 = t2 = MIN_INT;
			get(1, 1, n, u, v);
			cout << 1LL * (t1 + t2) << endl;
		}
	}
	return 0;
}