#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <assert.h>

template<typename T>
class Queue
{
protected:
	int rear, front;                //队尾与队头指针
	T *elements;                    //数组
	int maxSize;                    //队列最大容纳元素
public:
	Queue(int sz = 100);            //构造函数
	~Queue(){ delete[]elements;}    //析构函数
	bool EnQueue(const T&x);        //进队列
	bool DeQueue(T &x);             //出队列
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
//*******************************构造函数
template<typename T>
Queue<T>::Queue(int sz) :front(0), rear(0), maxSize(sz)
{
	elements = new T[maxSize];
	assert(elements!=nullptr);
}
//******************************队列未满，进队列
template<typename T>
bool Queue<T>::EnQueue(const T&x)
{
	if (IsFull())
		return false;
	elements[rear] = x;
	rear = (rear + 1) % maxSize;
	return true;
}
//******************************队列不为空，出队列
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
