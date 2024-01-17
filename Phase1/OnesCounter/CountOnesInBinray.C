#include<stdio.h>

int main(){
    unsigned int n;
    scanf("%d", &n);

    int k = 0; // count of ones

    while(n != 0){
      if(n%2 != 0)
        k++;
      n = n / 2;
    }

    printf("%d", k);
    return 0;
}