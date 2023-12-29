#include <stdio.h>
#include <string.h>
#include <stdint.h>

void printCharacters(int fromCode, int toCode) {
    for (int code = fromCode; code <= toCode; code++) {
        printf("%d - %c\n", code, (char)code);
    }
}

int main() {
    printCharacters(32, 255);

    return 0;
}