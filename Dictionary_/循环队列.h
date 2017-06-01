#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <assert.h>

template<typename T>
class Queue
{
protected:
	int rear, front;                //��β���ͷָ��
	T *elements;                    //����
	int maxSize;                    //�����������Ԫ��
public:
	Queue(int sz = 100);            //���캯��
	~Queue(){ delete[]elements;}    //��������
	bool EnQueue(const T&x);        //������
	bool DeQueue(T &x);             //������
	void makeEmpty(){ front = rear = 0; }
	bool IsEmpty()const { return (front == rear) ? true : false; }
	bool IsFull()const { return ((rear + 1) % maxSize == front) ? true : false; }
	int getSize()const { return (rear - front + maxSize) % maxSize; }
	int getFront(){ return front; }
	int getRear(){ return rear; }
	T Get_element(int i){ return elements[i]; }
	T Get_front(){ return elements[front]; }
	T Get_rear(){ return elements[rear-1]; }
};
//*******************************���캯��
template<typename T>
Queue<T>::Queue(int sz) :front(0), rear(0), maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements!=nullptr);
}
//******************************����δ����������
template<typename T>
bool Queue<T>::EnQueue(const T&x)
{
	if (IsFull())
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}
//******************************���в�Ϊ�գ�������
template<typename T>
bool Queue<T>::DeQueue(T &x)
{
	if (IsEmpty())
		return false;
	x=elements[front];
	front = (front + 1) % maxSize;
	return true;
}


#endif
