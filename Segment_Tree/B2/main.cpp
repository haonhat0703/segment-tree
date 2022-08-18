/*
	*** DE BAI:
	Cho mot tap hop rong, lan luot thuc hien N thao tac. Co hai loai thao tac sau: 
		1) Co dang (1 x): them so x vao tap hop.
		2) Co dang (2 x): loai bo x ra khoi tap hop (luon co x trong tap hop de loai bo).
	 Sau khi thuc hien moi thao tac, hay dua ra uoc chung lon nhat cua tap nay.

						INPUT					OUTPUT
						6						
						1 8						8
						1 12					4
						1 10					2
						1 8						2	
						2 8						2
						2 8						2
*/

// cai dat bai toan bang cay IT

#include <iostream>
#include <unordered_map>
#include <stack>

using namespace std;

const int N = int(1e6);

unordered_map <int, stack<int>> q;// q <x,arr> quan li mang vi tri xuat hien cua gia tri x 

int tree[N];

int gcd(int a, int b)// ham tim uoc chung lon nhat cua a va b
{
	if (a == 0) return b;
	if (b == 0) return a;
	if (a % b == 0) return b;
	return gcd(b, a % b);
}

void update(int id, int l, int r, int idx, int key)
// ham cap nhat gia tri key cho vi tri idx trong mang quan li boi id
{
	if (idx < l || idx > r) return;// vi tri can cap nhat ngoai doan dang xet => thoat

	if (l == r) {// da tim ra vi tri can thay doi gia tri (l = r = idx)
		tree[id] = key;// cap nhat lai cay dang quan li khoang nay
		return;
	}

	//chua tim ra vi tri => xuong duoi tiep tuc tim

	int mid = (l + r) / 2;
	update(id * 2, l, mid, idx, key);// trai
	update(id * 2 + 1, mid + 1, r, idx, key);// phai

	// di nguoc len tren cap nhat lai theo con duoi

	tree[id] = gcd(tree[id * 2], tree[id * 2 + 1]);// cap nhat lai cay cha dua tren con trai, phai  
}

int main()
{
	int n, tt, x;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> tt >> x;
		if (tt == 1) {//thao tac 1
			q[x].push(i);// them vi tri xuat hien cua x vao stack
			update(1, 1, n, i, x);// update them vi tri moi cho x trong cay 
		}
		else {
			int ans = q[x].top();// lay gia tri xuat hien dau cua gia tri x trong stack
			q[x].pop();// lay ra thi loai luon ra khoi stack

			update(1, 1, n, ans, 0);// cap nhat vi tri do co gia tri bang 0 vi gcd (0, x) = x => coi nhu loai di gia tri nay
		}

		cout << tree[1] << endl;// dinh cua cay IT se luon la uoc chung lon nhat cua tap hop hien tai
	}
	return 0;
}
