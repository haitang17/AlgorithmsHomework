#include "rb_tree.h"

int main()
{
	int A[6] = { 41,38,31,12,19,8 };
	RB_Tree tree;
	tree.RB_Create(A, 6);
	cout << "���ղ�α�����˳�����������ṹ" << endl;
	tree.LevelOrder_Traverse();
	cout << endl;
	cout << "��������������";
	tree.InOrder_Traverse();
	cout << endl;

	int k;
	while (1)
	{
		cout << "����Ҫ���������Ĺؼ��ֵ�ֵ������-1��ʾ�������룺";
		cin >> k;
		if (k == -1)
			break;
		else
		{
			Tree_Node *t = new Tree_Node(k);
			if (tree.RB_Insert(t))
				cout << "ֵΪ " << k << " �Ľ�����ɹ�" << endl;
		}
	}

	cout << "���ղ�α�����˳�����������ṹ" << endl;
	tree.LevelOrder_Traverse();
	cout << endl;
	cout << "��������������";
	tree.InOrder_Traverse();
	cout << endl;

	getchar();
	getchar();

	return 0;
}
