#ifndef __IO_LARGEREAD_H__
#define __IO_LARGEREAD_H__

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

void freNode();
void prtNode();
void insNode();
//void delNode(unsigned int id);
//void delList(void);

#endif  // __IO_LARGEREAD_H__