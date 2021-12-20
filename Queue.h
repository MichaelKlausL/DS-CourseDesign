#pragma once
#include<iostream>
using namespace std;


template <class T>
class Queue
{
private:
    int rear, front;			//队尾, 队头指针
    T* elements; 	            //队列元素数组	
    int maxSize;                //最大元素个数
public:
    Queue(int sz = 10) :front(0), rear(0), maxSize(sz)
    {
        elements = new T[maxSize];
    }
    ~Queue() { delete[] elements; }
    bool EnQueue(const T& x); 	    //进队
    bool DeQueue(T& x);            	//出队
    bool GetFront(T& x);       		//取队头元素
    void MakeEmpty() { front = rear = 0; }
    bool IsEmpty() const { return front == rear; }
    bool IsFull() const { return (rear + 1) % maxSize == front; }
    int GetSize() const
    {
        return (rear - front + maxSize) % maxSize;
    }
};


