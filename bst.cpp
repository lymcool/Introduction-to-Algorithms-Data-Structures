#include "bst.h"
void main() {

	BinarySearchTree<int> bstTree;
	bstTree.tree_insert(32);
	bstTree.tree_insert(21);
	bstTree.tree_insert(46);
	bstTree.tree_insert(54);
	bstTree.tree_insert(16);
	bstTree.tree_insert(38);
	bstTree.tree_insert(70);
	cout << "inorder tree walk is: ";
	bstTree.inorder_tree_traverse();

	BinarySearchTreeNode<int>* proot= bstTree.getRoot();
	cout << "max is" << bstTree.tree_max(proot)->key<< endl;
	cout << "min is" << bstTree.tree_min(proot)->key << endl;

	BinarySearchTreeNode<int>* ptnode;
	ptnode = bstTree.tree_search(38);
	if (ptnode)
		cout << "38 is exist in the binary tree." << endl;
	else
		cout << "38 is exist in the binary tree." << endl;

	cout << "the successor of 38 is: " << bstTree.tree_successor(38)->key << endl;
	cout << "the predecessor of 38 is:" << bstTree.tree_preccesor(38)->key << endl;
	if (bstTree.tree_remove(46) == 0)
		      cout << "delete 46 successfully" << endl;
	   else
		        cout << "delete 46 failed" << endl;
	cout << "inorder tree walk is: ";
	bstTree.inorder_tree_traverse();
	system("pause");
	exit(0);


}