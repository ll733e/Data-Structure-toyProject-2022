/*
void searchall(char *searchKey) {
    //char    searchKey[256];
    Node    *curNode = pHead;
    //memset(searchKey, 0, sizeof(searchKey));
    //FILE *fp = fopen("result.txt","w");
    FILE*   RFP;
    RFP = fopen(oriFILE, "r+t");
    if(RFP == NULL) { puts("데이터 파일이 없습니다."); exit(1); }
    
    char *title,*author,*isbn,*year;
    int searchNum = 0;

    //printf("검색할 단어를 입력하세요 >> ");
    //scanf("%[^\n]s", searchKey);

    char *s1;
    puts("[ 자료구조론 8팀 라이브러리 검색 결과 ]");
    printf("\"%s\"에 대한 검색 결과입니다.\n", searchKey);
    //fprintf(fp,"\"%s\"에 대한 검색 결과입니다.\n", searchKey);
  
    title   = malloc(sizeof(curNode->book.TITLE));
    author  = malloc(sizeof(curNode->book.AUTHOR));
    isbn    = malloc(sizeof(curNode->book.ISBN));
    year    = malloc(sizeof(curNode->book.YEAR));
    
    strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
    strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
    strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
    strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));

    while(curNode != NULL) {
        //int     lenSTR;             // 길이 카운터의 버퍼 길이
        char    line[500];
        fseek(RFP, 0, SEEK_SET);

        while(!feof(RFP)) {
            fgets(line, sizeof(line), RFP);
            s1 = strtok(line, ",\t ");
            while(strcmp(s1, "\0") != 0) {
                if(strcmp(s1, searchKey) == 0) {
                    if(strcmp(curNode->book.TITLE, title) == 0 && strcmp(curNode->book.AUTHOR, author) == 0 && strcmp(curNode->book.ISBN, isbn) == 0 && strcmp(curNode->book.YEAR, year) == 0) {
                        s1 = strtok(NULL, ",\t "); if(s1 == NULL) s1 = "\0"; else deleteEndString(s1);
                        continue;
                    }
                    else {
                        searchNum++;
                        strncpy(title,curNode->book.TITLE,   sizeof(curNode->book.TITLE));
                        strncpy(author,curNode->book.AUTHOR, sizeof(curNode->book.AUTHOR));
                        strncpy(isbn,curNode->book.ISBN,     sizeof(curNode->book.ISBN));
                        strncpy(year,curNode->book.YEAR,     sizeof(curNode->book.YEAR));
                        //fprintf(fp,"%d. \"%s\"에 대한 검색 결과입니다.\n", searchNum,searchKey);
                        //fprintf(fp,"%s\n%s\n%s\n%s\n", curNode->book.TITLE,curNode->book.AUTHOR,curNode->book.ISBN,curNode->book.YEAR);
                        showSingleInfo(&(curNode->book));
                    }
                }
                s1 = strtok(NULL, ",\t "); if(s1 == NULL) s1 = "\0"; else deleteEndString(s1);
            }
            curNode = curNode->pNext;
            if(curNode == NULL) {
                break;
            }
        }
        if(searchNum == 0) {
            curNode = pHead;
            while(curNode != NULL) {
            if (strcmp(curNode->book.TITLE, searchKey) == 0||strcmp(curNode->book.AUTHOR, searchKey) == 0||strcmp(curNode->book.YEAR, searchKey) == 0||strcmp(curNode->book.ISBN, searchKey) == 0) {
                //printf("\"%s\"에 대한 검색 결과입니다.\n", searchKey);
                showSingleInfo(&(curNode->book));
                return menu();
            }
            curNode = curNode->pNext;
    }
    printf("\n\"%s\"에 대한 검색 결과가 없습니다.\n", searchKey);

    return menu();
            //printf("\n\"%s\"에 대한 검색 결과가 없습니다.\n", searchKey);
        }
    }
    printf("\n%d개의 검색 결과가 있습니다.\n", searchNum);
    fclose(RFP);
    //fclose(fp);
    free(title);    free(author);   free(isbn);     free(year);

    return menu();
}
*/