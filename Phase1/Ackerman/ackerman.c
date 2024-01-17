#include <stdio.h>

long long ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return ackermann(m - 1, 1);
    } else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

int main() {
    int m, n;

    scanf("%d %d", &m, &n);

    long long result = ackermann(m, n);

    printf("%lld\n", result);

    return 0;
}
