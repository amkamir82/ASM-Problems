// This code will print the correct flag for this problem
#include <stdio.h>

typedef long long ll;
const ll mod = 1000 * 1000 * 1000 + 7;

ll f[1001];

int main(void) {
	f[1] = 5;
	f[2] = 8;
	f[3] = 1;
	for (ll i = 4; i <= 1000; i++) {
		f[i] = ((2 * (i - 1) * f[i - 1]) % mod +
				(7 * (i - 2) * f[i - 2]) % mod +
				((i - 3) * f[i - 3]) % mod) % mod;
	}
	printf("%lld\n", f[1000]);
	return 0;
}
