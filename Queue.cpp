#include "Queue.h"



//���
template <class T>
bool Queue<T>::EnQueue(const T& x) 
{
    if (IsFull() == true)  
        return false;
    elements[rear] = x;
    rear = (rear + 1) % maxSize;

    return true;
}


//����
template <class T>
bool Queue<T>::DeQueue(T& x) 
{
    if (IsEmpty() == true) 
        return false;
    x = elements[front];
    front = (front + 1) % maxSize;

    return true;
}

//���ض���ͷԪ�ص�ֵ
template <class T>
bool Queue<T>::GetFront(T& x)
{
    if (IsEmpty() == true)
        return false;
    x = elements[front];
    return true;
}