#pragma once

#include<iostream>
#include<assert.h>
#include"MyHashMap.h"
#include"DbLinkedList.h"
#include"WUSGraph.h"
using namespace std;

//向前声明
template<class T>
struct LinkNode;

template<class T>
struct Edge;


//删除和清除有内存泄露

static const int num_prime = 24;
static const unsigned int prime_list[num_prime] = //0～4294967295  -2147483648～2147483647
{
    17,        29,
    53,        97,      193,        389,       769,
    1543,      3079,    6151,       12289,     24593,
    49157,     98317,   196613,     393241,    786433,
    1572869,   3145739, 6291469,    12582917,  25165843,
    50331653,  100663319
};

template<typename K, typename E>
struct ChainNode {        //各木桶之间同义词子表的链结点定义
    E data;                  //元素
    K key;                   //键值
    ChainNode<K, E>* link = nullptr;   //链指针

    /////////////////////////连接邻接表结点
    LinkNode<int>* conVt = nullptr;
    Edge<int>* conEd = nullptr;


    ChainNode(K k, E e) :key(k), data(e), link(nullptr) {}
    ChainNode() :link(nullptr) {}
};

template <typename K, typename E>
class MyHashTable {		     //散列表类定义
public:

    
    MyHashTable();
    MyHashTable(int initialSize);
    MyHashTable(int initialSize, double m_MaxLoadFactor);
    //如未说明设置默认值 initialSize = 16 和 MaxLoadFactor = 0.7                      O(1)

    ~MyHashTable() { delete[]ht; } 	//析构函数

    bool Search(const K& k1) const;       //在散列表中查找                           O(1)
    bool Insert(const K& k1, const E& e1);//插入e1                                   O(1)
    int Remove(const K& k1, const E& e1); //删除e1                                   O(1)
    int Remove(const K& k1);	       	  //删除键值k1对应的数据                     O(1)
    void resizeTable();
    void clear();                         //置空表                                   O(V)
    unsigned hash(K k) const;


    ////////////////////////////////////////
    void connect(K k1,LinkNode<int>* node)       //与邻接表建立连接
    {
        ChainNode<K, E>* cnode = FindPos(k1);
        cnode->conVt = node;
    }
    void connect(K k1, Edge<int>* node)         //与邻接表建立连接
    {
        ChainNode<K, E>* cnode = FindPos(k1);
        cnode->conEd = node;
    }
    LinkNode<int>* getVertex(K k1)             //返回结点指针
    {
        ChainNode<K, E>* cnode = FindPos(k1);
        if (cnode != nullptr)
            return cnode->conVt;
        else
            return nullptr;
    }
    Edge<int>* getEdge(K k1)
    {
        ChainNode<K, E>* cnode = FindPos(k1);
        if (cnode != nullptr)
            return cnode->conEd;
        else
            return nullptr;
    }


    ////////////////////////////////////////////////////////


    ChainNode<K, E>* FindPos(const K& k1);//散列
    int next_prime(unsigned int n);
    void print();
    ChainNode<K, E>** ht;   //散列表定义
    int getTableSize() { return TableSize; }
private:
    int divisor;		    //散列函数的除数(必须是质数，小于容量的最大质数)
    int TableSize;	        //当前桶数及最大桶数
    double MaxLoadFactor;   //最大散列因子
   
};

template <typename K, typename E>
inline MyHashTable<K, E>::MyHashTable()
{
    divisor = 13;
    TableSize = 16;
    MaxLoadFactor = 0.7;

    ht = new ChainNode<K, E> *[TableSize] {nullptr};//创建结点

    assert(ht != nullptr);//断言，判断存储分配成功否
}

template <typename K, typename E>
inline MyHashTable<K, E>::MyHashTable(int initialSize)
{
    TableSize = next_prime(initialSize);
    divisor = TableSize;
    MaxLoadFactor = 0.7;

    ht = new ChainNode<K, E> *[TableSize] {nullptr};//创建结点

    assert(ht != nullptr);//断言，判断存储分配成功否
}

template <typename K, typename E>
inline MyHashTable<K, E>::MyHashTable(int initialSize, double m_MaxLoadFactor)
{
    TableSize = next_prime(initialSize);
    divisor = TableSize;
    MaxLoadFactor = m_MaxLoadFactor;

    ht = new ChainNode<K, E> *[TableSize] {nullptr};//创建结点

    assert(ht != nullptr);//断言，判断存储分配成功否
}

template <typename K, typename E>
inline bool MyHashTable<K, E>::Search(const K& k1) const
{
    unsigned j = hash(k1);
    //int j = k1 % divisor; //计算散列地址
    ChainNode<K, E>* p = ht[j];

    while (p != nullptr) {
        if (k1 == p->key) {
            return true;
        }
        p = p->link;
    }
    return false;
}

//时间复杂度O(1)
template <typename K, typename E>
inline bool MyHashTable<K, E>::Insert(const K& k1, const E& e1)
{
    ChainNode<K, E>* InsertNode = new ChainNode<K, E>;
    InsertNode->data = e1;
    InsertNode->link = nullptr;
    InsertNode->key = k1;

    unsigned j = hash(k1);
    //int j = k1 % divisor; //计算散列地址
    ChainNode<K, E>* p = ht[j];

    if (Search(k1)) {  //搜索成功,先删除表中数据
        Remove(k1);
        return Insert(k1, e1);
    }
    //尾插入
    if (p == nullptr) {
        ht[j] = InsertNode;

        resizeTable();
        return true;
    }
    else {
        while (p->link) {
            p = p->link;
        }
        p->link = InsertNode;

        resizeTable();//判断负载因子是否超出最大值
        return true;
    }
    return false;
}


template <typename K, typename E>
inline int MyHashTable<K, E>::Remove(const K& k1, const E& e1)
{
    unsigned j = hash(k1);
    //int j = k1 % divisor; //计算散列地址
    ChainNode<K, E>* p = ht[j];

    if (p == nullptr) {
        return 0;
    }
    if (p->data == e1 && p->key == k1) {

        ht[j] = p->link;
        //delete p;//应该删除第一个结点

        return 1;
    }
    ChainNode<K, E>* pre = p;
    ChainNode<K, E>* cur = pre->link;
    while (cur)
    {
        if (cur->data == e1 && cur->key == k1) {
            pre->link = cur->link;
            delete cur;
            return 1;
        }
        pre = cur;
        cur = cur->link;
    }
    return 0;
}


template <typename K, typename E>
inline int MyHashTable<K, E>::Remove(const K& k1)
{
    unsigned j = hash(k1);
    //int j = k1 % divisor; //计算散列地址
    ChainNode<K, E>* p = ht[j];

    if (p == nullptr) {
        return 0;
    }
    if (k1 == p->key) {

        ht[j] = p->link;
        //delete p;//应该删除第一个结点

        return 1;
    }
    ChainNode<K, E>* pre = p;
    ChainNode<K, E>* cur = pre->link;
    while (cur)
    {
        if (cur->key == k1) {
            pre->link = cur->link;
            delete cur;
            return 1;
        }
    }
    return 0;
}

////Remove 对pair偏特化
//template<>
//inline pair<int, int> MyHashMap<pair<string, string>, pair<int, int>>::Remove(pair<string, string> key)
//{
//    ChainNode<pair<string, string>, pair<int, int>>* p = m_table.FindPos(key);
//    m_table.Remove(key);
//    if (p != nullptr) {
//        return p->data;
//    }
//    return make_pair(0, 0);
//}
//
//template<>
//inline pair<string, string> MyHashMap<pair<int, int>, pair<string, string>>::Remove(pair<int, int> key)
//{
//    ChainNode<pair<int, int>, pair<string, string>>* p = m_table.FindPos(key);
//    m_table.Remove(key);
//    if (p != nullptr) {
//        return p->data;
//    }
//    return make_pair("", "");
//}




//负载因子低于MaxLoadFactor则执行此函数
template <typename K, typename E>
inline void MyHashTable<K, E>::resizeTable()
{
    int m = 0;//散列表中占有元素的位置数目
    for (int i = 0; i < TableSize; i++) {
        ChainNode<K, E>* p = ht[i];
        if (nullptr != p) {
            ++m;
        }
    }
    double LoadFactor = m / TableSize;
    if (LoadFactor > MaxLoadFactor) {

        int old_TableSize = TableSize;
        TableSize = next_prime(old_TableSize*2);
        divisor = TableSize;
        

        ChainNode<K, E>** old_ht = ht;
        ht = new ChainNode<K, E>*[TableSize] {nullptr};

        for (int i = 0; i < old_TableSize; ++i) {
            ChainNode<K, E>* cur = old_ht[i];
            while (nullptr != cur) {
                Insert(cur->key, cur->data);
                cur = cur->link;
            }
        }
    }
}

//时间复杂度O(V)
template <typename K, typename E>
inline void MyHashTable<K, E>::clear()
{
    int j = 0;
    ChainNode<K, E>* p = ht[j];
    for (; j < TableSize; ++j) {
        ht[j] = nullptr;
        if (p != nullptr) {

            ChainNode<K, E>* cur = p;
            ChainNode<K, E>* nex = p->link;
            while (cur)
            {
                delete cur;
                cur = nex;
                if (cur != nullptr)
                {
                    nex = cur->link;
                }
            }
        }
    }
}


//计算散列函数的除数(为小于木桶的最大质数)
template <typename K, typename E>
inline int MyHashTable<K, E>::next_prime(unsigned int n)
{
    //int n = TableSize;
    //int sign = 1;//判断是否时质数
    //for (; n > 0; --n) {
    //    sign = 1;//恢复
    //    for (int i = 2; i < n; ++i) {
    //        if (n % i == 0) {
    //            sign = 0;
    //            break;
    //        }
    //    }
    //    if (sign == 1) {
    //        return n;
    //    }
   /* }*/
    const unsigned int* first = prime_list;
    const unsigned int* last = prime_list + num_prime;
    const unsigned int* pos = lower_bound(first, last, n);
    //使用 lower_bound()序列需先排序
    return pos == last ? *(last - 1) : *pos;

}

template <typename K, typename E>
inline void MyHashTable<K, E>::print()
{
    for (int i = 0; i < TableSize; i++) {
        cout << "[" << i << "] ";
        ChainNode<K, E>* p = ht[i];
        while (p) {
            cout << "->"  << p->key << " ";
            p = p->link;
        }
        cout << endl;
    }
}

template <typename K, typename E>
inline ChainNode<K, E>* MyHashTable<K, E>::FindPos(const K& k1)
{
    unsigned j = hash(k1); //计算散列地址
    ChainNode<K,E>* p = ht[j];

    while (p != nullptr && p->key != k1) {
        p = p->link;
    }
    return p;//未查到的返回空指针
}



template <typename K, typename E>
inline unsigned MyHashTable<K, E>::hash(K k) const
{
    return k % divisor;
}

template<>//DJBHash算法
inline unsigned MyHashTable<string, int>::hash(string k) const
{
    unsigned int hash = 5381;
    const char* str = k.c_str();
    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF)%divisor;
}



template<>//DJBHash算法
inline unsigned MyHashTable<pair<string, string>, pair<int,int>>::hash(pair<string, string> k) const
{
    unsigned int hash = 5381;
    const char* str = k.first.c_str();
    while (*str)
    {
        hash += (hash << 5) + (*str++);
    }

    return (hash & 0x7FFFFFFF) % divisor;
}

template<>//DJBHash算法
inline unsigned MyHashTable<pair<int, int>, pair<string, string>>::hash(pair<int, int> k) const
{
    return (k.first + k.second) % divisor;
}

template<>//DJBHash算法
inline unsigned MyHashTable<int,string>::hash(int k) const
{
    return k % divisor;
}
