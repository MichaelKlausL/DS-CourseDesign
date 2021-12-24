#pragma once

#include<iostream>
#include<assert.h>
#include"MyHashMap.h"
#include"DbLinkedList.h"
#include"WUSGraph.h"
using namespace std;

//��ǰ����
template<class T>
struct LinkNode;

template<class T>
struct Edge;


//ɾ����������ڴ�й¶

static const int num_prime = 24;
static const unsigned int prime_list[num_prime] = //0��4294967295  -2147483648��2147483647
{
    17,        29,
    53,        97,      193,        389,       769,
    1543,      3079,    6151,       12289,     24593,
    49157,     98317,   196613,     393241,    786433,
    1572869,   3145739, 6291469,    12582917,  25165843,
    50331653,  100663319
};

template<typename K, typename E>
struct ChainNode {        //��ľͰ֮��ͬ����ӱ������㶨��
    E data;                  //Ԫ��
    K key;                   //��ֵ
    ChainNode<K, E>* link = nullptr;   //��ָ��

    /////////////////////////�����ڽӱ���
    LinkNode<int>* conVt = nullptr;
    Edge<int>* conEd = nullptr;


    ChainNode(K k, E e) :key(k), data(e), link(nullptr) {}
    ChainNode() :link(nullptr) {}
};

template <typename K, typename E>
class MyHashTable {		     //ɢ�б��ඨ��
public:

    
    MyHashTable();
    MyHashTable(int initialSize);
    MyHashTable(int initialSize, double m_MaxLoadFactor);
    //��δ˵������Ĭ��ֵ initialSize = 16 �� MaxLoadFactor = 0.7                      O(1)

    ~MyHashTable() { delete[]ht; } 	//��������

    bool Search(const K& k1) const;       //��ɢ�б��в���                           O(1)
    bool Insert(const K& k1, const E& e1);//����e1                                   O(1)
    int Remove(const K& k1, const E& e1); //ɾ��e1                                   O(1)
    int Remove(const K& k1);	       	  //ɾ����ֵk1��Ӧ������                     O(1)
    void resizeTable();
    void clear();                         //�ÿձ�                                   O(V)
    unsigned hash(K k) const;


    ////////////////////////////////////////
    void connect(K k1,LinkNode<int>* node)       //���ڽӱ�������
    {
        ChainNode<K, E>* cnode = FindPos(k1);
        cnode->conVt = node;
    }
    void connect(K k1, Edge<int>* node)         //���ڽӱ�������
    {
        ChainNode<K, E>* cnode = FindPos(k1);
        cnode->conEd = node;
    }
    LinkNode<int>* getVertex(K k1)             //���ؽ��ָ��
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


    ChainNode<K, E>* FindPos(const K& k1);//ɢ��
    int next_prime(unsigned int n);
    void print();
    ChainNode<K, E>** ht;   //ɢ�б���
    int getTableSize() { return TableSize; }
private:
    int divisor;		    //ɢ�к����ĳ���(������������С���������������)
    int TableSize;	        //��ǰͰ�������Ͱ��
    double MaxLoadFactor;   //���ɢ������
   
};

template <typename K, typename E>
inline MyHashTable<K, E>::MyHashTable()
{
    divisor = 13;
    TableSize = 16;
    MaxLoadFactor = 0.7;

    ht = new ChainNode<K, E> *[TableSize] {nullptr};//�������

    assert(ht != nullptr);//���ԣ��жϴ洢����ɹ���
}

template <typename K, typename E>
inline MyHashTable<K, E>::MyHashTable(int initialSize)
{
    TableSize = next_prime(initialSize);
    divisor = TableSize;
    MaxLoadFactor = 0.7;

    ht = new ChainNode<K, E> *[TableSize] {nullptr};//�������

    assert(ht != nullptr);//���ԣ��жϴ洢����ɹ���
}

template <typename K, typename E>
inline MyHashTable<K, E>::MyHashTable(int initialSize, double m_MaxLoadFactor)
{
    TableSize = next_prime(initialSize);
    divisor = TableSize;
    MaxLoadFactor = m_MaxLoadFactor;

    ht = new ChainNode<K, E> *[TableSize] {nullptr};//�������

    assert(ht != nullptr);//���ԣ��жϴ洢����ɹ���
}

template <typename K, typename E>
inline bool MyHashTable<K, E>::Search(const K& k1) const
{
    unsigned j = hash(k1);
    //int j = k1 % divisor; //����ɢ�е�ַ
    ChainNode<K, E>* p = ht[j];

    while (p != nullptr) {
        if (k1 == p->key) {
            return true;
        }
        p = p->link;
    }
    return false;
}

//ʱ�临�Ӷ�O(1)
template <typename K, typename E>
inline bool MyHashTable<K, E>::Insert(const K& k1, const E& e1)
{
    ChainNode<K, E>* InsertNode = new ChainNode<K, E>;
    InsertNode->data = e1;
    InsertNode->link = nullptr;
    InsertNode->key = k1;

    unsigned j = hash(k1);
    //int j = k1 % divisor; //����ɢ�е�ַ
    ChainNode<K, E>* p = ht[j];

    if (Search(k1)) {  //�����ɹ�,��ɾ����������
        Remove(k1);
        return Insert(k1, e1);
    }
    //β����
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

        resizeTable();//�жϸ��������Ƿ񳬳����ֵ
        return true;
    }
    return false;
}


template <typename K, typename E>
inline int MyHashTable<K, E>::Remove(const K& k1, const E& e1)
{
    unsigned j = hash(k1);
    //int j = k1 % divisor; //����ɢ�е�ַ
    ChainNode<K, E>* p = ht[j];

    if (p == nullptr) {
        return 0;
    }
    if (p->data == e1 && p->key == k1) {

        ht[j] = p->link;
        //delete p;//Ӧ��ɾ����һ�����

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
    //int j = k1 % divisor; //����ɢ�е�ַ
    ChainNode<K, E>* p = ht[j];

    if (p == nullptr) {
        return 0;
    }
    if (k1 == p->key) {

        ht[j] = p->link;
        //delete p;//Ӧ��ɾ����һ�����

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

////Remove ��pairƫ�ػ�
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




//�������ӵ���MaxLoadFactor��ִ�д˺���
template <typename K, typename E>
inline void MyHashTable<K, E>::resizeTable()
{
    int m = 0;//ɢ�б���ռ��Ԫ�ص�λ����Ŀ
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

//ʱ�临�Ӷ�O(V)
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


//����ɢ�к����ĳ���(ΪС��ľͰ���������)
template <typename K, typename E>
inline int MyHashTable<K, E>::next_prime(unsigned int n)
{
    //int n = TableSize;
    //int sign = 1;//�ж��Ƿ�ʱ����
    //for (; n > 0; --n) {
    //    sign = 1;//�ָ�
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
    //ʹ�� lower_bound()������������
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
    unsigned j = hash(k1); //����ɢ�е�ַ
    ChainNode<K,E>* p = ht[j];

    while (p != nullptr && p->key != k1) {
        p = p->link;
    }
    return p;//δ�鵽�ķ��ؿ�ָ��
}



template <typename K, typename E>
inline unsigned MyHashTable<K, E>::hash(K k) const
{
    return k % divisor;
}

template<>//DJBHash�㷨
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



template<>//DJBHash�㷨
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

template<>//DJBHash�㷨
inline unsigned MyHashTable<pair<int, int>, pair<string, string>>::hash(pair<int, int> k) const
{
    return (k.first + k.second) % divisor;
}

template<>//DJBHash�㷨
inline unsigned MyHashTable<int,string>::hash(int k) const
{
    return k % divisor;
}
