#pragma once

//��������Ķ���
template<class T>
struct LinkNode
{
	int data;			       	    //������
	LinkNode<T>* Llink, * Rlink;     	//��ָ����

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
	LinkNode<T>*first;	 //��ͷָ��

public:
	DbLinkedList() 
	{ 
		first = new LinkNode<T>; 
		first->Rlink = first;
		first->Llink = first;
	}  //���캯��
	DbLinkedList(const int& x) 
	{ 
		first = new LinkNode<T>(x); 
		first->Rlink = first;
		first->Llink = first;
	}

	~DbLinkedList() { makeEmpty(); }             //��������


	void makeEmpty();	     //��������Ϊ�ձ�
	int Length() const;	     //��������ĳ���
	


	LinkNode<T>* getHead()const { return first; }    //���ظ���ͷ����ַ
	LinkNode<T>* Search(const T& x, int d);	         //������xԪ��
	LinkNode<T>* Locate(int i);                      //��λ

	bool getData(int i, T& x);   //ȡ����iԪ��ֵ

	bool setDataPos(int i, const T& x);		   //���µ�iԪ��ֵ
	bool setData(T& val, const T& x);        //�ı�Ԫ��x��ֵ

	bool Insert(int i, const T& x,int d);//�ڵ�iԪ�غ����
	void push_back(const T& x);          //���

	bool RemovePos(int i);	                 //ɾ����i��Ԫ��
	bool Remove(const T& x);
	bool IsEmpty() const 		         //�б�շ�
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

