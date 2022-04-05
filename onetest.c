#include <stdio.h>

int main() {
    char    *filename   = "book1";
    char    buf[256];
    /* 초기화 */
    sprintf(buf, "../../data/book/%s.json", filename);

    printf("%s", buf);
}