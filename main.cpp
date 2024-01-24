#include "queue.h"

int main() {
    Queue<int> myQueue;

    myQueue.Enqueue(1);
    myQueue.Enqueue(2);
    myQueue.Enqueue(3);

    myQueue.Display();

    myQueue.Dequeue();
    myQueue.Display();

    myQueue.Enqueue(4);
    myQueue.Enqueue(5);
    myQueue.Display();

    return 0;
}