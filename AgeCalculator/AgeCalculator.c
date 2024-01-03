#include<stdio.h>

int main(){

    int sYear, sMonth, sDay;
    int dYear, dMonth, dDay;

    scanf("%d %d %d", &sYear, &sMonth, &sDay);
    scanf("%d %d %d", &dYear, &dMonth, &dDay);

    int days = (dYear - sYear) * 360 + (dMonth - sMonth)*30 + dDay - sDay;; 
    int year = days / 360;
    int month = (days % 360) / 30;
    int day = days%30;

    printf("%d", days);
    return 0;
}
