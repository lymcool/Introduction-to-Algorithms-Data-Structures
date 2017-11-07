#pragma once
//http://www.cnblogs.com/zhoutaotao/p/4096237.html

#include <iostream>
#include<stack>
using namespace std;

template<class T>
class BinarySearchTreeNode {
public:
	T key;
	BinarySearchTreeNode<T>* left;
	BinarySearchTreeNode<T>* right;
	BinarySearchTreeNode<T>* parent;
};
template<class T>
class BinarySearchTree {
public:
	BinarySearchTree();
	void tree_insert(const T& elem);
	int tree_remove(const T& elem);
	BinarySearchTreeNode<T>* tree_search(const T& elem)const;
	BinarySearchTreeNode<T>* tree_max(BinarySearchTreeNode<T>* root)const;
	BinarySearchTreeNode<T>* tree_min(BinarySearchTreeNode<T>* root)const;
	BinarySearchTreeNode<T>* tree_preccesor(const T& elem)const;
	BinarySearchTreeNode<T>* tree_successor(const T& elem)const;
	bool empty()const;
	void inorder_tree_traverse() const;
	BinarySearchTreeNode<T>* getRoot()const { return root; };
	void transplant(BinarySearchTreeNode<T>* u, BinarySearchTreeNode<T>* v);
private:
	BinarySearchTreeNode<T>* root;
};

//构造函数
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	root = NULL;
}
//插入（从根节点开始找，后插）
template<class T>
void BinarySearchTree<T>::tree_insert(const T& elem) {
	if (!empty()) {
		BinarySearchTreeNode<T>* newNode = new BinarySearchTreeNode<T>;
		newNode->key = elem;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->parent = NULL;
		BinarySearchTreeNode<T>* p =  root;
		BinarySearchTreeNode<T>* q = NULL;
		while (p) {
			q = p;
			if (p->key > elem)
				p = p->left;
			else
				p = p->right;
		}
		if (q->key > elem)
			q->left = newNode;
		else
			q->right = newNode;
		newNode->parent = q;
	}
	else {
		root = new BinarySearchTreeNode<T>;
		root->key = elem;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}

}
//删除(只有左孩子；只有右孩子；左右孩子都存在)
template<class T>
int  BinarySearchTree<T>::tree_remove(const T& elem) {
	BinarySearchTreeNode<T>* X = tree_search(elem);//要删除的节点、
	if (!X)
		return -1;
	if (X->left == NULL)
		transplant(X,X->right);
	else if(X->right == NULL)
		transplant(X, X->left);
	else {
		BinarySearchTreeNode<T>* pb = tree_min(X->right);//要删除的节点的后继
		if (pb->parent!= X) {
			transplant(pb,pb->right);
			pb->right=X->right;
			pb->right->parent = pb;
		}
		transplant(X,pb);
		pb->left = X->left;
		pb->left->parent = pb;
	}
	return 0;
}

//搜索
template<class T>  
BinarySearchTreeNode<T>*  BinarySearchTree<T>::tree_search(const T& elem)const {
	BinarySearchTreeNode<T>* p = root;
	while (p) {
		if (p->key == elem)
			break;
		else if (p->key > elem)
			p = p->left;
		else
			p = p->right;	
	}
	return p;
}
//最大(不断沿着右子树找下去)
template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_max(BinarySearchTreeNode<T>* root)const {
	BinarySearchTreeNode<T>* p = root;
	while (p->right)
		p = p->right;
	return p;
}
//最小(不断沿着左子树找下去)
template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_min(BinarySearchTreeNode<T>* root) const {
	BinarySearchTreeNode<T>* p = root;
	while (p->left)
		p = p->left;
	return p;
}

//前继
template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_preccesor(const T& elem)const {
	BinarySearchTreeNode<T>* x = tree_search(elem);
	BinarySearchTreeNode<T>* p;
	if (x== NULL)
		return NULL;
	else{
		if (x->left)
			return tree_max(x->left);
		else {
			p = x->parent;
			while (p && x==p->left) {
				x= p;
				p = p->parent;		
			}
		}
		return p;
    }
}
//后继
template<class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_successor(const T& elem)const {
	BinarySearchTreeNode<T>* x = tree_search(elem);
	BinarySearchTreeNode<T>* p;
	if (x == NULL)
		return NULL;
	else {
		if (x->right)
			return tree_min(x->right);
		else {
			 p = x->parent;			
			while (p && x == p->right) {
				x= p;
				p = p->parent;
			}
		}
		return p;
	}
}

//替换(用v替换u)
template <class T>
void BinarySearchTree<T>::transplant(BinarySearchTreeNode<T>* u, BinarySearchTreeNode<T>* v) {
	if (u->parent == NULL)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;	
	if (u == u->parent->right)
		u->parent->right = v;
	if (v)
		v->parent = u->parent;
}

//清空
template <class T>
bool BinarySearchTree<T>::empty() const
 {
     return (NULL == root);
 }

////中序遍历（借助栈）
template <class T>
void BinarySearchTree<T>::inorder_tree_traverse()const {
	if (root!=NULL) {
		stack<BinarySearchTreeNode<T>*> s;
		BinarySearchTreeNode<T>* p = root;
		while (p != NULL || !s.empty() ) {
			if (p) {
				s.push(p);
				p = p->left;
			}
			else {
				p = s.top();
				s.pop();
				cout << p->key << " ";
				p = p->right;
			}
		}	
	}
}

