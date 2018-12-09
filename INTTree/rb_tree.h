#pragma once
#include <iostream>

using namespace std;



//����������ɫ��Ϊȫ�ֱ���
enum RB_COLOR { BLACK, RED };

typedef struct Interval {
	int low;
	int high;

}Interval;

class RB_Tree;   //ǰ������

//������ڵ���
class Tree_Node
{

	friend RB_Tree;

private:
	//����������������
	RB_COLOR color;
	int key;
	Tree_Node *parent;
	Tree_Node *l_child;
	Tree_Node *r_child;

public:
	Interval interval;
	int max;

public:
	Tree_Node() :color(BLACK), parent(NULL), l_child(NULL), r_child(NULL)//Ĭ�Ϲ��캯��
	{
	}
	Tree_Node(int l, int h) :color(BLACK), key(0), parent(NULL), l_child(NULL), r_child(NULL)//���캯��
	{
		interval.low = l;
		interval.high = h;
	}
	Tree_Node(const Tree_Node &p)  //�������캯��
	{
		color = p.color;
		key = p.key;
		l_child = p.l_child;
		r_child = p.r_child;
		parent = p.parent;
	}
	~Tree_Node()
	{
		parent = 0;
		l_child = 0;
		r_child = 0;
	}
};

//�������
class RB_Tree
{
private:
	Tree_Node *root; //��ָ��
	Tree_Node *Nil; //�ڱ����ָ��
public:
	RB_Tree()
	{
		Nil = new Tree_Node();	//�ڱ�������ɫ�Ǻ�ɫ��
		Nil->parent = Nil;
		Nil->l_child = Nil;
		Nil->r_child = Nil;
		Nil->interval.low = 0;
		Nil->interval.high = 0;
		Nil->max = 0;
		root = Nil;
	}
	~RB_Tree()
	{
		delete Nil;
		Nil = NULL;
		root = NULL;
	}

	void Leaf_Rotate(Tree_Node *x);		 //����ת
	void Right_Rotate(Tree_Node *x);	//����ת

	bool RB_Search(int k, Tree_Node *x);     //����

	bool RB_Insert(Tree_Node *x);     //����
	void RB_Insert_Fixup(Tree_Node *z);   //��������������ṹ
	Tree_Node *IntervalSearch(int low, int high, RB_Tree tree);

	//void RB_Create(int A[], int n);   //���������
	void RB_Create(int low, int high);   //���������

	void LevelOrder_Traverse();  //��α��������
	void InOrder_Traverse();  //������������
};
