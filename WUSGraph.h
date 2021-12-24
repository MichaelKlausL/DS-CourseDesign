#pragma once

#include"DbLinkedList.h"
#include"MyHashMap.h"
#include<vector>
#include<utility>
using std::pair;
using std::vector;



//向前声明
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
	vector<Object> object;   //邻接顶点数组
	vector<Weight> weight;   //权值数组

	Neighbors()
	{
	}
	~Neighbors()
	{
	}

	void push_back(Object o, Weight w)     //推
	{
		object.push_back(o);
		weight.push_back(w);
	}
	pair<Object,Weight> pop()              //返回并删除
	{
		auto it1 = object.begin();
		auto it2 = weight.begin();
		Object o = *it1;
		Weight w = *it2;

		object.erase(it1);
		weight.erase(it2);

		return make_pair(o, w);
	}
	pair<Object, Weight> operator[](const int& pos)//重载[]
	{
		return make_pair(object[pos], weight[pos]);
	}
	int size()                             //返回Neighbors大小
	{
		return object.size();
	}
};


//边结点
template<class Weight>
struct Edge
{
	int dest;					//边的另一顶点位置
	Weight cost;			    //边上的权值
	Edge* lLink;		   	    //下一条边左链指针
	Edge* rLink;                //下一条边右链指针
	Edge* fptr;
	LinkNode<int>* ver;//顶点指针


	Edge() :dest(-1), cost(0), lLink(nullptr), rLink(nullptr), fptr(nullptr),ver(nullptr) { }//构造函数
	Edge(int num, Weight weight): dest(num), cost(weight), lLink(nullptr),rLink(nullptr),fptr(nullptr), ver(nullptr) { }//构造函数

/*	bool operator != (Edge& R) const
	{
		return dest != R.dest;
	}*/	   	//判边等否

};


template<class Object, class Weight>
class WUSGraph
{
public:
	WUSGraph(int v);      //用 v 个顶点和 0 条边初始化一个空图        O(|V|)
	WUSGraph() {};        //默认构造函数
	~WUSGraph() {};       //析构函数

	int vertexCount() { return vtCount; }     //返回图中的顶点数    O(1)
	int edgeCount() { return egCount; }       //返回图中的边数      O(1)
	int Degree(Object v);         //顶点的度                        O(1)

	Object* getVertices(); //返回包含所有顶点的数组            O(|V|)
	Neighbors<Object,Weight> getNeighbors(Object v);//返回顶点的所有邻接顶点  O(d)*
	Weight getWeight(Object v1, Object v2);      //求某边的权值  O(1)

	bool isVertex(Object v); // 判断该顶点是否在图中           O(1)*
	bool isEdge(Object v1, Object v2);        //判断是否为边   O(1)*

	void addVertex(Object v);   //添加顶点                     O(1)
	void removeVertex(Object v);//删除顶点                     O(d)*
	void addEdge(Object v1, Object v2, Weight w);//添加边      O(1)
	void removeEdge(Object v1, Object v2);       //删除边      O(1)*
	

private:
	DbLinkedList<int> NodeTable;        //顶点链表

	MyHashMap<Object, int> Vmap;                         //顶点哈希映射
	MyHashMap<pair<Object,Object>, pair<int,int>> Emap;  //边哈希映射

	MyHashMap<int, Object> vmap;                         //反向顶点映射
	MyHashMap<pair<int, int>, pair<Object, Object>> emap;//反向边映射
	
	int egCount=0;            //边计数器
	int vtCount=0;            //顶点计数器
	int Count = 0;            //顶点编号
	vector<int> degree;       //顶点度数

	static int MAX_WEIGHT;

};

