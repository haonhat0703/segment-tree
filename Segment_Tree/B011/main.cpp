/*
	Cho day so n so. 2 truy van
		1) (1 i v): gan so o vi tri i thanh gia tri v.
		2) (2 u v k): in ra so nho nhat ma lon hon bang k trong khoang u->v (khong tim duoc in -1). 

						INPUT							OUTPUT
						5 4								3
						1 5 3 4 5						-1
						2 1 3 2							2
						2 3 5 6
						1 2 2
						2 1 5 2
	Y TUONG: xay dung cay IT quan li doan con cua day so nay. thao tac mot ta xoa di gia tri hien tai va them gia tri moi vao doan tuong ung
	. thao tac 2 ta di vao tung doan tuong ung de tim gia tri thoa dk (lower_bound). su dung mutilset(mutilset tu sap xep theo gia tri tang dan,
	khi ta them mot phan tu moi vao mutilset)
*/

#include <iostream>
#include <set>
#include <algorithm>
#include <math.h>

using namespace std;

const int N = int(1e6);// so luong phan tu cua mang
const int inf = int (1e9) + 7;//gia tri oo

int n, m, a[N];
multiset <int> tree[N];// mutilset quan li doan con cua node dang giu

void build(int id, int l, int r)
// ham xay dung cay IT voi moi node quan li doan tuong ung
{
	if (l==r) {// la la => doan nay quan li gia tri al
		tree[id].insert(a[l]);// them al vao
		return;// thoat
	}

	int mid = (l + r) / 2;
	build(id * 2, l, mid);//trai
	build(id * 2 + 1, mid + 1, r);//phai

	//tinh nguoc len bang ket qua cua node con trai va phai
	// node nay la cac phan tu cua hai node con 
	tree[id] = tree[id * 2];// khoi tao la so phan tu hien tai cua node trai
	for (auto x : tree[id * 2 + 1])// voi moi phan tu node phai
		tree[id].insert(x);//ta them vao node cha
}

void update(int id, int l, int r, int idx, int old, int val)
// ham cap nhat gia tri moi cho la
{
	if (idx < l || r < idx) return;// vi tri thay doi nam ngoai doan dang xet => thoat
	if (l==r) {// da den vi tri can thay doi => la
		tree[id].clear();// vi la la nen chi chua mot phan tu => xoa rong truoc
		tree[id].insert(val);// them gia tri moi vao doan nay
		return;// thoat
	}

	int mid = (l + r) / 2;
	update(id * 2, l, mid, idx, old, val);// trai
	update(id * 2 + 1, mid + 1, r, idx, old, val);// phai

	// tinh nguoc lai cho node cha

	tree[id].erase(tree[id].find(old));// xoa di phan tu cua node la cu
	tree[id].insert(val);// them phan tu moi vao doan dang quan li
}

int get(int id, int l, int r, int u, int v, int key)
// ham tra ve ket qua theo thao tac 2
{
	if (v < l || r < u) return inf;// doan dang xet khong giao voi u v ta tra ve oo (vi dang tim min) 
	if (u <= l && r <= v) {//la doan con
		auto it = tree[id].lower_bound(key);// su dung lb de tim phan tu nho nhat lon hon hoac bang key trong mutilset
		if (it == tree[id].end()) return inf;// neu khong tim thay => tra ve inf
		return *it;// tra ve gia tri da tim duoc thoa yeu cau (lower_bound tra ve dia chi cua gia tri thoa yeu cau)
	} 

	int mid = (l + r) / 2;
	return min(get(id * 2, l, mid, u, v, key), get(id * 2 + 1, mid + 1, r, u, v, key));//tinh 
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);

	for (int i = 1; i <= m; i++) {
		int tt, u, v;
		cin >> tt >> u >> v;
		if (tt == 1) {
			update(1, 1, n, u, a[u], v);
			a[u] = v;// cap nhat lai gia tri cua mang
		} else {
			int k;
			cin >> k;
			int ans = get(1, 1, n, u, v, k);
			cout << ((ans == inf) ? -1 : ans) << endl;// neu la inf => -1 nguoc lai xuat kq vua tim duoc
			// phai dam bao khong co ket qua nao tra ve trung voi inf (nen lay gia tri cua inf rat lon xem nhu vo cung)
		}
	} 
	return 0;
}