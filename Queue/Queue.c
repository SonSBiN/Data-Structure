#include "Queue.h"

Queue* QueCreate()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q) {
        q->darr = DACreate();
        q->front = -1;
        q->rear = -1;
    }
    return q;
}

int QueEmpty(const Queue* queue)
{
    return queue && queue->darr && DAGetCount(queue->darr) == 0;
}

int QueEnqueue(Queue* queue, Element e)
{
    if (queue) {
        DAAdd(queue->darr, e); // 제일 마지막에 추가
        queue->rear++;
        return 1;
    }
    return 0;
}

int QueDequeue(Queue* queue, Element* pe) 
{
    if (queue && queue->darr && pe) {
        if (DAGet(queue->darr, 0, pe)) {
            // 한 칸씩 앞으로 이동
            Element temp;
            if (queue->rear > 0) {
                for (int i = 1; i < queue->rear; i++) {
                    if (DAGet(queue->darr, i, &temp)) {
                        DAPut(queue->darr, i - 1, temp);
                    }
                }
            }
            queue->rear--;
            return 1;
        }
    }
    return 0;
}

int QueFront(const Queue* queue, Element* pe)
{
    return queue && queue->darr && pe && DAGet(queue->darr, 0, pe);
}

void QuePrint(const Queue* queue, PrintFunc func)
{
    if (queue && queue->darr) {
        DAPrint(queue->darr, func);
    }
}

void QueDestroy(Queue* queue)
{
    if (queue && queue->darr) {
        DADestroy(queue->darr);
        free(queue);
    }
}
