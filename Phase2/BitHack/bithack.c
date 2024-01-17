#include <stdio.h>
#include <stdint.h>

int main() {
    uint64_t key;
    scanf("%lx", &key);

    uint64_t tmp1 = key & 0x78bceef12c97afca;

    uint64_t tmp2 = tmp1 >> 5;

    uint64_t tmp3 = tmp2 + 0x12345678;

    uint64_t tmp4 = tmp3 ^ 0x4841434B45525321;

    if(tmp4 == 0x4b81a26e56263d85){
        printf("Welldone!\n");
    }else {
        printf("Try Again!\n");
    }
    return 0;
}

