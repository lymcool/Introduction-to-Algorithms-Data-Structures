#include "AVL.h"
#include<iostream>

using namespace std;

void main() {

  avl<int> avltree ;
  avltree.insert(32);
	avltree.insert(21);
	avltree.insert(46);
	avltree.insert(54);
	avltree.insert(16);
	avltree.insert(38);
	avltree.insert(70);
	cout << "inorder tree walk is: ";

	avlNode<int>* root = avltree.getRoot();
	avltree.preOrderTraverse(root);
	//avltree.inorder_tree_traverse();
	//avltree.preOrder(root);
	
	cout << endl;
	cout << "root of the tree is: "<<root->key<<endl;

		system("pause");
		exit(0);
}
