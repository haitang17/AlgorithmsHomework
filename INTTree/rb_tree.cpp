#include "rb_tree.h"
#include <iostream>
#include <queue>
#include <stack>


int GetMax(int high, int leftMax, int rightMax)
{
	int temp = (leftMax > rightMax) ? leftMax : rightMax;
	return (high > temp) ? high : temp;
}


//�Խ��xΪ���Ľ�������ת
void RB_Tree::Leaf_Rotate(Tree_Node *x)
{
	Tree_Node *y = x->r_child;	//y<---right[x]
	x->r_child = y->l_child;		//right[x]<---left[y]

	if (y->l_child != Nil)		//y�����Ӳ�Ϊ�գ������ĸ���Ϊx
		y->l_child->parent = x;	//left[y]!=Nil,x<---parent[y]
	y->parent = x->parent;		//parent[y]<---parent[x]

	if (x->parent == Nil)		//xΪ���ڵ�
		root = y;
	else if (x->parent->l_child == x)//x���丸�׵����ӣ���y���뵽����
		x->parent->l_child = y;
	else								//x���丸�ڵ���Һ��ӣ���y���뵽�Һ���
		x->parent->r_child = y;

	y->l_child = x;
	x->parent = y;

	x->max = GetMax(x->interval.high, x->l_child->max, x->r_child->max);
	y->max = GetMax(y->interval.high, y->l_child->max, y->r_child->max);
}

//��xΪ���Ľ�������ת
void RB_Tree::Right_Rotate(Tree_Node *x)
{
	Tree_Node *y = x->l_child;
	x->l_child = y->r_child;

	if (y->r_child != Nil)	//y���Һ��Ӳ�Ϊ�գ�����ת����Һ��ӵĸ���Ϊx
		y->r_child->parent = x;
	y->parent = x->parent;

	if (x->parent == Nil)	//xΪ���ڵ㣬���µĸ��ڵ���Ϊy
		root = y;
	else if (x->parent->l_child == x)//x���丸�ڵ�����ӣ���y��Ϊ���ڵ������
		x->parent->l_child = y;
	else
		x->parent->r_child = y;

	y->r_child = x;
	x->parent = y;

	x->max = GetMax(x->interval.high, x->l_child->max, x->r_child->max);
	y->max = GetMax(y->interval.high, y->l_child->max, y->r_child->max);
}



//�ں�����������ؼ���ֵΪk�Ľ��
bool RB_Tree::RB_Search(int k, Tree_Node *x)
{
	//��������ڶ����������Ļ����Ͻ����ģ�����Ҳ�������
	x = root;
	while (x != Nil)
	{
		if (x->key == k)
			return true;
		else if (x->key < k)
			x = x->r_child;
		else
			x = x->l_child;
	}
	return false;
}


//�ں�����в���ؼ���ֵΪk�Ľ��
bool RB_Tree::RB_Insert(Tree_Node *k)
{
	Tree_Node *z = NULL;
	if (false)
	{
		cout << "���йؼ���ֵΪ " << k->key << " �Ľ���Ѵ��ڣ����ظ�����" << endl;
		return false;
	}
	else
	{
		Tree_Node *x = root;
		Tree_Node *y = Nil;
		k->max = k->interval.high;
		while (x != Nil)
		{
			x->max = max(k->interval.high, x->max);
			y = x;
			if (k->interval.low < x->interval.low)
				x = x->l_child;
			else
				x = x->r_child;
		}
		k->parent = y;
		if (y == Nil)	//�����Ϊ��
			root = k;
		else if (k->interval.low < y->interval.low)	//���k���ֵС��y���ֵ������뵽���ӣ�������뵽�Һ���
			y->l_child = k;
		else
			y->r_child = k;

		k->l_child = Nil;
		k->r_child = Nil;
		k->color = RED;				//��������Ϳ��
		if (k == root)				//���k�Ǹ��ڵ㣬��k�ĸ��ڵ�ָ��Nil
			k->parent = Nil;
		RB_Insert_Fixup(k);			//�Բ���Ľ��е���
	}
	return true;
}

//��������������ṹ,ʹ������Ԫ�غ������������������Ҫ��
void RB_Tree::RB_Insert_Fixup(Tree_Node *z)
{
	Tree_Node *y;
	while (z->parent->color == RED)	//z�ĸ���Ϊ�죬z���游������Ϊ��
	{
		if (z->parent == z->parent->parent->l_child)
		{
			y = z->parent->parent->r_child;
			if (y->color == RED)
			{
				//case 1 ������z�ĸ��������游������ ��z��������Ϊ�졣
				//������ԣ�ʹz������
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				//case 2 ������z�ĸ��������游������ ��z��������Ϊ�ڣ�z���丸�׵��Һ���
				//������ԣ�תΪcase 3
				if (z == z->parent->r_child)
				{
					z = z->parent;
					Leaf_Rotate(z);
				}
				//case 3 ������z�ĸ��������游������ ��z��������Ϊ�ڣ�z���丸�׵�����
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				Right_Rotate(z->parent->parent);
			}

		}
		else
		{
			//z->parent == z->parent->parent->r_child
			y = z->parent->parent->l_child;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->l_child)
				{
					z = z->parent;
					Right_Rotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				Leaf_Rotate(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

/*
//��������A[]�е����ݴ��������
void RB_Tree::RB_Create(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		Tree_Node *k = new Tree_Node(A[i]);
		if (RB_Insert(k))
			cout << "���� " << A[i] << " �ɹ�" << endl;
	}
	cout << "������������" << endl;
}
*/

void RB_Tree::RB_Create(int low, int high)
{
	Tree_Node *k = new Tree_Node(low,high);
	if (RB_Insert(k))
		cout << "���� " << "{" << low << "," << high << "}" << " �ɹ�" << endl;
}



Tree_Node* RB_Tree::IntervalSearch(int low, int high, RB_Tree tree)
{
	Tree_Node* x = tree.root;
	while (x != Nil && (x->interval.high < low || high < x->interval.low))
	{
		if (x->l_child != Nil && x->l_child->max >= low)
			x = x->l_child;
		else
			x = x->r_child;
	}
	return x;
}


//��α���������������������������ɫ
void RB_Tree::LevelOrder_Traverse()
{
	Tree_Node *y = root;
	queue<Tree_Node *> qu;	//��������
	qu.push(y);
	while (!qu.empty())
	{
		y = qu.front();
		qu.pop();
		cout << "{" << y->interval.low << "," << y->interval.high << "}" << " ,color= ";
		if (y->color == BLACK)
			cout << "BLACK" << endl;
		else
			cout << "RED" << endl;
		if (y->l_child != Nil)
			qu.push(y->l_child);
		if (y->r_child != Nil)
			qu.push(y->r_child);
	}
}

//�����������������Ĺؼ���ֵ
void RB_Tree::InOrder_Traverse()
{
	Tree_Node *y;
	stack<Tree_Node *> s;	//����ջ
	y = root;
	while ((y != Nil) || (!s.empty()))
	{
		if (y != Nil)
		{
			s.push(y);
			y = y->l_child;
		}
		else
		{
			y = s.top();
			s.pop();
			cout << "{" << y->interval.low << "," << y->interval.high << "}";
			y = y->r_child;
		}
	}
}
