#include "rb_tree.h"
#include <iostream>
#include <queue>
#include <stack>


int GetMax(int high, int leftMax, int rightMax)
{
	int temp = (leftMax > rightMax) ? leftMax : rightMax;
	return (high > temp) ? high : temp;
}


//以结点x为中心进行左旋转
void RB_Tree::Leaf_Rotate(Tree_Node *x)
{
	Tree_Node *y = x->r_child;	//y<---right[x]
	x->r_child = y->l_child;		//right[x]<---left[y]

	if (y->l_child != Nil)		//y的左孩子不为空，则它的父亲为x
		y->l_child->parent = x;	//left[y]!=Nil,x<---parent[y]
	y->parent = x->parent;		//parent[y]<---parent[x]

	if (x->parent == Nil)		//x为根节点
		root = y;
	else if (x->parent->l_child == x)//x是其父亲的左孩子，将y插入到左孩子
		x->parent->l_child = y;
	else								//x是其父节点的右孩子，将y插入到右孩子
		x->parent->r_child = y;

	y->l_child = x;
	x->parent = y;

	x->max = GetMax(x->interval.high, x->l_child->max, x->r_child->max);
	y->max = GetMax(y->interval.high, y->l_child->max, y->r_child->max);
}

//以x为中心进行右旋转
void RB_Tree::Right_Rotate(Tree_Node *x)
{
	Tree_Node *y = x->l_child;
	x->l_child = y->r_child;

	if (y->r_child != Nil)	//y的右孩子不为空，则旋转后的右孩子的父亲为x
		y->r_child->parent = x;
	y->parent = x->parent;

	if (x->parent == Nil)	//x为根节点，则将新的根节点置为y
		root = y;
	else if (x->parent->l_child == x)//x是其父节点的左孩子，将y置为父节点的左孩子
		x->parent->l_child = y;
	else
		x->parent->r_child = y;

	y->r_child = x;
	x->parent = y;

	x->max = GetMax(x->interval.high, x->l_child->max, x->r_child->max);
	y->max = GetMax(y->interval.high, y->l_child->max, y->r_child->max);
}



//在红黑树中搜索关键字值为k的结点
bool RB_Tree::RB_Search(int k, Tree_Node *x)
{
	//红黑树是在二叉排序树的基础上建立的，所以也是有序的
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


//在红黑树中插入关键字值为k的结点
bool RB_Tree::RB_Insert(Tree_Node *k)
{
	Tree_Node *z = NULL;
	if (false)
	{
		cout << "含有关键字值为 " << k->key << " 的结点已存在，不重复插入" << endl;
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
		if (y == Nil)	//如果树为空
			root = k;
		else if (k->interval.low < y->interval.low)	//如果k结点值小于y结点值，则插入到左孩子，否则插入到右孩子
			y->l_child = k;
		else
			y->r_child = k;

		k->l_child = Nil;
		k->r_child = Nil;
		k->color = RED;				//将插入结点涂红
		if (k == root)				//如果k是根节点，则将k的父节点指向Nil
			k->parent = Nil;
		RB_Insert_Fixup(k);			//对插入的进行调整
	}
	return true;
}

//插入后调整红黑树结构,使插入新元素后的树满足红黑树的性质要求
void RB_Tree::RB_Insert_Fixup(Tree_Node *z)
{
	Tree_Node *y;
	while (z->parent->color == RED)	//z的父亲为红，z的祖父存在且为黑
	{
		if (z->parent == z->parent->parent->l_child)
		{
			y = z->parent->parent->r_child;
			if (y->color == RED)
			{
				//case 1 插入结点z的父亲是其祖父的左孩子 且z的叔叔结点为红。
				//处理策略：使z上升。
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				//case 2 插入结点z的父亲是其祖父的左孩子 且z的叔叔结点为黑，z是其父亲的右孩子
				//处理策略：转为case 3
				if (z == z->parent->r_child)
				{
					z = z->parent;
					Leaf_Rotate(z);
				}
				//case 3 插入结点z的父亲是其祖父的左孩子 且z的叔叔结点为黑，z是其父亲的左孩子
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
//利用数组A[]中的数据创建红黑树
void RB_Tree::RB_Create(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		Tree_Node *k = new Tree_Node(A[i]);
		if (RB_Insert(k))
			cout << "插入 " << A[i] << " 成功" << endl;
	}
	cout << "红黑树创建完成" << endl;
}
*/

void RB_Tree::RB_Create(int low, int high)
{
	Tree_Node *k = new Tree_Node(low,high);
	if (RB_Insert(k))
		cout << "插入 " << "{" << low << "," << high << "}" << " 成功" << endl;
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


//层次遍历红黑树，并且输出各个结点的颜色
void RB_Tree::LevelOrder_Traverse()
{
	Tree_Node *y = root;
	queue<Tree_Node *> qu;	//借助队列
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

//中序遍历红黑树各结点的关键字值
void RB_Tree::InOrder_Traverse()
{
	Tree_Node *y;
	stack<Tree_Node *> s;	//借助栈
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
