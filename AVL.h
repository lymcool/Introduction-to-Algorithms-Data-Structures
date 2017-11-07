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
};//���������ʼ��������


template<class T>
class avl {
private:
	avlNode<T>* root=NULL;
public:
	avl() { };
	bool isTaller = false;//��ǰ�����
	//���뼰����
	bool insert(const T& elem);
	bool insertAvl(const T& elem, avlNode<T>* node);
	void leftBalance(avlNode<T>* node);
	void rightBalance(avlNode<T>* node);
	void lRotate(avlNode<T>* node);
	void rRotate(avlNode<T>* node);
	//ɾ��������
	avlNode<T>* max(avlNode<T>* node);
	avlNode<T>* min(avlNode<T>* node);
	void removeAvl(const T& elem, avlNode<T>* node);
	
	avlNode<T>* getRoot();
	void preOrderTraverse(avlNode<T>* node);//ǰ��(false????)
	void inorder_tree_traverse()const ;//�������
	//void  preOrder(avlNode<T>* pnode) ;
	//void  inOrder( );
};


//����
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
		//����������
		if (node->key > elem) {
			if (!node->left) {
				avlNode<T>* newNode = new avlNode<T>(elem);
				node->left = newNode;
				newNode->parent = node;
				isTaller = true;
			}
			else
				insertAvl(elem,node->left);
			if(isTaller){//��߸�
				switch (node->bFactor) {
				case LH://1->2,��ƽ�⴦��
				{
					leftBalance(node);
					isTaller = false;
					break;			
				}
				case EH://0->1,������
				{
					node->bFactor = LH;
					isTaller = true;
					break;				
				}
				case RH://-1->0,������
				{
					node->bFactor = EH;
					isTaller = true;
					break;
				}			
				}
          }
		}
		//����������			
		else {
			if (!node->right) {
				avlNode<T>* newNode = new avlNode<T>(elem);
				node->right = newNode;
				newNode->parent = node;
				isTaller = true;
			}
			else
				insertAvl(elem, node->right);
			if (isTaller) {//�ұ߸�
				switch (node->bFactor) {
				case LH://1->0,������
				{
					node->bFactor = EH;
					isTaller = true;
					break;
				}
				case EH://0->-1,������
				{
					node->bFactor = RH;
					isTaller = true;
					break;
				}	
				case RH: //-1->-2,��ƽ�⴦��
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
//��ƽ�⴦��
template<class T>
void avl<T>::leftBalance(avlNode<T>* node) {
	avlNode<T>* p = node->left;//�õ�����
	switch (p->bFactor) {
	case LH://�½ڵ�������ӵ��������ϣ�����1->2��,�Ըõ�����
	{
		node->bFactor=p->bFactor = EH;
		rRotate(node);
		break;
	}
	case RH://���ң�1->2��,�Ըõ������������ٶԸõ�����
	{
		avlNode<T>* pr = p->right;//�õ����ӵ��Һ���
		switch (pr->bFactor) {//Ϊ���޸�node�������ӵ�ƽ������  
		case LH:  //������̵���⣿����
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


//��ƽ�⴦��
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
	case LH://�½ڵ�����Һ��ӵ��������ϣ��Ըõ��Һ����������ٶԸõ�����
	{
		avlNode<T>* pr = p->left;//�õ��Һ��ӵ�����
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

//����
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



//����
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

//ɾ��
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
		if (elem == node->key) {//���ҵ�Ҫɾ����Ԫ��
			if (node->left && node->right) {
				if (node->bFactor == LH) {//�����ѡԪ���滻(max)
					avlNode<T>* p = max(node->left);
					node->key = p->key;
					removeAvl(p->key, node->left);
				}
				else {//���ұ�ѡԪ���滻(min)
					avlNode<T>* p = min(node->right);
					node->key = p->key;
					removeAvl(p->key, node->right);
				}
			}
			else {
				avlNode<T>* pnode = node;//Ϊʲô��Ҫ����
				if (node->left)
					node = node->left;
				else
					node = node->right;
				delete pnode;
			}

		}

		else if (elem > node->key) {//Ҫɾ����Ԫ����������(�ݹ�ɾ��������ƽ��)
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
		else {//Ҫɾ����Ԫ����������(�ݹ�ɾ��������ƽ��)
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

//�õ����ڵ�
template<class T>
avlNode<T>* avl<T>::getRoot() {
     return this->root;
}

//ǰ�����
template<class T>
void avl<T>::preOrderTraverse(avlNode<T>* node) {
	if (node) {
		cout << node->key << " ";
		preOrderTraverse(node->left);
		preOrderTraverse(node->right);
	}
}

////�������������ջ��
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

///*�������*/
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