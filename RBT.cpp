//#include <iostream>
//#include "RBT.h"
//
//using namespace std;
//void main() {
//	int a[] = {10,40,30,60,90,70,20,50,80};
//	int check_insert = 0;
//	int check_remove = 0;
//	int i;
//	int ilen = (sizeof(a)) / (sizeof(a[0]));
//	RBTTree<int>* tree=new RBTTree<int>();
//	cout << "ԭʼ���ݣ�";
//	for (i = 0;i < ilen;i++) 
//		cout << a[i] << " ";
//	cout << endl;
//
//		for (i = 0;i < ilen;i++) {
//			tree->insert(a[i]);
//			if (check_insert) {
//				cout << "��ӵĽڵ㣺" << a[i] << endl;
//				cout << "������ϸ��Ϣ��" << endl;
//				tree->print();
//				cout << endl;
//			}
//		}
//		cout << "ǰ�������";
//		tree->preOrder();
//		cout << "\n���������";
//		tree->inOrder();
//		cout << "\n���������";
//		tree->postOrder();
//		cout << endl;
//		cout << "��Сֵ: " << tree->minimum()<< endl;
//		cout << "���ֵ: " << tree->maximum() << endl;
//		cout << "������ϸ��Ϣ: " << endl;
//		tree->print();
//   
//	if (check_remove)
//	{
//		       for (i = 0; i<ilen; i++)
//			        {
//			           tree->remove(a[i]);
//                       cout << "== ɾ���ڵ�: " << a[i] << endl;
//			           cout << "== ������ϸ��Ϣ: " << endl;
//			           tree->print();
//			           cout << endl;
//			    }
//		    }
//	
//	    tree->destroy();
//	
//}
//
