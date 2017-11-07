#pragma once

#include <iostream>
#include <stack>

const int LH = 1;
const int EH = 0;
const int RH = -1;

template<class T>
class avlNode {
public:
	T key = NULL;
	//int bFactor;
	int bFactor = EH;
	avlNode<T>* left = NULL;
	avlNode<T>* right = NULL;
	avlNode<T>* parent = NULL;

	avlNode(T k){ this->key = k; };
};//在类里面初始化？？？


template<class T>
class avl {
private:
	avlNode<T>* root=NULL;
public:
	avl() { };
	bool isTaller = false;//当前树变高
	//插入及调整
	bool insert(const T& elem);
	bool insertAvl(const T& elem, avlNode<T>* node);
	void leftBalance(avlNode<T>* node);
	void rightBalance(avlNode<T>* node);
	void lRotate(avlNode<T>* node);
	void rRotate(avlNode<T>* node);
	//删除及调整
	avlNode<T>* max(avlNode<T>* node);
	avlNode<T>* min(avlNode<T>* node);
	void removeAvl(const T& elem, avlNode<T>* node);
	
	avlNode<T>* getRoot();
	void preOrderTraverse(avlNode<T>* node);//前序(false????)
	void inorder_tree_traverse()const ;//中序遍历
	//void  preOrder(avlNode<T>* pnode) ;
	//void  inOrder( );
};


//插入
template<class T>
bool avl<T>::insert(const T& elem) {
	if (elem) {
		if (!root) {
			root = new avlNode<T>(elem);
			return true;
		}
		else {
		return insertAvl(elem,root);
		}
	}
	return false;
}
template<class T>
bool avl<T>::insertAvl(const T& elem, avlNode<T>* node)  {
	if (node->key == elem) {
		isTaller = false;
		return false;
	}
	else{
		//左子树搜索
		if (node->key > elem) {
			if (!node->left) {
				avlNode<T>* newNode = new avlNode<T>(elem);
				node->left = newNode;
				newNode->parent = node;
				isTaller = true;
			}
			else
				insertAvl(elem,node->left);
			if(isTaller){//左边高
				switch (node->bFactor) {
				case LH://1->2,左平衡处理
				{
					leftBalance(node);
					isTaller = false;
					break;			
				}
				case EH://0->1,不处理
				{
					node->bFactor = LH;
					isTaller = true;
					break;				
				}
				case RH://-1->0,不处理
				{
					node->bFactor = EH;
					isTaller = true;
					break;
				}			
				}
          }
		}
		//右子树搜索			
		else {
			if (!node->right) {
				avlNode<T>* newNode = new avlNode<T>(elem);
				node->right = newNode;
				newNode->parent = node;
				isTaller = true;
			}
			else
				insertAvl(elem, node->right);
			if (isTaller) {//右边高
				switch (node->bFactor) {
				case LH://1->0,不处理
				{
					node->bFactor = EH;
					isTaller = true;
					break;
				}
				case EH://0->-1,不处理
				{
					node->bFactor = RH;
					isTaller = true;
					break;
				}	
				case RH: //-1->-2,右平衡处理
				{
					rightBalance(node);
					isTaller = false;
					break;
				}
				}
			}		
		}
    }

}
//左平衡处理
template<class T>
void avl<T>::leftBalance(avlNode<T>* node) {
	avlNode<T>* p = node->left;//该点左孩子
	switch (p->bFactor) {
	case LH://新节点插在左孩子的左子树上，左左（1->2）,对该点右旋
	{
		node->bFactor=p->bFactor = EH;
		rRotate(node);
		break;
	}
	case RH://左右（1->2）,对该点左孩子左旋，再对该点右旋
	{
		avlNode<T>* pr = p->right;//该点左孩子的右孩子
		switch (pr->bFactor) {//为了修改node与其左孩子的平衡因子  
		case LH:  //下面过程的理解？？？
		{
			node->bFactor = RH;
			p->bFactor = EH;
		}
		case EH:
		{
			node->bFactor = p->bFactor = EH;
		}
		case RH:
		{
			node->bFactor = EH;
			p->bFactor = LH;
		}
		}
		pr->bFactor = EH;
		lRotate(p);
		rRotate(node);
		break;
	}

	}

}


//右平衡处理
template<class T>
void avl<T>::rightBalance(avlNode<T>* node) {
	avlNode<T>* p = node->right;
	switch (p->bFactor) {
	case RH:
	{
		node->bFactor = p->bFactor = EH;
		lRotate(node);
		break;
	}
	case LH://新节点插在右孩子的左子树上，对该点右孩子右旋，再对该点左旋
	{
		avlNode<T>* pr = p->left;//该点右孩子的左孩子
		switch (pr->bFactor) {
		case LH:
		{
			p->bFactor = RH;
			node->bFactor = EH;
		}
		case EH:
		{
			node->bFactor = p->bFactor = EH;
		}
		case RH:
		{
			p->bFactor = EH;
			node->bFactor = LH;
		}
		}
		pr->bFactor = EH;
		rRotate(p);
		lRotate(node);
		break;
	}

	}

}

//左旋
template<class T>
void avl<T>::lRotate(avlNode<T>* node) {
	avlNode<T>* p = node->right;
	node->right=p->left;
	p->left=node;
	if (!node->parent)
		root = p;
	else if (node->parent->left == node)
		node->parent->left = p;
	else
		node->parent->right = p;
}



//右旋
template<class T>
void avl<T>::rRotate(avlNode<T>* node) {
	avlNode<T>* p = node->left;
	node->left = p->right;
	p->right = node;
	if (!node->parent)
		root = p;
	else if (node->parent->left == node)
		node->parent->left = p;
	else
		node->parent->right = p;
}

//删除
template<class T>
avlNode<T>* avl<T>::max( avlNode<T>* node) {
	avlNode<T>* p = node;
	while (p) {
		p = p->right;
	}
	return p;
}
template<class T>
avlNode<T>* avl<T>::min(avlNode<T>* node) {
	avlNode<T>* p = node;
	while (p) {
		p = p->left;
	}
	return p;
}
template<class T>
void avl<T>::removeAvl(const T& elem, avlNode<T>* node) {
	if (node) {
		if (elem == node->key) {//已找到要删除的元素
			if (node->left && node->right) {
				if (node->bFactor == LH) {//在左边选元素替换(max)
					avlNode<T>* p = max(node->left);
					node->key = p->key;
					removeAvl(p->key, node->left);
				}
				else {//在右边选元素替换(min)
					avlNode<T>* p = min(node->right);
					node->key = p->key;
					removeAvl(p->key, node->right);
				}
			}
			else {
				avlNode<T>* pnode = node;//为什么需要？？
				if (node->left)
					node = node->left;
				else
					node = node->right;
				delete pnode;
			}

		}

		else if (elem > node->key) {//要删除的元素在右子树(递归删除并调整平衡)
			removeAvl(elem, node->right);
			if (node->bFactor == 2) {
				if (node->left->bFactor == 1)
					rRotate(node);
				else {
					lRotate(node->left);
					rRotate(node);
				}
			}
		}
		else {//要删除的元素在左子树(递归删除并调整平衡)
			removeAvl(elem, node->left);
			if (node->bFactor == -2) {
				if (node->right->bFactor == -1)
					lRotate(node);
				else {
					rRotate(node->right);
					lRotate(node);
				}
			}

		}

	}
}

//得到根节点
template<class T>
avlNode<T>* avl<T>::getRoot() {
     return this->root;
}

//前序遍历
template<class T>
void avl<T>::preOrderTraverse(avlNode<T>* node) {
	if (node) {
		cout << node->key << " ";
		preOrderTraverse(node->left);
		preOrderTraverse(node->right);
	}
}

////中序遍历（借助栈）
template <class T>
void avl<T>::inorder_tree_traverse()const {
	if (root != NULL) {
		stack<avlNode<T>*> s;
		avlNode<T>* p = root;
		while (p != NULL || !s.empty()) {
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

///*先序遍历*/
//template<class T>
//void avl<T>::preOrder(avlNode<T>* pnode) 
//{
//	if (pnode)
//	{
//		cout << pnode->key << endl;
//		inOrder(pnode->left);
//		inOrder(pnode->right);
//	}
//};
//template<class T>
//void avl<T>::inOrder( )
//{
//	inOrder(root);
//};