#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"

typedef struct NODE {
    char        *Title[300];
    char        *Author[100];
    char        *ISBN[13];
    char        *Year[4];
    int         ID;
    struct      NODE    *next;
}   bookNode;

struct NODE    *pHead = NULL;
struct NODE    *pTail = NULL;

void freNode() {
    bookNode*   pTemp;

    while(pHead != NULL) {
        pTemp = pHead;
        pHead = pTemp->next;
        free(pTemp);
    }
}

void prtNode() {

    bookNode    *pCurrentNode = pHead;
    uint32      nCount        = 0;

    while(pCurrentNode != NULL) {
        printf("======| %s |======\n",  *pCurrentNode->Title);
        printf("저자           %s\n",    *pCurrentNode->Author);
        printf("ISBN           %s\n",   *pCurrentNode->ISBN);
        printf("발행년도       %s\n",     *pCurrentNode->Year);
        //printf("등록 ID        %d\n",     pCurrentNode->ID);
        puts("");
        pCurrentNode = pCurrentNode->next;
        nCount++;
    }
}

void insNode(   char  *inTitle, 
                char  *inAuthor, 
                char  *inISBN, 
                char  *inYear) {
    bookNode    *pNewNode;
    pNewNode = (bookNode*)malloc(sizeof(bookNode));

    pNewNode->ID        = 10;
    *pNewNode->Title    = inTitle;
    *pNewNode->Author   = inAuthor;
    *pNewNode->ISBN     = inISBN;
    *pNewNode->Year     = inYear;

    if(pHead == NULL) {
        pHead = pNewNode;
        pTail = pNewNode;
    } else {
        pTail->next = pNewNode;
        pTail = pNewNode;
    }
}
//void delNode(unsigned int id);
//void delList(void);

int main(int argc,char* argv[]) {
	if(argc!=5) return -1;

	char buf[256]={"Books.dat"};
	char record[]={"ID.dat"};
	int id;
	FILE *fp = fopen(buf,"a+b");
	FILE *ID = fopen(record,"r");

	//insNode(Title, Author, ISBN, Year);
	insNode(argv[1],argv[2],argv[3],argv[4]);
	fscanf(ID,"%d",&id);

	fprintf(fp,"%d",id);
	fclose(ID);

	id++;
	ID = fopen(record,"w");
	fprintf(ID,"%d",id);

	for(int i=1;i<5;i++){
		fwrite("/",strlen("/"),1,fp);
		fwrite(argv[i],strlen(argv[i]),1,fp);
	}
	fwrite("\n",strlen("\n"),1,fp);
	prtNode();
	fclose(fp);
}
