#include <stdio.h>

void secret_function() {
    int reversed_hex[] = {
        0xfb, 0xa2, 0xff, 0xba, 0xff, 0xec, 0xf9, 0xbe, 0xff, 0xfb, 0xf9, 0xad, 
        0xa1, 0xec, 0xa1, 0xbf, 0xad, 0xec, 0xff, 0xa4, 0xfb, 0xec, 0xfc, 0xb8, 
        0xec, 0xa9, 0xa1, 0xfc, 0xaf, 0xfd, 0xa9, 0xbb
    };

    int length = sizeof(reversed_hex) / sizeof(reversed_hex[0]);

    for(int i = 0; i < length; i++) {
        printf("%x ", reversed_hex[i]^0xcc);
    }
    putchar('\n');
}

void echo() {
    char buffer[200];

    printf("welcome to the asm masters event\n");
    printf("\nOops, I think I revealed the flag to you. But is this really the flag? Don't forget to reverse me.\n");
    printf("\nTell me a story and then I'll tell you one\n");
    scanf("%s", buffer);
    printf("Here the story is: %s\n", buffer);
    if (buffer[0] == 0x61 && buffer[1] == 0x73 && buffer[2] == 0x6d) {
        secret_function(); 
    }
}

int main() {

    echo();
    return 0;
}
