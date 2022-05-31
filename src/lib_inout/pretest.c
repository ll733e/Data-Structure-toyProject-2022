#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "MY NAME IS TOM|TAMASDF adfasf |adfacs"; 
    char *temp = strtok(str,"|"); 
    while (temp != NULL) {
        printf("%s\n",temp); 
        temp = strtok(NULL, "|");
    }
	
    return 0;
}