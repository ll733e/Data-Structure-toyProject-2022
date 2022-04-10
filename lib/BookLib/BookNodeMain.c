#include <stdio.h>

void insNode();
void prtNode();
void freNode();

int main(   int     argc,
            char    *argv[]
) {
    //insNode("책 제목", "저자", "ISBN", 발행년도);
    if(argc != 5)   return -1;
    insNode(argv[1], argv[2], argv[3], argv[4]);
    prtNode();
    freNode();
    return 0;
}