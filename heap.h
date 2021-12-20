#ifndef HEAP_H
#define HEAP_H


#include <vector>

using std::vector;

const int DefaultSize=10;

//声明MSTEdgeNode
struct MSTEdgeNode;

template <class T, class E>
class MinHeap                              //最小堆
{
public:
    MinHeap(int sz = DefaultSize);		//构造函数
    MinHeap(E arr[], int n);		//构造函数
    ~MinHeap() { delete[] heap; }		//析构函数
    bool Insert(E& d);			//插入
    bool Remove(E& d);			//删除
    bool IsEmpty() const { return  currentSize == 0; } 	//判堆空否
    bool IsFull() const { return currentSize == maxHeapSize; } //判堆满否
    void MakeEmpty() { currentSize = 0; }	//置空堆

    void traverse(MSTEdgeNode EdgeNodes[]);//遍历
    void traverse(vector<MSTEdgeNode>& EdgeNodes);


    int size()                    //返回结点数量
    {
        return currentSize;
    }


    //运算符重载=
    bool operator =(MinHeap& c)
    {
        for(int i=0;i<c.currentSize;i++)
        {
            heap[i]=c.heap[i];

            currentSize++;//容量+1
        }
        return heap;
    }



private:
    MSTEdgeNode* heap;			       //最小堆元素存储数组
    int currentSize;		           //最小堆当前元素个数
    int maxHeapSize;		           //最小堆最大容量
    void siftDown(int start, int m);		//调整算法
    void siftUp(int start);		          	//调整算法
};



#endif // HEAP_H
