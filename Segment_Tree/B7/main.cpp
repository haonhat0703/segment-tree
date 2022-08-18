/*
	DE BAI:
	Cho mang a gom n phan tu (phan tu dau tien la a [1]) . Co m thao tac, moi thao tac co 3 lua chon:
		1) (0 u v): tra ve tong cac phan tu tu (u -> v).
		2) (1 u v): gan gia tri a[u] = v.
		3) (2 u v k): tang cac gia tri tu u -> v len k don vi.

	INPUT									OUTPUT
	8
	-6 2 3 -3 10 -8 7 -4
	5						
	0 2 5									12
	2 3 6 3									5
	1 5 7									2
	0 4 8
	0 1 4
*/

// Cay IT va lazy!!!!!

#include<iostream>

using namespace std;

const int N = int(1e6);

int tree[N], lazy[N];// tree quan li tong cua doan dang quan li, lazy la tong can cong them cho cac con duoi

void down(int id, int l, int mid, int r) 
// lazy xuong duoi khi can
{
	// (id*2) quan li (l -> mid) -> do dai doan la (mid - l + 1), (id*2+1) quan li (mid + 1 -> r) -> do dai doan la (r - mid)
	tree[id * 2] += lazy[id] * (mid - l + 1);//vi moi phan tu trong doan cong them k = (do dai doan nay) * (gia tri can cong them)
	tree[id * 2 + 1] += lazy[id] * (r - mid);// tuong tu nhu (id*2)

	lazy[id * 2] += lazy[id];// them gia tri cho cac con duoi cua (id*2) can cong them !(khong nhan voi do dai doan)  
	lazy[id * 2 + 1] += lazy[id];// nhu tren
	
	lazy[id] = 0;// da dua xuong duoi thi danh dau lai la 0
}

void update1(int id, int l, int r, int idx, int key)
// ham nay gan lai gia tri cho node la tu do tinh lai tong cua cac cha dang quan li  
{
	if (idx < l || r < idx) return;//vi tri thay doi khong thuoc doan dang xet => thoat 
	if (l==r) {// (l==r==idx) => la nut la => cap nhap gia tri
		tree[id] = key;
		return;// thoat
	} 

	// di xuong duoi tim la

	int mid = (l + r) / 2;

	down(id, l, mid, r);// vi dang di xuong nen cap nhap xuong lun theo lazy de dam bao sau nay khong cong bua ay mu
	
	update1(id * 2, l, mid, idx, key);// trai
	update1(id * 2 + 1, mid + 1, r, idx, key);// phai
	
	tree[id] = tree[id * 2] + tree[id * 2 + 1];// tinh lai dua tren con trai phai
}

void update2(int id, int l, int r, int u, int v, int key)
// ham nay tang gia tri doan [u, v] len key 
{
	if (v < l || r < u) return;// doan dang xet khong giao [u, v] => thoat 
	if (u <= l && r <= v ){// doan dang xet la con cua [u, v]
		tree[id] += key * (r - l + 1); // tang gia tri tong nay len key * (do dai doan) => 
		lazy[id] += key;// luu lai tong can cong them cho cac con trai phai !(khong nhan do dai doan)
		return;// thoat
	}

	// la doan giao => di xuong de tinh

	int mid = (l + r) / 2;
	down(id, l, mid, r);// da di xuong thi tinh lai gia tri doan duoi theo lazy truoc khi di xuong 
	
	update2(id * 2, l, mid, u, v, key);//trai
	update2(id * 2 + 1, mid + 1, r, u, v, key);// phai

	tree[id] = tree[id * 2] + tree[id * 2 + 1];// tinh lai tong dua vao con duoi
}

int get (int id, int l, int r, int u, int v)
// ham tra ve tong tu u -> v
{
	if (v < l || r < u) return 0;// doan dang xet khong giao [u, v] => thoat
	if (u <= l && r <= v) return tree[id];// doan dang xet la con cua [u, v] => tra ve tong dang quan li de tinh de quy (hoac khong can)

	// la doan giao => xuong duoi de tinh tong

	int mid = (l + r) / 2;
	down(id, l, mid, r);// da di xuong thi tinh lai gia tri doan duoi theo lazy truoc khi di xuong 
	
	return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
	// ket qua la tong ben trai + ben phai
}

int main()
{
	int n, x;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		update1(1, 1, n, i, x);// cap nhat gia tri tai vi tri i la x (ban dau cay la 0 het)
	} 

	int m;
	cin >> m;// so thao tac
	for (int i = 1; i <= m; i++) {
		int tt, u, v;
		cin >> tt >> u >> v;
		if (tt == 0)
			cout << get(1, 1, n, u, v) << endl;
		else if (tt == 1) 
			update1(1, 1, n, u, v);
		else {
			int k;
			cin >> k;
			update2(1, 1, n, u, v, k);
		}
	} 
	return 0;
}