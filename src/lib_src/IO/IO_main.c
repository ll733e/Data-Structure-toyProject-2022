#include <stdio.h>

int main(int argc, char* argv[]) {
    if(argc != 5) return -1;
    insNode(argv[1], argv[2], argv[3], argv[4]);
    prtNode();
}