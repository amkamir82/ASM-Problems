#include <stdio.h>
#include <stdlib.h>

int* multiply(int arr1[], int n1, int arr2[], int n2, int* result_size) {
    *result_size = n1 + n2 + 1;
    int* ans = (int*)malloc((*result_size) * sizeof(int));
    for (int i = 0; i <= *result_size; i++) {
        ans[i] = 0;
    }

    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            ans[i + j] += arr1[i] * arr2[j];
        }
    }

    return ans;
}

int main() {
    int n1, n2;
    scanf("%d", &n1);
    int* arr1 = (int*)malloc((n1+1) * sizeof(int));
    for (int i = 0; i <= n1; i++) {
        scanf("%d", &arr1[n1-i]);
    }

    scanf("%d", &n2);
    int* arr2 = (int*)malloc((n2+1) * sizeof(int));
    for (int i = 0; i <= n2; i++) {
        scanf("%d", &arr2[n2-i]);
    }

    int result_size;
    int* result = multiply(arr1, n1, arr2, n2, &result_size);

    int sum = n1 + n2;
    for (int i = result_size - 1; i > 0; i--) {
        int power = result_size - 1 - i;
        if (result[i] > 0) {
            printf("+%dx^%d", result[i], sum - power);
        } else {
                printf("%dx^%d", result[i], sum - power);
        }
    }

    if (result[0] > 0) {
            printf("+%d", result[0]);
    } else {
            printf("%d", result[0]);
    }

    free(arr1);
    free(arr2);
    free(result);

    return 0;
}
