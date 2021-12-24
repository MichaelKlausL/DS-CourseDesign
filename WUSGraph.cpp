#include "WUSGraph.h"
#include <set>
using std::set;


template<class Object, class Weight>
int WUSGraph<Object, Weight>::MAX_WEIGHT = 100000;


//���캯��
template<class Object, class Weight>
WUSGraph<Object, Weight>::WUSGraph(int v)
{
	
}


//���ض���v����
template<class Object, class Weight>
int WUSGraph<Object, Weight>::Degree(Object v)
{
	if (!Vmap.containsKey(v))
		return 0;

	int val=Vmap.getValue(v);
	return degree[val];

}

//�ж��Ƿ���ڱ�<v1,v2>
template<class Object, class Weight>
bool WUSGraph<Object, Weight>::isEdge(Object v1, Object v2)
{
	pair<Object, Object> pa(v1, v2);
	pair<Object, Object> pa2(v2, v1);
	if (Emap.containsKey(pa)|| Emap.containsKey(pa2))           //����pair��v1��v2���Ƿ��ڹ�ϣӳ����
		return true;
	return false;
}

//�ж��Ƿ���ڶ���v
template<class Object, class Weight>
bool WUSGraph<Object, Weight>::isVertex(Object v)
{     
	if (Vmap.containsKey(v))           //���Ҷ���v�Ƿ��ڹ�ϣӳ����
		return true;
	return false;
}



//���ذ������ж��������
template<class Object, class Weight>
Object* WUSGraph<Object, Weight>::getVertices()
{
	set<Object> s = Vmap.keySet();    //���Vmap�����м�ֵ��ɵ�set
	int size = s.size();
	int i = 0;
	Object *a=new Object[size];

	for (auto it = s.begin(); it != s.end(); it++,i++)
	{
		a[i] = *it;		
	}

	return a;
}


//���رߵ�Ȩֵ
template<class Object, class Weight>
Weight WUSGraph<Object, Weight>::getWeight(Object v1, Object v2)
{
	if(!isEdge(v1,v2))//�жϱ��Ƿ���ڣ��������򷵻�MAX_WEIGHT
		return MAX_WEIGHT;


	/*                  ӳ��              */
	Edge<int>* Ed = Emap.getEdge(make_pair(v1, v2));
	if (Ed != nullptr)
		return Ed->cost;	
	/*                  ӳ��              */

}



//���붥��
template<class Object, class Weight>
void WUSGraph<Object, Weight>::addVertex(Object v)
{
	if (Vmap.containsKey(v)) //��v�Ѵ��ڣ���������
		return;



	pair < Object, int > pa(v, Count); 
	LinkNode<int>* ver = NodeTable.push_back(Count);  //����NodeTable	
	Vmap.Insert(pa);                                  //����Vmapӳ��

	pair<int, Object> pa2(Count, v);                  ////����vmapӳ��
	vmap.Insert(pa2);

	/*           ӳ��                  */
	Vmap.connect(v, ver);
	/*           ӳ��                  */


	Count++;            //��ż�һ
	vtCount++;          //��������+1
	degree.push_back(0);//������������+1


}


//�����
template<class Object, class Weight>
void  WUSGraph<Object, Weight>::addEdge(Object v1, Object v2, Weight w)
{
	///////�жϱ��Ƿ����//////////
	if (Emap.containsKey(make_pair(v1, v2))|| Emap.containsKey(make_pair(v2, v1)))//���ߴ��ڣ�����Ȩֵ
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

	///////�ж��Ƿ����Ի�///////////
	if (v1 == v2)//����Ի���������
		return;


	///////�ж϶����Ƿ����////////
	if (!Vmap.containsKey(v1))   //�����㲻���ڣ��Ȳ��붥��
		addVertex(v1);
	if (!Vmap.containsKey(v2))
		addVertex(v2);

	//ӳ��
	int pos1 = Vmap.getValue(v1);
	int pos2 = Vmap.getValue(v2);

	pair<Object, Object> pa1(v1, v2);
	pair<int, int> pa2(pos1, pos2);

	Emap.Insert(make_pair(pa1, pa2));                          //����Emapӳ��
	emap.Insert(make_pair(pa2, pa1));                          ////����emapӳ��



	Edge<int>* newEdge = new Edge<int>(pos2,w);//�߽������ڽӱ�


	/*          ӳ��                */
	Emap.connect(pa1, newEdge);

	LinkNode<int>* p1 = Vmap.getVertex(v1);    //��λ����
	LinkNode<int>* p2 = Vmap.getVertex(v2);
	/*          ӳ��                */





	newEdge->rLink = p1->adj;                  //����newEdge
	if(newEdge->rLink != nullptr)
	{
		newEdge->rLink->ver = nullptr;
		newEdge->rLink->lLink = newEdge;
	}
	newEdge->ver = p1;
	p1->adj = newEdge;

	Edge<int>* newEdge2 = new Edge<int>(pos1,w);
	newEdge2->rLink = p2->adj;                //����newEdge2
	if(newEdge2->rLink != nullptr)
	{
		newEdge2->rLink->ver = nullptr;
		newEdge2->rLink->lLink = newEdge2;
	}
	newEdge2->ver = p2;
	p2->adj = newEdge2;

	newEdge->fptr = newEdge2;  //���ָ��
	newEdge2->fptr = newEdge;

	egCount++;      //������+1 
	degree[pos1]++; //����+1
	degree[pos2]++;

}


//ɾ������        ///////////////////////////////////////////////
template<class Object, class Weight>
void WUSGraph<Object, Weight>::removeVertex(Object v)
{
	//�ж϶����Ƿ����
	if (!Vmap.containsKey(v))//���v�����ڣ���������
		return;

	//ӳ��
	int pos = Vmap.getValue(v);

	/*           ӳ��               */
	LinkNode<int>* p = Vmap.getVertex(v);

	if (p == nullptr)//��v�����ڣ���������
		return;
	/*           ӳ��               */


	Edge<int>* del = p->adj;
	Edge<int>* fri;
	Edge<int>* temp;

	int count = 0;

	while (del != nullptr)//ɾ���߽��
	{
		temp = del;
		fri = del->fptr;         //ɾ�������

		//��������
		degree[del->dest]--;//�ڽӶ������-1


		//ɾ��ɢ��ӳ��Emap,emap//
		//����
		pair<int, int> pa2(p->data, del->dest);
		pair<Object, Object> pa1 = emap.getValue(pa2);
		Emap.Remove(pa1,pa2);
		emap.Remove(pa2,pa1);
		//����
		pa2 = make_pair(del->dest,p->data);
		pa1 = emap.getValue(pa2);
		Emap.Remove(pa1, pa2);
		emap.Remove(pa2, pa1);
		


		/////////////////////////////////////////////////////////////////
		//ɾ��fri
		if (fri->ver == nullptr)
		{
			fri->lLink->rLink = fri->rLink;
			if(fri->rLink!=nullptr)
				fri->rLink->lLink = fri->lLink;
		}
		else
		{
			fri->ver->adj = fri->rLink;//fri�ڽ��Ŷ�����
			if (fri->rLink != nullptr)
			{
				fri->rLink->ver = fri->ver;
				fri->rLink->lLink = nullptr;
			}
		}


		//ɾ��del
		del->ver->adj = del->rLink;
		if(del->rLink!=nullptr)
			del->rLink->ver = del->ver;

		del = temp->rLink;
		delete fri;
		delete temp;		


	}
	cout << "׼��ɾ������" << p->data << endl;
	NodeTable.Remove(p);              //ɾ������


	//ɾ������ӳ��Vmap,vmap
	Vmap.Remove(v, pos);
	vmap.Remove(pos, v);

	vtCount--;                        //��������-1
	egCount = egCount - degree[pos];  //������-����
	degree[pos] = 0;                  //�������

}


//ɾ����
template<class Object, class Weight>
void WUSGraph<Object, Weight>::removeEdge(Object v1, Object v2)
{

	//�жϱ��Ƿ����
	if (!isEdge(v1, v2))//�߲�������������
		return;

	/*         ӳ��              */
	Edge<int>* del = Emap.getEdge(make_pair(v1, v2));
	if (del == nullptr)//��v1��v2�����ڣ���������
		del= Emap.getEdge(make_pair(v2, v1));
	Edge<int>* fri = del->fptr;

	/*         ӳ��              */


	//ɾfri
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
	//ɾdel
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



	//ɢ�б�ɾ��
	pair<Object, Object> pa1(v1, v2);
	pair<int, int> pa2 = Emap.getValue(pa1);
	Emap.Remove(pa1, pa2);
	emap.Remove(pa2, pa1);

	pa1 = make_pair(v2, v1);
	pa2 = Emap.getValue(pa1);
	Emap.Remove(pa1, pa2);
	emap.Remove(pa2, pa1);


	//��������
	egCount--;      //������-1
	int pos1 = Vmap.getValue(v1);
	int pos2 = Vmap.getValue(v2);
	degree[pos1]--; //������һ;
	degree[pos2]--;


}


//���ض��������ڽӶ���
template<class Object, class Weight>
Neighbors<Object, Weight> WUSGraph<Object, Weight>::getNeighbors(Object v)
{
	Neighbors<Object,int> neighbors;

	/*         ӳ��           */
	LinkNode<int>* p = Vmap.getVertex(v);

	if (p == nullptr)//��v�����ڣ����ؿ�neighbors
		return neighbors;
	/*         ӳ��           */

	Edge<int>* ed = p->adj;

	///////////����ӳ��//////////////////////////
	while (ed != nullptr)
	{
		Object vertex = vmap.getValue(ed->dest);     //vertexΪ�ڽӶ����ǩ
		neighbors.push_back(vertex, ed->cost);

		ed = ed->rLink;
	}
	return neighbors;
}