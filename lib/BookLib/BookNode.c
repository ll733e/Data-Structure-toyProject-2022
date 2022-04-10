#include "BookNode.h"

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
        printf("등록 ID        %d\n",     pCurrentNode->ID);
        puts("");
        pCurrentNode = pCurrentNode->next;
        nCount++;
    }
}

void insNode(   char  *inTitle, 
                char  *inAuthor, 
                char  *inISBN, 
                char  *inYear) {

    bookNode    *pNewNode;          NodeID++;
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
//void delNode(unsigned int id);
//void delList(void);