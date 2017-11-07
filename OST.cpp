////http://blog.csdn.net/lu597203933/article/details/43459035

#include <iostream>
#include "OST.h"

using namespace std;

void main() {
	int a[10] = { 5,4,6, 7,2,4, 1, 8, 5, 10 };
	OSRBTree osbrt(a[0]);
	for (int i = 1;i < 10;i++)
		osbrt.insertOSRBTree(osbrt.root,a[i]);
	cout << "中序遍历的结果："<<endl;
	osbrt.inorderOSRBTree(osbrt.root);
	cout << endl;

	int ith = 6;
	BSTNode* rank = osbrt.os_select(osbrt.root, ith);
	if (rank)
		cout << "排名" << ith << ":" << rank->val << endl;
	else
		cout << "排名" << ith << "不存在。" << rank->val << endl;

	int x = 6;
	cout << x << "排名为：";
cout << osbrt.os_rank(osbrt.root,x) << endl;
	system("pause");
}
