#pragma once

#include<iostream>
#include<cstring>
#include<vector>
#include<list>
#include<set>
#include"MyHashTable.h"
#include"DbLinkedList.h"
#include"WUSGraph.h"
using namespace std;

//向前声明
template<class T>
struct LinkNode;
template<class E>
struct Edge;

template<typename K, typename V>
class MyHashMap
{

	
public:
	MyHashMap();
	MyHashMap(int initialSize);
	MyHashMap(int initialSize, double MaxLoadFactor);
	~MyHashMap();
	V getValue(K key);// 获取 Map 中指定键 key 映射到的值或对应的值，如果 Map 不包含键的映射，返回 V() O(1)
	set<K> keySet();  //返回 Map 中包含的键的集合。                                                    O(V)
	bool containsKey(K key);//如果 Map 包含指定键 key 的映射，则返回true                               O(1)
	void Insert(std::pair<K, V> k_v);//在 Map 中添加键值对 k_v。                                       O(1)
	//在 Map 中将指定值 value 与指定键 key 相关联。如果键k_v.key 已经存在，那么原来的键值对将被替代成新的键值对。
	V Remove(K key);//从 Map 中删除指定键 key 的映射(如果存在)。                                       O(1)
	V Remove(K key, V val);//仅当键 key 当前映射到指定值 value 时，才删除该项映射。                    O(1)
	void clear();//删除 Map 的所有映射                                                                 O(1)
	int getSize();//返回 Map 中的键-值对映射的总数                                                     O(V)


	///////////////////////映射////////////////////////
	void connect(K k1, LinkNode<int>* node)       //与邻接表建立连接
	{
		m_table.connect(k1, node);
	}
	void connect(K k1, Edge<int>* node)          //与邻接表建立连接
	{
		m_table.connect(k1, node);
	}
	LinkNode<int>* getVertex(K k1)              //返回结点指针
	{
		return m_table.getVertex(k1);
	}
	Edge<int>* getEdge(K k1)
	{
		return m_table.getEdge(k1);
	}
	////////////////////////////////////////





//private:
	MyHashTable<K, V> m_table;
};

template<typename K, typename V>
inline MyHashMap<K, V>::MyHashMap()
{
}

template<typename K, typename V>
inline MyHashMap<K, V>::MyHashMap(int initialSize):m_table(initialSize)
{

}

template<typename K, typename V>
inline MyHashMap<K, V>::MyHashMap(int initialSize, double MaxLoadFactor):m_table(initialSize, MaxLoadFactor)
{

}

template<typename K, typename V>
inline V MyHashMap<K, V>::getValue(K key)
{
	ChainNode<K, V>* p = m_table.FindPos(key);
	if (p != nullptr) {
		return p->data;
	}
	//return  V();/////////////////////////////////////返回值是什么//////////

	V a;
	memset(&a, 0, sizeof(a)); 
	return a;
}



template<typename K, typename V>
inline set<K> MyHashMap<K, V>::keySet()
{
	set<K> m_set;
	int j = 0;
	for (; j < m_table.getTableSize(); ++j) {
		ChainNode<K, V>* p = m_table.ht[j];
		while (p != nullptr) { 
			m_set.insert(p->key);
			p = p->link;
		}
	}
	return m_set;
}

//如果 Map 包含指定键 key 的映射，则返回true
//时间复杂度为O(V)
template<typename K, typename V>
inline bool MyHashMap<K, V>::containsKey(K key)
{
	return m_table.Search(key);
}

//关联两个量K V
template<typename K, typename V>
inline void MyHashMap<K, V>::Insert(pair<K, V> k_v)
{
	m_table.Insert(k_v.first,k_v.second);
}

template<typename K, typename V>
inline V MyHashMap<K, V>::Remove(K key)
{
	ChainNode<K,V>* p = m_table.FindPos(key);
	m_table.Remove(key);
	if (p != nullptr) {
		return p->data;
	}
	return V();
}

template<typename K, typename V>
inline V MyHashMap<K, V>::Remove(K key, V val)
{
	ChainNode<K,V>* p = m_table.FindPos(key);
	
	if (p != nullptr) {
		V data = p->data;
		m_table.Remove(key, val);
		return data;
	}
	return V();
}

template<typename K, typename V>
inline void MyHashMap<K, V>::clear()
{
	m_table.clear();
}

template<typename K, typename V>
inline int MyHashMap<K, V>::getSize()
{
	int num = 0;
	int j = 0;
	for (; j < m_table.getTableSize(); ++j) {
		ChainNode<K, V>* p = m_table.ht[j];
		if (p != nullptr) {
			p = p->link;
			++num;
		}
	}
	return num;
}

template<typename K, typename V>
inline MyHashMap<K, V>::~MyHashMap()
{
}


