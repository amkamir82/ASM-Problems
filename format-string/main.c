#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void test_printf(const char *format, const char *stack, int stack_size);

int main(int argc, char const *argv[])
{
    // Check arguments
    if (argc < 2) {
        puts("Pass the test number as the first argument");
        exit(1);
    }
    int test_name = atoi(argv[1]);
    // Open the input file
    char filename_buffer[32];
    sprintf(filename_buffer, "input/input%d.txt", test_name);
    FILE *input = fopen(filename_buffer, "r");
    if (input == NULL) {
        printf("Cannot find file %s\n", filename_buffer);
        exit(1);
    }
    // Read the input file and create the stack
    char stack[4 * 1024], current_line[1024], format_line[1024];
    int stack_end = 0;
    fgets(format_line, sizeof(format_line), input);
    while (!feof(input)) {
        fgets(current_line, sizeof(current_line), input);
        switch (current_line[0]) {
        case 'n':
            int64_t value = strtol(current_line + 1, NULL, 10);
            *((int64_t *) (stack + stack_end)) = value;
            stack_end += 8;
            break;
        case 's':
            char *buffer = malloc(1024);
            strcpy(buffer, current_line + 1);
            *((uint64_t *) (stack + stack_end)) = (uint64_t) buffer;
            stack_end += 8;
            break;
        default:
            printf("Invalid line identifier: %c\n", current_line[0]);
            exit(1);
        }
    }
    // Execute the things
    test_printf(format_line, stack, stack_end);
    return 0;
}
