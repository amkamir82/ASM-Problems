#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

double get_multiplier(double a) {
    switch (rand() % 3) {
    case 0:
        return a;
    case 1:
        return -a;
    case 2:
        return 0;
    }
} 

double generate_random_double() {
    double result = 0;
    double init = 1;
    for (int i = 0; i < 25; i++) {
        init /= 2;
        result += get_multiplier(init);
    }
    init = 1;
    for (int i = 0; i < 25; i++) {
        init *= 2;
        result += get_multiplier(init);
    }
    return result;
}

union conv {
    double   f;
    uint64_t i;
};

int main() {
    srand(time(NULL));
    system("rm -rf input output");
    system("mkdir input output");
    union conv a, b, c;
    for (int i = 0; i < 50; i++) {
        a.f = generate_random_double();
        b.f = generate_random_double();
        char operator = rand() % 2 == 0 ? '+' : '-';
        char file_buffer[50];
        sprintf(file_buffer, "input/input%d.txt", i);
        FILE *input = fopen(file_buffer, "w");
        sprintf(file_buffer, "output/output%d.txt", i);
        FILE *output = fopen(file_buffer, "w");
        fprintf(input, "%lu %lu %c", a.i, b.i, operator);
        c.f = operator == '+' ? (a.f + b.f) : (a.f - b.f);
        fprintf(output, "%lu", c.i);
        fclose(input);
        fclose(output);
        printf("%lf %c %lf = %lf\n", a.f, operator, b.f, c.f);
    }
    return 0;
}
