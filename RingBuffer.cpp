#include "RingBuffer.h"

template<class T>
RingBuffer<T>::RingBuffer(size_t size) :
    ringBuffer(std::unique_ptr<T[]>(new T[size])),
    maxSize(size)
{
    head = 0;
    tail = 0;
    full = false;
}

template<class T>
void RingBuffer<T>::push(T value)
{
    ringBuffer[head] = value;
    head = (head + 1) % maxSize;

    if (full)
    {
        tail = (tail + 1) % maxSize;
    }
    full = head == tail ? true : false;
}

template<class T>
T RingBuffer<T>::get()
{
    if (!isEmpty())
    {
        size_t tempTail = tail;
        tail = (tail + 1) % maxSize;
        full = false;
        return ringBuffer[tempTail];
    }
    return T();
}

template<class T>
void RingBuffer<T>::pop_front()
{
    if (!isEmpty())
    {
        ringBuffer[tail] = T();
        tail = (tail + 1) % maxSize;

        if (full) { full = false; }
    }
}

template<class T>
void RingBuffer<T>::pop_back()
{
    if (!isEmpty())
    {
        head = (head == 0) ? maxSize - 1 : head - 1;
        ringBuffer[head] = T();
        if (full) { full = false; }
    }
}

template<class T>
bool RingBuffer<T>::isEmpty() const
{
    return (!full && (head == tail));
}

template<class T>
bool RingBuffer<T>::isFull() const
{
    return full;
}

template<class T>
size_t RingBuffer<T>::getMaxSize() const
{
    return maxSize;
}

template<class T>
size_t RingBuffer<T>::sizeQueue() const
{
    size_t size = maxSize;

    if (!full)
    {
        if (head >= tail)
        {
            size = head - tail;
        }
        else
        {
            size = maxSize + head - tail;
        }
    }
    return size;
}
