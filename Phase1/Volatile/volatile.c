#include <stdio.h>

int sum_array(int size, int array[]) {
    int sum = 0;
    for(int i = 0; i <size; i++){
        sum += array[i];
    }
    printf("%d", sum);
}

int main() {
    int size;
    scanf("%d", &size);
    int numbers[size];

	for (int i = 0; i < size; i++) numbers[i] = 0;

    char str[100];
    scanf(" %99s", str);
    char *ptr = str;

    // Inline assembly block
    __asm__(
		// Your assembly code here
    );

    sum_array(size, numbers);

    return 0;
}
