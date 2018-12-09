#include "rb_tree.h"

int main()
{
	//int A[6] = { 41,38,31,12,19,8 };
	RB_Tree tree;
	tree.RB_Create(16, 21);
	tree.RB_Create(8, 9);
	tree.RB_Create(25, 30);
	tree.RB_Create(5, 8);
	tree.RB_Create(15, 23);
	tree.RB_Create(17, 19);
	tree.RB_Create(26, 26);
	cout << endl;

	cout << "按照层次遍历的顺序输出红黑树结构" << endl;
	tree.LevelOrder_Traverse();
	cout << endl;
	cout << "中序遍历红黑树：";
	tree.InOrder_Traverse();
	cout << endl;

	RB_Tree p;
	int a = 0;
	int b = 0;
	cout << "\n请输入查询的区间：" << endl;
	cin >> a >> b;
	Tree_Node *r = p.IntervalSearch(a, b, tree);
	cout << "重叠区间为：\n" << endl;
	cout << "{" << r->interval.low << "," << r->interval.high << "}";

	getchar();
	getchar();

	return 0;
}
