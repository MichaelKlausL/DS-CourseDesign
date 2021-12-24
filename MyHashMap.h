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

//��ǰ����
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
	V getValue(K key);// ��ȡ Map ��ָ���� key ӳ�䵽��ֵ���Ӧ��ֵ����� Map ����������ӳ�䣬���� V() O(1)
	set<K> keySet();  //���� Map �а����ļ��ļ��ϡ�                                                    O(V)
	bool containsKey(K key);//��� Map ����ָ���� key ��ӳ�䣬�򷵻�true                               O(1)
	void Insert(std::pair<K, V> k_v);//�� Map ����Ӽ�ֵ�� k_v��                                       O(1)
	//�� Map �н�ָ��ֵ value ��ָ���� key ������������k_v.key �Ѿ����ڣ���ôԭ���ļ�ֵ�Խ���������µļ�ֵ�ԡ�
	V Remove(K key);//�� Map ��ɾ��ָ���� key ��ӳ��(�������)��                                       O(1)
	V Remove(K key, V val);//������ key ��ǰӳ�䵽ָ��ֵ value ʱ����ɾ������ӳ�䡣                    O(1)
	void clear();//ɾ�� Map ������ӳ��                                                                 O(1)
	int getSize();//���� Map �еļ�-ֵ��ӳ�������                                                     O(V)


	///////////////////////ӳ��////////////////////////
	void connect(K k1, LinkNode<int>* node)       //���ڽӱ�������
	{
		m_table.connect(k1, node);
	}
	void connect(K k1, Edge<int>* node)          //���ڽӱ�������
	{
		m_table.connect(k1, node);
	}
	LinkNode<int>* getVertex(K k1)              //���ؽ��ָ��
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
	//return  V();/////////////////////////////////////����ֵ��ʲô//////////

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

//��� Map ����ָ���� key ��ӳ�䣬�򷵻�true
//ʱ�临�Ӷ�ΪO(V)
template<typename K, typename V>
inline bool MyHashMap<K, V>::containsKey(K key)
{
	return m_table.Search(key);
}

//����������K V
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


