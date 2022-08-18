//{}[]

#include <iostream>

using namespace std;

const int N = int(1e6);

int bit[N], a[N], n;

void update(int u, int v)
{
	int idx = u;
	
	while (idx <= n) {
		bit[idx] =
	} 
}

int main()
{
	int x;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		update(i, x);
	} 
	return 0;
}