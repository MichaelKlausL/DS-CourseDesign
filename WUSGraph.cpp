#include "WUSGraph.h"
#include <set>
using std::set;


template<class Object, class Weight>
int WUSGraph<Object, Weight>::MAX_WEIGHT = 100000;


//构造函数
template<class Object, class Weight>
WUSGraph<Object, Weight>::WUSGraph(int v)
{
	
}


//返回顶点v度数
template<class Object, class Weight>
int WUSGraph<Object, Weight>::Degree(Object v)
{
	if (!Vmap.containsKey(v))
		return 0;

	int val=Vmap.getValue(v);
	return degree[val];

}

//判断是否存在边<v1,v2>
template<class Object, class Weight>
bool WUSGraph<Object, Weight>::isEdge(Object v1, Object v2)
{
	pair<Object, Object> pa(v1, v2);
	pair<Object, Object> pa2(v2, v1);
	if (Emap.containsKey(pa)|| Emap.containsKey(pa2))           //查找pair（v1，v2）是否在哈希映射中
		return true;
	return false;
}

//判断是否存在顶点v
template<class Object, class Weight>
bool WUSGraph<Object, Weight>::isVertex(Object v)
{     
	if (Vmap.containsKey(v))           //查找顶点v是否在哈希映射中
		return true;
	return false;
}



//返回包含所有顶点的数组
template<class Object, class Weight>
Object* WUSGraph<Object, Weight>::getVertices()
{
	set<Object> s = Vmap.keySet();    //获得Vmap中所有键值组成的set
	int size = s.size();
	int i = 0;
	Object *a=new Object[size];

	for (auto it = s.begin(); it != s.end(); it++,i++)
	{
		a[i] = *it;		
	}

	return a;
}


//返回边的权值
template<class Object, class Weight>
Weight WUSGraph<Object, Weight>::getWeight(Object v1, Object v2)
{
	if(!isEdge(v1,v2))//判断边是否存在，不存在则返回MAX_WEIGHT
		return MAX_WEIGHT;


	/*                  映射              */
	Edge<int>* Ed = Emap.getEdge(make_pair(v1, v2));
	if (Ed != nullptr)
		return Ed->cost;	
	/*                  映射              */

}



//插入顶点
template<class Object, class Weight>
void WUSGraph<Object, Weight>::addVertex(Object v)
{
	if (Vmap.containsKey(v)) //若v已存在，不做操作
		return;



	pair < Object, int > pa(v, Count); 
	LinkNode<int>* ver = NodeTable.push_back(Count);  //更新NodeTable	
	Vmap.Insert(pa);                                  //更新Vmap映射

	pair<int, Object> pa2(Count, v);                  ////更新vmap映射
	vmap.Insert(pa2);

	/*           映射                  */
	Vmap.connect(v, ver);
	/*           映射                  */


	Count++;            //序号加一
	vtCount++;          //顶点数量+1
	degree.push_back(0);//度数数组容量+1


}


//插入边
template<class Object, class Weight>
void  WUSGraph<Object, Weight>::addEdge(Object v1, Object v2, Weight w)
{
	///////判断边是否存在//////////
	if (Emap.containsKey(make_pair(v1, v2))|| Emap.containsKey(make_pair(v2, v1)))//若边存在，更改权值
	{
		pair<int, int> pa;
		if (Emap.containsKey(make_pair(v1, v2)))
		{
			Edge<int>* ed = Emap.getEdge(make_pair(v1, v2));
			ed->cost = w;
		}
		if (Emap.containsKey(make_pair(v2, v1)))
		{
			Edge<int>* ed = Emap.getEdge(make_pair(v2,v1));
			ed->cost = w;
		}

		return;
	}

	///////判断是否是自环///////////
	if (v1 == v2)//如果自环则不做操作
		return;


	///////判断顶点是否存在////////
	if (!Vmap.containsKey(v1))   //若顶点不存在，先插入顶点
		addVertex(v1);
	if (!Vmap.containsKey(v2))
		addVertex(v2);

	//映射
	int pos1 = Vmap.getValue(v1);
	int pos2 = Vmap.getValue(v2);

	pair<Object, Object> pa1(v1, v2);
	pair<int, int> pa2(pos1, pos2);

	Emap.Insert(make_pair(pa1, pa2));                          //更新Emap映射
	emap.Insert(make_pair(pa2, pa1));                          ////更新emap映射



	Edge<int>* newEdge = new Edge<int>(pos2,w);//边结点插入邻接表


	/*          映射                */
	Emap.connect(pa1, newEdge);

	LinkNode<int>* p1 = Vmap.getVertex(v1);    //定位顶点
	LinkNode<int>* p2 = Vmap.getVertex(v2);
	/*          映射                */





	newEdge->rLink = p1->adj;                  //插入newEdge
	if(newEdge->rLink != nullptr)
	{
		newEdge->rLink->ver = nullptr;
		newEdge->rLink->lLink = newEdge;
	}
	newEdge->ver = p1;
	p1->adj = newEdge;

	Edge<int>* newEdge2 = new Edge<int>(pos1,w);
	newEdge2->rLink = p2->adj;                //插入newEdge2
	if(newEdge2->rLink != nullptr)
	{
		newEdge2->rLink->ver = nullptr;
		newEdge2->rLink->lLink = newEdge2;
	}
	newEdge2->ver = p2;
	p2->adj = newEdge2;

	newEdge->fptr = newEdge2;  //伙伴指针
	newEdge2->fptr = newEdge;

	egCount++;      //边数量+1 
	degree[pos1]++; //度数+1
	degree[pos2]++;

}


//删除顶点        ///////////////////////////////////////////////
template<class Object, class Weight>
void WUSGraph<Object, Weight>::removeVertex(Object v)
{
	//判断顶点是否存在
	if (!Vmap.containsKey(v))//如果v不存在，不做操作
		return;

	//映射
	int pos = Vmap.getValue(v);

	/*           映射               */
	LinkNode<int>* p = Vmap.getVertex(v);

	if (p == nullptr)//若v不存在，不做操作
		return;
	/*           映射               */


	Edge<int>* del = p->adj;
	Edge<int>* fri;
	Edge<int>* temp;

	int count = 0;

	while (del != nullptr)//删除边结点
	{
		temp = del;
		fri = del->fptr;         //删除伙伴结点

		//度数更新
		degree[del->dest]--;//邻接顶点度数-1


		//删除散列映射Emap,emap//
		//正向
		pair<int, int> pa2(p->data, del->dest);
		pair<Object, Object> pa1 = emap.getValue(pa2);
		Emap.Remove(pa1,pa2);
		emap.Remove(pa2,pa1);
		//反向
		pa2 = make_pair(del->dest,p->data);
		pa1 = emap.getValue(pa2);
		Emap.Remove(pa1, pa2);
		emap.Remove(pa2, pa1);
		


		/////////////////////////////////////////////////////////////////
		//删除fri
		if (fri->ver == nullptr)
		{
			fri->lLink->rLink = fri->rLink;
			if(fri->rLink!=nullptr)
				fri->rLink->lLink = fri->lLink;
		}
		else
		{
			fri->ver->adj = fri->rLink;//fri邻接着顶点结点
			if (fri->rLink != nullptr)
			{
				fri->rLink->ver = fri->ver;
				fri->rLink->lLink = nullptr;
			}
		}


		//删除del
		del->ver->adj = del->rLink;
		if(del->rLink!=nullptr)
			del->rLink->ver = del->ver;

		del = temp->rLink;
		delete fri;
		delete temp;		


	}
	cout << "准备删除顶点" << p->data << endl;
	NodeTable.Remove(p);              //删除顶点


	//删除顶点映射Vmap,vmap
	Vmap.Remove(v, pos);
	vmap.Remove(pos, v);

	vtCount--;                        //顶点数量-1
	egCount = egCount - degree[pos];  //边数量-度数
	degree[pos] = 0;                  //度数清空

}


//删除边
template<class Object, class Weight>
void WUSGraph<Object, Weight>::removeEdge(Object v1, Object v2)
{

	//判断边是否存在
	if (!isEdge(v1, v2))//边不存在则不做操作
		return;

	/*         映射              */
	Edge<int>* del = Emap.getEdge(make_pair(v1, v2));
	if (del == nullptr)//若v1，v2不存在，不做操作
		del= Emap.getEdge(make_pair(v2, v1));
	Edge<int>* fri = del->fptr;

	/*         映射              */


	//删fri
	if (fri->ver == nullptr)
	{
		fri->lLink->rLink = fri->rLink;
		if (fri->rLink != nullptr)
			fri->rLink->lLink = fri->lLink;
	}
	else
	{
		fri->ver->adj = fri->rLink;
		if (fri->rLink != nullptr)
		{
			fri->rLink->ver = fri->ver;
			fri->rLink->lLink = nullptr;
		}
	}
	//删del
	if (del->ver == nullptr)
	{
		del->lLink->rLink = del->rLink;
		if (del->rLink != nullptr)
			del->rLink->lLink = del->lLink;
	}
	else
	{
		del->ver->adj = del->rLink;
		if (del->rLink != nullptr)
		{
			del->rLink->ver = del->ver;
			del->rLink->lLink = nullptr;
		}
	}

	delete del;
	delete fri;



	//散列表删除
	pair<Object, Object> pa1(v1, v2);
	pair<int, int> pa2 = Emap.getValue(pa1);
	Emap.Remove(pa1, pa2);
	emap.Remove(pa2, pa1);

	pa1 = make_pair(v2, v1);
	pa2 = Emap.getValue(pa1);
	Emap.Remove(pa1, pa2);
	emap.Remove(pa2, pa1);


	//度数更新
	egCount--;      //边数量-1
	int pos1 = Vmap.getValue(v1);
	int pos2 = Vmap.getValue(v2);
	degree[pos1]--; //度数减一;
	degree[pos2]--;


}


//返回顶点所有邻接顶点
template<class Object, class Weight>
Neighbors<Object, Weight> WUSGraph<Object, Weight>::getNeighbors(Object v)
{
	Neighbors<Object,int> neighbors;

	/*         映射           */
	LinkNode<int>* p = Vmap.getVertex(v);

	if (p == nullptr)//若v不存在，返回空neighbors
		return neighbors;
	/*         映射           */

	Edge<int>* ed = p->adj;

	///////////反向映射//////////////////////////
	while (ed != nullptr)
	{
		Object vertex = vmap.getValue(ed->dest);     //vertex为邻接顶点标签
		neighbors.push_back(vertex, ed->cost);

		ed = ed->rLink;
	}
	return neighbors;
}