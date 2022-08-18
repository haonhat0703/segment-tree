/*
	DE BAI:
	Co n hop keo, hop thu i co Ai vien va tat ca m nguoi lan luot toi an. Nguoi thu i se chi an keo o nhung hop co so luong con lai khong it
	hon Ti chiec va se an o nhung hop nay, moi hop mot vien. Hay xac dinh so keo tung nguoi an.
	
							INPUT							OUTPUT
							3								3
							3 1 1							1	
							2
							1 2
	
	Y TUONG: xay dung cay it quan li min max cua doan, khi lay den Ti ta tim min doan (1->n) thoa min >= Ti => lay keo doan nay duoc,
	ket hop lazy danh dau la lay 1 tu doan nay, de tang thoi gian chay ta de y khi max doan < Ti => di xuong nua cung khong tim duoc min >= Ti
	=>thoat, thuat toan nay con cham (su dung BIT de co toc do xu li tot hon, ta coi day la mot bai luyen tap thui nhe!!! ><)
	!De co thoi gian xu li nhanh ta nen sap xep day Ai ban dau theo thu tu tang hoac giam.
*/

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
const int N = int(1e6);
typedef long long ll;

ll tree[N], lazy[N], treeM[N], a[N];// tree quan li min doan, treeM quan li max doan

void build(int id, int l, int r, int idx, ll key)
// ham xay dung cay IT voi gia tri key ban dau cho cac la
{
	if (idx < l || r < idx) return;// doan dang xet khong chua idx => thoat
	if (l == r) return tree[id] = key, treeM[id] = key, void();//la la => min = max = key

	//di xuong duoi tim la

	int mid = (l + r) / 2;
	build(id * 2, l, mid, idx, key);//trai
	build(id * 2 + 1, mid + 1, r, idx, key);//phai

	tree[id] = min(tree[id * 2], tree[id * 2 + 1]);// tinh min cha tu hay nut con
	treeM[id] = max(treeM[id * 2], treeM[id * 2 + 1]);// tinh max cha tu hai nut con
}

void down(int id)
// lazy dua gia tri xuong con duoi 
{
	tree[id * 2] += lazy[id];//tru di so keo da lay ra tu doan  => max va min deu giam 1
	tree[id * 2 + 1] += lazy[id];

	treeM[id * 2] += lazy[id];
	treeM[id * 2 + 1] += lazy[id];

	lazy[id * 2] += lazy[id];// nho cho con duoi de sau nay update theo lazy
	lazy[id * 2 + 1] += lazy[id];

	lazy[id] = 0;// da truyen xuong duoi => lam rong di
}

ll get (int id, int l, int r, int key)
// ham tra ve so luong cac so lon hon hoac bang key
{
	if (treeM[id] < key) return 0;//khi doan dang xet co max < key => khong co gia tri nao trong doan nay co the lay keo ra => thoat

	if (tree [id] >= key) {//doan nay co min >= key => tat ca keo trong doan nay thoa => lay ra 
		tree[id] -= 1;// da lay ra => min giam di mot
		treeM[id] -= 1;// max cung giam
		lazy[id] -= 1;// danh dau lay ra them 1 cay nho vao lazy de truyen cho cac con duoi
		return (r - l + 1);// ket qua tra ve so luong keo lay ra la do dai doan nay
	} 

	if (l == r) return 0;// neu da toi la ma van khong thoa cac dieu kien tren => thoat (khong lay duoc bat ki vien nao) => return 0

	down(id);//di xuong duoi de tim truoc khi xuong phai xu li lazy

	int mid = (l + r) / 2;
	return get(id * 2, l, mid, key) + get(id * 2 + 1, mid + 1, r, key);
	// ket qua tra ve se la tong
}

int main()
{
	int n;
	ll x;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	sort(a+1, a+1+n);//ta sort lai de sap xep cac cay keo theo thu tu nhat dinh, giup thoi gian xu li cay nhanh hon
	// thuat toan sort duoc su dung thong qua thu vien algorithms la quickSort va sap xep tang dan

	for (int i = 1; i <= n; i++)
		build(1, 1, n, i, a[i]);//xay dung cay phan doan
	
	int m;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> x;
		cout << 1LL * get(1, 1, n, x) << endl;
	}

	return 0;
}