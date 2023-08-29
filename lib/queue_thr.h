#ifndef QUEUE_THR_H
#define QUEUE_THR_H

#include <thread>


class Queue
{
    private:
        int count;

    public:
        Queue();
        ~Queue();

        const int get();
        {
            return count;
        }
} 

#endif