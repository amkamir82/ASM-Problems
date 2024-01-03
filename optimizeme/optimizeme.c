#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef long long ll;
const ll mod = 1000 * 1000 * 1000 + 7;

ll function_1(ll);
ll function_2(ll);

void disable_io_buffering____doesnt_need_to_be_reversed(void) {
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);
}


ll function_1(ll x) {
	if (x == 1) return 5;
	if (x == 2) return 8;
	if (x == 3) return 1;
	return (2ll * function_2(x - 1) + 7ll * function_2(x - 2) + function_2(x - 3)) % mod;
}

ll function_2(ll x) {
	return (x * function_1(x)) % mod;
}

int main(void)
{
	disable_io_buffering____doesnt_need_to_be_reversed();
	puts("Hi! This is the easiest problem ever!");
	printf("Just wait and I will give you the flag in...");
	sleep(1);
	puts("a million years!!!");

	printf("The flag is: ");
	int ans = function_1(1000);
	printf("%d\n", ans);
	return 0;
}