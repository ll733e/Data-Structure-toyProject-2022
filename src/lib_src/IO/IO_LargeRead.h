/*
    LARGEREAD는 책을 모아놓은 빅데이터의 입출력을 담당하는 라이브러리입니다.
*/
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
/*      Linked List      */
void    freNode();
void    prtNode();
void    insNode();
void    desNode(unsigned int id);
void    delNode(bookNode* delete);

/*      File I/O        */
void    FILELOAD();
void    FILESAVE();
void    FILEMODIFY();

#endif  // __IO_LARGEREAD_H__