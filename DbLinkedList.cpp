#include "DbLinkedList.h"












//�������
template<class T>
void DbLinkedList<T>::makeEmpty()
{
	LinkNode<T>* del = first->Rlink;             //�ͷ����пռ�
	while (first->Rlink != first)
	{
		del = first->Rlink;
		first->Rlink = del->Rlink;
		delete del;
	}

	delete first;                            //ɾ��ͷָ��
}


//��������
template <class T>
int DbLinkedList<T> ::Length()const {
	//���ָ�� p ָʾ��һ�����
	LinkNode<T>* p = first->Rlink;
	int count = 0;

	//��������
	while (p != first) 
	{
		p = p->Rlink; 
		count++;
	}
	return count;
}


//����Ԫ��Ϊx�Ľ�㣬���ؽ��ָ��

template <class T>
LinkNode<T>* DbLinkedList<T>::Search(const T & x, int d) 
{
	//��˫��ѭ��������Ѱ����ֵ����x�Ľ��, d=0��ǰ������,d��0����̷���

	LinkNode<T>* current = (d == 0) ? first->Llink : first->Rlink;   //��dȷ����������

	while (current != first && current->data != x)	
		current = (d == 0) ? current->Llink : current->Rlink;

	if(current != first) 
		return current;//�����ɹ�
	else 
		return first;//����ʧ��
}


template <class T>
void DbLinkedList<T>::push_back(const T& x)
{
	LinkNode<T>* current = first->Llink;
	LinkNode<T>* newNode = new LinkNode<T>(x);
	newNode->data = x;

	//����
	newNode->Rlink = current->Rlink;   //����rLink��
	current->Rlink = newNode;
	newNode->Rlink->Llink = newNode;   //����lLink��
	newNode->Llink = current;

}



//����Ԫ��
template <class T>
bool DbLinkedList<T>::Insert(int i, const T& x, int d) 
{
	//����һ��������ֵx���½��, �����䰴 d ָ����
	//������뵽��i�����֮��


	//�������Ϊ��,�����һ��Ԫ��Ҫ��Rlinkָ��first
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

	//��dָʾ������ҵ�i�����

	if (current == first)             //����ʧ��
		return false;    

	LinkNode<T>* newNode = new LinkNode<T>(x);

	if (d == 0) {	  //ǰ������:���ڵ�i��������
		newNode->Llink = current->Llink; //����lLink��
		current->Llink = newNode;
		newNode->Llink->Rlink = newNode; //����rLink��
		newNode->Rlink = current;
	}
	else {		      //��̷���:���ڵ�i��������
		newNode->Rlink = current->Rlink;   //����rLink��
		current->Rlink = newNode;
		newNode->Rlink->Llink = newNode;   //����lLink��
		newNode->Llink = current;
	}
	return true; 	    //����ɹ�
}





//ɾ��ֵλ��Ϊi��Ԫ��
template <class  T>
bool DbLinkedList<T>::RemovePos(int i) 
{
	//��˫��ѭ�������а�d��ָ����ɾ����i����㡣

	LinkNode<T>* current = Locate(i);
	if (current == first) 
		return false;  //ɾ��ʧ��

	current->Rlink->Llink = current->Llink;
	current->Llink->Rlink = current->Rlink;

	delete current;    //ɾ��

	return true;       
}

//ɾ��ֵΪx��Ԫ��
template <class  T>
bool DbLinkedList<T>::Remove(const T& x)
{
	//��˫��ѭ�������а�d��ָ����ɾ����i����㡣

	LinkNode<T>* current = Search(x,1);
	if (current == first)
		return false;  //ɾ��ʧ��

	current->Rlink->Llink = current->Llink;
	current->Llink->Rlink = current->Rlink;

	delete current;    //ɾ��

	return true;
}






template <class  T>
LinkNode<T>* DbLinkedList<T>::Locate(int i) 
{
	//�������ر��е� i ��Ԫ�صĵ�ַ����i < 0�� i ��
	//�����н��������򷵻�first��

	if (i < 0)                    //i������
		return first;	

	LinkNode<T>* current = first->Rlink;  
	int k = 0;
	while (current != first && k < i )
	{
		current = current->Rlink;	
		k++;
	}

	return current;  //���ص� i �Ž���ַ��first
}


//ȡ��λ��Ϊi��Ԫ��
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