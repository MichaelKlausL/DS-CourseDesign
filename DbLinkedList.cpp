#include "DbLinkedList.h"












//清空链表
template<class T>
void DbLinkedList<T>::makeEmpty()
{
	LinkNode<T>* del = first->Rlink;             //释放所有空间
	while (first->Rlink != first)
	{
		del = first->Rlink;
		first->Rlink = del->Rlink;
		delete del;
	}

	delete first;                            //删除头指针
}


//求链表长度
template <class T>
int DbLinkedList<T> ::Length()const {
	//检测指针 p 指示第一个结点
	LinkNode<T>* p = first->Rlink;
	int count = 0;

	//逐个结点检测
	while (p != first) 
	{
		p = p->Rlink; 
		count++;
	}
	return count;
}


//搜索元素为x的结点，返回结点指针

template <class T>
LinkNode<T>* DbLinkedList<T>::Search(const T & x, int d) 
{
	//在双向循环链表中寻找其值等于x的结点, d=0按前驱方向,d≠0按后继方向。

	LinkNode<T>* current = (d == 0) ? first->Llink : first->Rlink;   //按d确定搜索方向

	while (current != first && current->data != x)	
		current = (d == 0) ? current->Llink : current->Rlink;

	if(current != first) 
		return current;//搜索成功
	else 
		return first;//搜索失败
}


template <class T>
void DbLinkedList<T>::push_back(const T& x)
{
	LinkNode<T>* current = first->Llink;
	LinkNode<T>* newNode = new LinkNode<T>(x);
	newNode->data = x;

	//插入
	newNode->Rlink = current->Rlink;   //链入rLink链
	current->Rlink = newNode;
	newNode->Rlink->Llink = newNode;   //链入lLink链
	newNode->Llink = current;

}



//插入元素
template <class T>
bool DbLinkedList<T>::Insert(int i, const T& x, int d) 
{
	//建立一个包含有值x的新结点, 并将其按 d 指定的
	//方向插入到第i个结点之后。


	//如果链表为空,插入第一个元素要将Rlink指向first
	//if (first->Rlink == nullptr)
	//{
	//	LinkNode<T>* newNode = new LinkNode<T>(x);
	//	first->Rlink = newNode;
	//	newNode->Rlink = first;
	//	newNode->Llink = first;

	//	return true;
	//}


	LinkNode<T>* current=first;
	int k = 0;
	while(current!=first&&k<i)
	{
		current = current->Rlink;
		k++;
	}

	//按d指示方向查找第i个结点

	if (current == first)             //插入失败
		return false;    

	LinkNode<T>* newNode = new LinkNode<T>(x);

	if (d == 0) {	  //前驱方向:插在第i个结点左侧
		newNode->Llink = current->Llink; //链入lLink链
		current->Llink = newNode;
		newNode->Llink->Rlink = newNode; //链入rLink链
		newNode->Rlink = current;
	}
	else {		      //后继方向:插在第i个结点后面
		newNode->Rlink = current->Rlink;   //链入rLink链
		current->Rlink = newNode;
		newNode->Rlink->Llink = newNode;   //链入lLink链
		newNode->Llink = current;
	}
	return true; 	    //插入成功
}





//删除值位置为i的元素
template <class  T>
bool DbLinkedList<T>::RemovePos(int i) 
{
	//在双向循环链表中按d所指方向删除第i个结点。

	LinkNode<T>* current = Locate(i);
	if (current == first) 
		return false;  //删除失败

	current->Rlink->Llink = current->Llink;
	current->Llink->Rlink = current->Rlink;

	delete current;    //删除

	return true;       
}

//删除值为x的元素
template <class  T>
bool DbLinkedList<T>::Remove(const T& x)
{
	//在双向循环链表中按d所指方向删除第i个结点。

	LinkNode<T>* current = Search(x,1);
	if (current == first)
		return false;  //删除失败

	current->Rlink->Llink = current->Llink;
	current->Llink->Rlink = current->Rlink;

	delete current;    //删除

	return true;
}






template <class  T>
LinkNode<T>* DbLinkedList<T>::Locate(int i) 
{
	//函数返回表中第 i 个元素的地址。若i < 0或 i 超
	//出表中结点个数，则返回first。

	if (i < 0)                    //i不合理
		return first;	

	LinkNode<T>* current = first->Rlink;  
	int k = 0;
	while (current != first && k < i )
	{
		current = current->Rlink;	
		k++;
	}

	return current;  //返回第 i 号结点地址或first
}


//取出位置为i的元素
template <class  T>
bool DbLinkedList<T>::getData(int i, T& x)
{
	LinkNode<T>* current = Locate(i);
	if (current == first)
		return false;

	x = current->data;
	return true;

}

template <class  T>
bool DbLinkedList<T>::setDataPos(int i,const T& x)
{
	LinkNode<T>* current = Locate(i);
	if (current == first)
		return false;

	current->data = x;
	return true;
}

template <class  T>
bool DbLinkedList<T>::setData(T& val,const T& x)
{
	LinkNode<T>* current = Search(val,0);
	if (current == first)
		return false;

	current->data = x;
	return true;
}