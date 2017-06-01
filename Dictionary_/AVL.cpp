#include "stdafx.h"
#include "AVL.h"

//************************实现部分

//*************************左单旋
void AVLTree::RotateL(AVLNode*& ptr)
{
	AVLNode* subL = ptr;
	ptr = subL->right;
	subL->right = ptr->left;
	ptr->left = subL;
	ptr->bf = subL->bf = 0;
}
//*************************右单旋
void AVLTree::RotateR(AVLNode*& ptr)
{
	AVLNode* subR = ptr;
	ptr = subR->left;
	subR->left = ptr->right;
	ptr->right = subR;
	ptr->bf = subR->bf = 0;
}
//************************先左后右双旋
void AVLTree::RotateLR(AVLNode*& ptr)
{
	AVLNode* subR = ptr;
	AVLNode* subL = subR->left;
	ptr = subL->right;
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf <= 0)
		subL->bf = 0;
	else
		subL->bf = -1;
	subR->left = ptr->right;
	ptr->right = subR;
	if (ptr->bf == -1)
		subR->bf = 1;
	else
		subR->bf = 0;
	ptr->bf = 0;
}
//**************************先右后左双旋
void AVLTree::RotateRL(AVLNode*& ptr)
{
	AVLNode* subL = ptr;
	AVLNode* subR = subL->right;
	ptr = subR->left;
	subR->left = ptr->right;
	ptr->right = subR;
	if (ptr->bf >= 0)
		subR->bf = 0;
	else
		subR->bf = 1;
	subL->right = ptr->left;
	ptr->left = subL;
	if (ptr->bf == 1)
		subL->bf = -1;
	else
		subL->bf = 0;
	ptr->bf = 0;
}

//**************************搜索
AVLNode* AVLTree::Search(CString x, AVLNode* ptr)
{
	if (ptr == nullptr)
		return nullptr;
	else if (x < ptr->letter)
		return Search(x, ptr->left);
	else if (x > ptr->letter)
		return Search(x, ptr->right);
	else
		return ptr;
}

//**************************插入
bool AVLTree::Insert(AVLNode*& ptr, AVLNode* e1)
{
	AVLNode* pr = nullptr, *p = ptr;
	AVLNode* q = nullptr;
	int d;
	Stack<AVLNode*>st;
	//先找点是否存在，已存在就不插入了
	while (p != nullptr)
	{
		if (e1->letter == p->letter)
			return false;
		pr = p;
		st.Push(pr);
		if (e1->letter < p->letter)
			p = p->left;
		else
			p = p->right;
	}
	p = new AVLNode;
	p->letter = e1->letter;
	p->note = e1->note;
	//若为空树
	if (pr == nullptr)
	{
		ptr = p;
		return true;
	}
	if (e1->letter < pr->letter)
		pr->left = p;
	else
		pr->right = p;
	while (st.IsEmpty() == false)
	{
		st.Pop(pr);
		if (p == pr->left)
			pr->bf--;
		else
			pr->bf++;
		if (pr->bf == 0)
			break;
		if (pr->bf == 1 || pr->bf == -1)
			p = pr;
		else
		{
			d = (pr->bf < 0) ? -1 : 1;
			if (p->bf == d)
			{
				if (d == -1)
					RotateR(pr);
				else
					RotateL(pr);
			}
			else
			{
				if (d == -1)
					RotateLR(pr);
				else
					RotateRL(pr);
			}
			break;
		}
	}
	if (st.IsEmpty() == true)
		ptr = pr;
	else
	{
		st.getTop(q);
		if (q->letter > pr->letter)
			q->left = pr;
		else
			q->right = pr;
	}
	return true;
}

//**************************树的析构
void AVLTree::makeEmpty(AVLNode*& ptr)
{
	if (ptr != nullptr)
	{
		makeEmpty(ptr->left);
		makeEmpty(ptr->right);
		delete ptr;
	}
}

//***********************中序遍历
void AVLTree::midOrder(AVLNode*subTree,CString find)
{
	if (subTree != nullptr)
	{
		midOrder(subTree->left,find);
		//找到子串压栈
		if (subTree->letter.Find(find)!=-1)

		midOrder(subTree->right,find);
	}
}

//*************************删除
bool AVLTree::Remove(AVLNode*& ptr, CString x)
{
	AVLNode* pr = nullptr;
	AVLNode* p = ptr;
	AVLNode* q = nullptr;
	AVLNode* ppr = nullptr;
	int d, dd = 0;
	Stack<AVLNode*>st;
	while (p != nullptr)
	{
		//找到即停止搜索
		if (x == p->letter)
			break;
		pr = p;
		st.Push(pr);
		if (x < p->letter)
			p = p->left;
		else
			p = p->right;
	}
	//未找到
	if (p == nullptr)
		return false;
	//被删除的结点有两个子女
	if (p->left != nullptr&&p->right != nullptr)
	{
		pr = p;
		st.Push(pr);
		q = p->left;
		while (q->right != nullptr)
		{
			pr = q;
			st.Push(pr);
			q = q->right;
		}
		p->letter = q->letter;
		p->note = q->note;
		p = q;
	}
	//被删除的结点只有一个子女
	if (p->left != nullptr)
		q = p->left;
	else
		q = p->right;
	//被删除的是根结点
	if (pr == nullptr)
		ptr = q;
	else
	{
		if (pr->left == p)
			pr->left = q;
		else
			pr->right = q;
		while (st.IsEmpty() == false)
		{
			st.Pop(pr);
			if (pr->right == q)
				pr->bf--;
			else
				pr->bf++;
			if (st.IsEmpty() == false)
			{
				st.getTop(ppr);
				dd = (ppr->left == pr) ? -1 : 1;
			}
			else
				dd = 0;
			if (pr->bf == 1 || pr->bf == -1)
				break;
			if (pr->bf != 0)
			{
				if (pr->bf < 0)
				{
					d = -1;
					q = pr->left;
				}
				else
				{
					d = 1;
					q = pr->right;
				}
				if (q->bf == 0)
				{
					if (d == -1)
					{
						RotateR(pr);
						pr->bf = 1;
						pr->left->bf = -1;
					}
					else
					{
						RotateL(pr);
						pr->bf = -1;
						pr->right->bf = 1;
					}
					break;
				}
				if (q->bf == d)
				{
					if (d == -1)
						RotateR(pr);
					else
						RotateL(pr);
				}
				else
				{
					if (d == -1)
						RotateLR(pr);
					else
						RotateRL(pr);
				}
				if (dd == -1)
					ppr->left = pr;
				else if (dd == 1)
					ppr->right = pr;
			}
			q = pr;
		}
		if (st.IsEmpty() == true)
			ptr = pr;
	}
	delete p;
	return true;
}