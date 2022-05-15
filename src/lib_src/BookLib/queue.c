#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

//오류 함수
void error(char *message)
{
    fprint(stderr, "%s\n", message);
    exit(1);
}

//공백 상태 검출 함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

//공백 상태 검출 함수
int is_empty(Queue Type *q)
{
    return (q->front == q->rear);
}

//포하 상태 검출 함수
int is_full(QueueType *q)
{
    return ((q->rear + ) % MAX_QUEUE_SIZE == q->front);
}

//삽입 함수
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("예약이 다 찼다");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

//삭제 함수
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("예약이 공백상태다");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}





