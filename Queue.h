#pragma once
#include<iostream>
using namespace std;


template <class T>
class Queue
{
private:
    int rear, front;			//��β, ��ͷָ��
    T* elements; 	            //����Ԫ������	
    int maxSize;                //���Ԫ�ظ���
public:
    Queue(int sz = 10) :front(0), rear(0), maxSize(sz)
    {
        elements = new T[maxSize];
    }
    ~Queue() { delete[] elements; }
    bool EnQueue(const T& x); 	    //����
    bool DeQueue(T& x);            	//����
    bool GetFront(T& x);       		//ȡ��ͷԪ��
    void MakeEmpty() { front = rear = 0; }
    bool IsEmpty() const { return front == rear; }
    bool IsFull() const { return (rear + 1) % maxSize == front; }
    int GetSize() const
    {
        return (rear - front + maxSize) % maxSize;
    }
};


