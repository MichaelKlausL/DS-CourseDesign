#pragma once

#include"DbLinkedList.h"
#include"MyHashMap.h"
#include<vector>
#include<utility>
using std::pair;
using std::vector;



//��ǰ����
template<class T>
class DbLinkedList;

template<class K,class V>
class HashMap;

template<class T>
struct LinkNode;


template<class Object,class Weight>
class Neighbors
{
public:
	vector<Object> object;   //�ڽӶ�������
	vector<Weight> weight;   //Ȩֵ����

	Neighbors()
	{
	}
	~Neighbors()
	{
	}

	void push_back(Object o, Weight w)     //��
	{
		object.push_back(o);
		weight.push_back(w);
	}
	pair<Object,Weight> pop()              //���ز�ɾ��
	{
		auto it1 = object.begin();
		auto it2 = weight.begin();
		Object o = *it1;
		Weight w = *it2;

		object.erase(it1);
		weight.erase(it2);

		return make_pair(o, w);
	}
	pair<Object, Weight> operator[](const int& pos)//����[]
	{
		return make_pair(object[pos], weight[pos]);
	}
	int size()                             //����Neighbors��С
	{
		return object.size();
	}
};


//�߽��
template<class Weight>
struct Edge
{
	int dest;					//�ߵ���һ����λ��
	Weight cost;			    //���ϵ�Ȩֵ
	Edge* lLink;		   	    //��һ��������ָ��
	Edge* rLink;                //��һ��������ָ��
	Edge* fptr;
	LinkNode<int>* ver;//����ָ��


	Edge() :dest(-1), cost(0), lLink(nullptr), rLink(nullptr), fptr(nullptr),ver(nullptr) { }//���캯��
	Edge(int num, Weight weight): dest(num), cost(weight), lLink(nullptr),rLink(nullptr),fptr(nullptr), ver(nullptr) { }//���캯��

/*	bool operator != (Edge& R) const
	{
		return dest != R.dest;
	}*/	   	//�бߵȷ�

};


template<class Object, class Weight>
class WUSGraph
{
public:
	WUSGraph(int v);      //�� v ������� 0 ���߳�ʼ��һ����ͼ        O(|V|)
	WUSGraph() {};        //Ĭ�Ϲ��캯��
	~WUSGraph() {};       //��������

	int vertexCount() { return vtCount; }     //����ͼ�еĶ�����    O(1)
	int edgeCount() { return egCount; }       //����ͼ�еı���      O(1)
	int Degree(Object v);         //����Ķ�                        O(1)

	Object* getVertices(); //���ذ������ж��������            O(|V|)
	Neighbors<Object,Weight> getNeighbors(Object v);//���ض���������ڽӶ���  O(d)*
	Weight getWeight(Object v1, Object v2);      //��ĳ�ߵ�Ȩֵ  O(1)

	bool isVertex(Object v); // �жϸö����Ƿ���ͼ��           O(1)*
	bool isEdge(Object v1, Object v2);        //�ж��Ƿ�Ϊ��   O(1)*

	void addVertex(Object v);   //��Ӷ���                     O(1)
	void removeVertex(Object v);//ɾ������                     O(d)*
	void addEdge(Object v1, Object v2, Weight w);//��ӱ�      O(1)
	void removeEdge(Object v1, Object v2);       //ɾ����      O(1)*
	

private:
	DbLinkedList<int> NodeTable;        //��������

	MyHashMap<Object, int> Vmap;                         //�����ϣӳ��
	MyHashMap<pair<Object,Object>, pair<int,int>> Emap;  //�߹�ϣӳ��

	MyHashMap<int, Object> vmap;                         //���򶥵�ӳ��
	MyHashMap<pair<int, int>, pair<Object, Object>> emap;//�����ӳ��
	
	int egCount=0;            //�߼�����
	int vtCount=0;            //���������
	int Count = 0;            //������
	vector<int> degree;       //�������

	static int MAX_WEIGHT;

};

