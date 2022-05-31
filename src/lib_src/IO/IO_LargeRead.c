#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO_LargeRead.h"
#include "../types.h"

#define     locDIR      "../../../data/"       // 디렉토리
#define     oriFILE     "liblist.dat"        // 원본파일
#define     bakFILE     "liblist.bak"       // 백업파일

#if HEAD
#define     HEADSTRING  "KOREA UNIV CYBER SECURITY DATA STRUCTURES08\n"
#endif

static unsigned int     NodeID = 0;
static unsigned int     ID = 0;

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

void insNode(   char  *inTitle, char  *inAuthor, char  *inISBN, char  *inYear) {
    bookNode    *pNewNode;
    pNewNode = (bookNode*)malloc(sizeof(bookNode));

    pNewNode->ID        = NodeID;
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

void desNode(unsigned int id) {
    if(pHead == NULL)
        return;
    bookNode* cur = pHead;
    
    if(cur->ID == id) {
        pHead = cur->next;
        delNode(cur);
    }
    return;
}

void delNode(bookNode* delete) {
    free(delete);
    delete = NULL;
}

void FILELOAD() {
    char        DIR[256];
    int         test = 100;
    bookNode    BK;
    FILE        *RFP, *WFP;
    sprintf(DIR, "%s%s", locDIR, oriFILE);

    RFP = fopen(DIR, "a+");
    
    
}

int main(int argc, char* argv[]) {
//    if(argc != 5) return -1;
    FILELOAD();
    //insNode(argv[1], argv[2], argv[3], argv[4]);
    //prtNode();
}