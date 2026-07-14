#include <stdio.h>
#include <string.h>

#define MAX_QUEUE 64

typedef struct {
    int items[MAX_QUEUE];
    int head;
    int tail;
    int count;
} Queue;

void queue_init(Queue *q) {
    memset(q, 0, sizeof(Queue));
}

int queue_push(Queue *q, int value) {
    if (q->count == MAX_QUEUE) return -1;
    q->items[q->tail] = value;
    q->tail = (q->tail + 1) % MAX_QUEUE;
    q->count++;
    return 0;
}

int queue_pop(Queue *q, int *out) {
    if (q->count == 0) return -1;
    *out = q->items[q->head];
    q->head = (q->head + 1) % MAX_QUEUE;
    q->count--;
    return 0;
}

int main(void) {
    Queue q;
    queue_init(&q);

    for (int i = 0; i < 10; i++) {
        queue_push(&q, i * i);
    }

    int value;
    while (queue_pop(&q, &value) == 0) {
        printf("popped: %d\n", value);
    }

    return 0;
}
