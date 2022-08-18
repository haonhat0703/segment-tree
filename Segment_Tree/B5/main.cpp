//{}[]
/*
	DE BAI:
	Cho mot xau nhi phan do dai n. Xet 2 loai thao tac:
		1) (0 i j): Dao bit trong doan [i, j].
		2) (1 u v): Tinh so bit 1 trong doan [u, v].
	Cho m truy van.

							INPUT				OUTPUT
							5					2
							11010				4
							3
							1 2 4
							0 3 5
							1 1 5
*/

#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

const int N = int(1e6);

struct BIT {// quan li thong tin cay phan doan
	int val;// so luong cac bit dang bat trong doan dang quan li
	bool childUpdate;// false(0, mac dinh) -> khong can update con duoi, true(1) -> can cap nhat con duoi 
};

BIT tree[N];// Cay phan doan quan li

void update(int id, int l, int r, int u, int v)
// ham dao bit trong doan u -> v.
{
	if (v < l || r < u) return;// doan dang xet khong giao voi u v -> thoat

	if (u <= l && r <= v) {// doan dang xet nam trong u, v
		tree[id].val = (r - l + 1) - tree[id].val;// dao so luong bit lai = cach lay do dai doan - di cac bit dang bat
		tree[id].childUpdate = 1 - tree[id].childUpdate;// neu cac doan con duoi dang can update thi danh dau lai la khong can nua
		// vi update cua update la khong lam gi (^>^), nguoc lai thi danh dau can upadte => bieu thuc nhu tren 
		return;// thoat thoi
	} 

	int mid = (l + r) / 2;

	// la doan giao, xuong cac con duoi

	// truoc khi xuong kiem tra xem may be duoi can update khong
	if (tree [id].childUpdate) {// khi childUpdate = true => update con duoi
		tree[id * 2].val = (mid - l + 1) - tree[id * 2].val;// nhu tren voi id
		tree[id * 2].childUpdate = 1 - tree[id * 2].childUpdate;// nhu tren voi id
		
		tree[id * 2 + 1].val = (r - mid) - tree[id * 2 + 1].val;// nhu tren voi id
		tree[id * 2 + 1].childUpdate = 1 - tree[id * 2 + 1].childUpdate;// nhu tren voi id

		tree[id].childUpdate = 0;// danh dau lai la tui o duoi update rui => chilUpdate = false (0) 
	} 

	//update rui thi di xuong thoi
	update(id * 2, l, mid, u, v);//trai
	update(id * 2 + 1, mid + 1, r, u, v);//phai

	tree[id].val = tree[id * 2].val + tree[id * 2 + 1].val;
	// vi la doan giao nen ket qua la so luong bit bat ben trai + bit bat ben phai 
}

int get (int id, int l, int r, int u, int v)
// tra ve so luong bit dang bat trong doan u->v!!
{
	if (v < l || r < u) return 0;// khong lien quan gi doan dang xet => out
	if (u <= l && r <= v) return tree[id].val;// doan dang xet la con => tra lai gia tri lun

	// la doan giao, xuong con duoi
	// da xuong duoi thi kiem tra xem can update khong nhe
	int mid = (l + r) / 2;
	if (tree[id].childUpdate) {// nhu ham update!!!
		tree[id * 2].val = (mid - l + 1) - tree[id * 2].val;
		tree[id * 2].childUpdate = 1 - tree[id * 2].childUpdate;

		tree[id * 2 + 1].val = (r - mid) - tree[id * 2 + 1].val;
		tree[id * 2 + 1].childUpdate = 1 - tree[id * 2 + 1].childUpdate;

		tree[id].childUpdate = 0;
	}
	
	return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
	// vi la doan giao nen => ket qua la tong con trai va phai
}

int main ()
{
	int n;
	char ch;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> ch;
		if (ch == '1') 
			update(1, 1, n, i, i);
	} 

	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int tt, u, v;
		cin >> tt >> u >> v;

		if (tt == 0)
			update(1, 1, n, u, v);
		else
			cout << get(1, 1, n, u, v) << endl;
	} 
	return 0;
}