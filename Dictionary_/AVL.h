#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "Stack.h"
using namespace std;

struct AVLNode
{
	int bf;                            //平衡因子
	CString letter;                    //单词
	CString note;                      //注释
	AVLNode* left;                     //左指针
	AVLNode* right;                    //右指针
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
	AVLNode* Search(CString x, AVLNode* ptr);      //递归搜索
	void makeEmpty(AVLNode*& ptr);                //递归置空
	bool Insert(AVLNode*& ptr,AVLNode* e1);       //递归插入
	bool Remove(AVLNode*& ptr, CString x);         //递归删除
	//****************************旋转
	void RotateL(AVLNode*& ptr);                  //左单旋
	void RotateR(AVLNode*& ptr);                  //右单旋
	void RotateLR(AVLNode*& ptr);                 //先左后右双旋
	void RotateRL(AVLNode*& ptr);                 //先右后左双旋

public:
	AVLTree(){ root = nullptr; }
	~AVLTree(){ makeEmpty(root); };
	bool Insert(AVLNode* e1) { return Insert(root, e1); } //插入
	bool Remove(CString e1){return Remove(root,e1);}       //删除
	AVLNode* Search(CString x){ return Search(x,root); }   //查找
	//中序遍历
	void midOrder(AVLNode*subTree,CString find);                      
	void midOrder(CString find)       
	{
		midOrder(root,find);
	}
};


#endif