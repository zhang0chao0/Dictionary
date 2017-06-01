#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "Stack.h"
using namespace std;

struct AVLNode
{
	int bf;                            //ƽ������
	CString letter;                    //����
	CString note;                      //ע��
	AVLNode* left;                     //��ָ��
	AVLNode* right;                    //��ָ��
	AVLNode() :left(nullptr), right(nullptr), bf(0){};
	bool operator<(AVLNode& R){ return letter<R.letter; }
	bool operator>(AVLNode& R){ return letter>R.letter; }
	bool operator<=(AVLNode& R){ return letter <= R.letter; }
	bool operator>=(AVLNode& R){ return letter >= R.letter; }
	bool operator==(AVLNode& R){ return letter == R.letter; }
};


class AVLTree
{
protected:
	AVLNode* root;
	AVLNode* Search(CString x, AVLNode* ptr);      //�ݹ�����
	void makeEmpty(AVLNode*& ptr);                //�ݹ��ÿ�
	bool Insert(AVLNode*& ptr,AVLNode* e1);       //�ݹ����
	bool Remove(AVLNode*& ptr, CString x);         //�ݹ�ɾ��
	//****************************��ת
	void RotateL(AVLNode*& ptr);                  //����
	void RotateR(AVLNode*& ptr);                  //�ҵ���
	void RotateLR(AVLNode*& ptr);                 //�������˫��
	void RotateRL(AVLNode*& ptr);                 //���Һ���˫��

public:
	AVLTree(){ root = nullptr; }
	~AVLTree(){ makeEmpty(root); };
	bool Insert(AVLNode* e1) { return Insert(root, e1); } //����
	bool Remove(CString e1){return Remove(root,e1);}       //ɾ��
	AVLNode* Search(CString x){ return Search(x,root); }   //����
	//�������
	void midOrder(AVLNode*subTree,CString find);                      
	void midOrder(CString find)       
	{
		midOrder(root,find);
	}
};


#endif