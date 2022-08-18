/*
	DE BAI:
	Cho day so a gom n phan tu (phan tu dau tien a[0]) cac phan tu ban dau deu co gia tri la 0. Co m truy van, moi truy van 2 thao tac:
		1) (0 u v): tang gia tri tu u->v len 1 don vi.
		2) (1 u v): trong khoang tu [u, v] co bao nhieu gia tri chia het cho 3.

									INPUT							OUTPUT
									4 7								4
									1 0 3							1
									0 1 2							0
									0 1 3							2
									1 0 0
									0 0 3
									1 3 3
									1 0 3
	Y TUONG: dung cay IT quan li so luong so chia cho 3 du 0, chia 3 du 1 => tu day co the tinh so luong so chia 3 du 2.
	Khi them 1 khoang [u, v] ta dua vao thong tin cay IT dang quan li doan de update 
*/

#include <iostream>

using namespace std;

const int N = int(1e6);

struct node {
	int div3, div1;
	//div3 so luong so chia 3 du 0, div1 so luong so chia 3 du 1
};

node tree[N];//cay IT
int lazy[N];//cai dat lazy

void build(int id, int l, int r)
// xay dung cay IT ban dau tat ca phan tu la 0 => luon chia het cho 3
{
	if (l==r) {// den la => gia tri la 0 => chia het cho 3 => 1
		tree[id].div3 = 1;
		return;//thoat
	}

	//di xuong duoi

	int mid = (l + r) / 2;
	build(id * 2, l, mid);// trai
	build(id * 2 + 1, mid + 1, r);// phai

	// tinh node cha theo con duoi

	tree[id].div3 = tree[id * 2].div3 + tree[id * 2 + 1].div3;
	// so luong chia het cho 3 cua node cha se tong 2 node con dang quan li
}

void down(int id, int l, int mid, int r)
// ham lazy truyen xuong duoi
{
	int a = tree[id * 2].div3, b = tree[id * 2].div1, c = tree[id * 2 + 1].div3, d = tree[id * 2 + 1].div1;
	// vi da mod 3 nen lazy chi co the nhan gia tri 0, 1, 2
	if (lazy[id]==1) {// cong 1 cho cac con duoi
		tree[id * 2] = { (mid - l + 1) - a - b, a };//(mod 3 == 0) = (mod 3 == 2), (mod 3 == 1) = (mod 3 == 0) vi cong them 1
		// (mod 3 == 2) = do dai doan - (mod 3 == 0) - (mod 3 == 1)
		lazy[id * 2] = (lazy[id * 2] + 1) % 3;//nho lazy cho con duoi

		tree[id * 2 + 1] = { (r - mid) - c - d, c };//tuong tu nhu tren
		lazy[id * 2 + 1] = (lazy[id * 2 + 1] + 1) % 3;// nho lazy cho con duoi
	}
	else if (lazy[id] == 2) {// cong 2 cho cac con duoi
		tree[id * 2] = { b, (mid - l + 1) - a - b };//(mod 3 == 0) = (mod 3 == 1), (mod 3 == 1) = (mod 3 == 2) vi cong them 2
		lazy[id * 2] = (lazy[id * 2] + 2) % 3;//nho lazy cho con duoi

		tree[id * 2 + 1] = { d, (r - mid) - c - d };//tuong tu nhu tren
		lazy[id * 2 + 1] = (lazy[id * 2 + 1] + 2) % 3;// nho lazy cho con duoi
	}
	lazy[id] = 0;// da truyen lazy xuong => lam rong nho nay
}

void update(int id, int l, int r, int u, int v)
// ham update cong 1 cho cac phan tu tu u->v
{
	if (v < l || r < u) return;//doan khong lien quan => thoat
	if (u <= l && r <= v) {// la doan con
		int a = tree[id].div3, b = tree[id].div1;
		tree[id] = { (r - l + 1) - a - b,a };// cong them 1 nen nhu ham down
		lazy[id] = (lazy[id] + 1) % 3;// nho lazy cho duoi
		return;// thoat
	}

	//xuong duoi

	int mid = (l + r) / 2;

	down(id, l, mid, r);// vi di xuong nen tren lazy xuong

	update(id * 2, l, mid, u, v);//trai
	update(id * 2 + 1, mid + 1, r, u, v);//phai

	//tinh nguoc len

	tree[id] = { tree[id * 2].div3 + tree[id * 2 + 1].div3, tree[id * 2].div1 + tree[id * 2 + 1].div1 };
}

int get(int id, int l, int r, int u, int v)
// ham tra ve so luong so chia het cho 3 trong khoang u->v
{
	if (v < l || r < u) return 0;//
	if (u <= l && r <= v) return tree[id].div3;

	int mid = (l + r) / 2;
	down(id, l, mid, r);
	return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}

int main()
{
	int n, m;
	cin >> n >> m;
	build(1, 1, n);

	for (int i = 1; i <= m; i++) {
		int tt, u, v;
		cin >> tt >> u >> v;
		u++, v++;
		if (tt == 0)
			update(1, 1, n, u, v);
		else
			cout << get(1, 1, n, u, v) << endl;
	}
	return 0;
}