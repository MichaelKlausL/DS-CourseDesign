#pragma once

//链表结点类的定义
template<class T>
struct LinkNode
{
	int data;			       	    //数据域
	LinkNode<T>* Llink, * Rlink;     	//链指针域

	LinkNode<T>(LinkNode<T>* ptr = nullptr)
	{
		data = 0;
		Llink = ptr;
		Rlink = ptr;
	}
	LinkNode<T>(const T& item, LinkNode* ptr = nullptr)
	{
		data = item;
		Llink = ptr;
		Rlink = ptr;
	}
};



template<class T>
class DbLinkedList
{
private:
	LinkNode<T>*first;	 //表头指针

public:
	DbLinkedList() 
	{ 
		first = new LinkNode<T>; 
		first->Rlink = first;
		first->Llink = first;
	}  //构造函数
	DbLinkedList(const int& x) 
	{ 
		first = new LinkNode<T>(x); 
		first->Rlink = first;
		first->Llink = first;
	}

	~DbLinkedList() { makeEmpty(); }             //析构函数


	void makeEmpty();	     //将链表置为空表
	int Length() const;	     //计算链表的长度
	


	LinkNode<T>* getHead()const { return first; }    //返回附加头结点地址
	LinkNode<T>* Search(const T& x, int d);	         //搜索含x元素
	LinkNode<T>* Locate(int i);                      //定位

	bool getData(int i, T& x);   //取出第i元素值

	bool setDataPos(int i, const T& x);		   //更新第i元素值
	bool setData(T& val, const T& x);        //改变元素x的值

	bool Insert(int i, const T& x,int d);//在第i元素后插入
	void push_back(const T& x);          //后插

	bool RemovePos(int i);	                 //删除第i个元素
	bool Remove(const T& x);
	bool IsEmpty() const 		         //判表空否
	{
		return first->Rlink == first ? true : false;
	}

	bool isMember(const T& x)
	{
		LinkNode<T>* current = Search(x,1);
		if (current == first)
			return false;
		return true;
	}


};

