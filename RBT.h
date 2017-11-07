#pragma once

#include <iostream>
using namespace std;

enum RBTColor{RED,BLACK};

template<class T>
class RBTNode{
public:
	T key;
	RBTNode<T>* parent;
	RBTNode<T>* leftchild;
	RBTNode<T>* rightchild;
	RBTColor color;

	RBTNode(T v, RBTNode<T>* p, RBTNode<T>* l, RBTNode<T>* r, RBTColor c):
		key(v), parent(p),leftchild(l),rightchild(r),color(c) {}
};

template<class T>
class RBTTree {
	RBTNode<T>* root;
public:
	RBTTree();
	~RBTTree();
	void preOrder();
	void preOrder(RBTNode<T>* tree)const;
	void inOrder();
	void inOrder(RBTNode<T>* tree)const;
	void postOrder();
	void postOrder(RBTNode<T>* tree)const;//����
	RBTNode<T>* Recur_search(T v);
	RBTNode<T>* Recur_search(RBTNode<T>* x,T v);
	RBTNode<T>* search(T v);
	RBTNode<T>* search(RBTNode<T>* x, T v);//����
	T maximum();
	RBTNode<T>* maximum(RBTNode<T>* tree);
	T minimum();
	RBTNode<T>* minimum(RBTNode<T>* tree);//�����Сֵ
	RBTNode<T>* predecessor(RBTNode<T>* x);
	RBTNode<T>* successor(RBTNode<T>* x);//ǰ�����

	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* x);//��ת
	void insert(T v);
	RBTNode<T>* insert(RBTNode<T>* &root, RBTNode<T>* node);//����
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);//��������
	void remove(T v);
	void remove(RBTNode<T>* &root, RBTNode<T>* node);//ɾ��
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
	
	void destroy();
	void destroy(RBTNode<T>* tree);//����
	void print();
	void print(RBTNode<T>* tree,T key,int direction);//��ӡ
};

template<class T>
RBTTree<T>::RBTTree() {
	root = NULL;
}

template<class T>
RBTTree<T>::~RBTTree() {
	destroy();
}

template<class T>
void  RBTTree<T>::preOrder() {
		preOrder(root);	
}

template<class T>
void  RBTTree<T>::preOrder(RBTNode<T>* tree)const {
	if (tree) {
		cout << tree->key << " ";
		preOrder(tree->leftchild);
		preOrder(tree->rightchild);
	}
}

template<class T>
void  RBTTree<T>::inOrder() {
		inOrder(root);
}

template<class T>
void  RBTTree<T>::inOrder(RBTNode<T>* tree)const {
	if (tree) {
		inOrder(tree->leftchild);
		cout << tree->key << " ";
		inOrder(tree->rightchild);
	}
}

template<class T>
void  RBTTree<T>::postOrder() {
		postOrder(root);
}

template<class T>
void  RBTTree<T>::postOrder(RBTNode<T>* tree)const {
	if (tree) {
		postOrder(tree->leftchild);
		postOrder(tree->rightchild);
		cout << tree->key << " ";
	}
}

template<class T>
RBTNode<T>* RBTTree<T>::Recur_search(T v) {
	Recur_search(root, v);
}
template<class T>
RBTNode<T>* RBTTree<T>::Recur_search(RBTNode<T>* x, T v) {
	if (!x || x->key == v)
		return x;
	else if (x->key > v)
		search(x->leftchild, v);
	else
		search(x->rightchild, v);
}

template<class T>
RBTNode<T>*  RBTTree<T>::search(T v) {
	search(root,v);
}

template<class T>
RBTNode<T>*  RBTTree<T>::search(RBTNode<T>* x, T v) {
	while (x && x->key != v) {
		if (x->key > v)
			x=x->leftchild;
		else
			x=x->rightchild;	
	}
		return x;
}

template<class T>
T RBTTree<T>::maximum() {
	RBTNode<T>* p = maximum(root);
	if (p)
		return p->key;
	return (T)NULL;
}


template<class T>
RBTNode<T>* RBTTree<T>::maximum(RBTNode<T>* tree) {
	if (tree) {
		while (tree->rightchild)
			tree = tree->rightchild;
		return tree;
	}
	else
		return NULL;
}

template<class T>
T RBTTree<T>::minimum() {
	RBTNode<T>* p = minimum(root);
	if (p)
		return p->key;
	return (T)NULL;
}

template<class T>
RBTNode<T>* RBTTree<T>::minimum(RBTNode<T>* tree) {
	if (tree) {
		while (tree->leftchild)
			tree = tree->leftchild;
		return tree;
	}
	else
		return NULL;
}

template<class T>
RBTNode<T>*  RBTTree<T>::predecessor(RBTNode<T>* x) {
	if (x->leftchild)
	 return	maxmum(x->leftchild);
	else {
		RBTNode<T>* y=x->parent;
		while (y&&x==y->leftchild) {
			x = y;
			y = y->parent;
		}
		return y;
	}
}

template<class T>
RBTNode<T>*  RBTTree<T>::successor(RBTNode<T>* x) {
	if (x->rightchild)
		return	minimum(x->rightchild);
	else {
		RBTNode<T>* y = x->parent;
		while (y&&x == y->rightchild) {
			x = y;
			y = y->parent;
		}
		return y;
	}

}

template<class T>
void  RBTTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x) {
	RBTNode<T>*  y = x->rightchild;
	x->rightchild=y->leftchild;
	if (y->leftchild)
		y->leftchild->parent = x;
	y->parent = x ->parent;
	if (x->parent) {
		if (x->parent->left == x)
			y = x->parent->left;
		else
			y = x->parent->right;
	}
	else
		root = y;
	y->leftchild = x;
	x->parent = y;
}
template<class T>
void  RBTTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* x) {
	RBTNode<T>*  y = x->leftchild;
	x->leftchild = y->rightchild;
	if (y->rightchild)
		y->rightchild->parent = x;

	y->parent = x->parent;
	if (x->parent) {
		if (x->parent->left == x)
			y = x->parent->left;
		else
			y = x->parent->right;
	}
	else
		root = y;
	y->rightchild = x;
	x->parent = y;
}
template <class T>
void RBTTree<T>::insert(T key)
 {
	    RBTNode<T> *z = NULL;
		if ((z = new RBTNode<T>(key, NULL, NULL, NULL, BLACK)) == NULL)
		     return;
		 insert(root, z);
 }
template<class T>
RBTNode<T>* RBTTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node) {
	//RBTNode<T>*node=new RBTNode<T>(v,BLACK,NULL,NULL,NULL)) 
	RBTNode<T>* x = root;
	RBTNode<T>* y = NULL;
	if (root)
		y = x;
	if (x->key > node->key)
		x = x->leftchild;
	else
		x = x->rightchild;
	node->parent = y;
	if (y) {
		if (y->key > node->key)
			y->lefchild = node;
		else
			y->rightchild = node;
	}
	else
		root = node;

	node->color = RED;
	insertFixUp(root, node);
}

template <class T>
void RBTTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* p,*u,*gp;//���ڵ㣬����ڵ���游�ڵ�
	RBTNode<T>* temp;//��ʱ
	while ((p=node->parent)&&(node->parent->color==RED)) {//���ڵ������Ϊ��
		gp = p->parent;
	if(p==gp->leftchild){//�ø��ڵ�Ϊ�游�ڵ������
		u = gp->rightchild;
		//1.����ڵ�ҲΪ��
		if (u&&u->color == RED) {
			u->color = BLACK;
			p->color = BLACK;
			gp->color = RED;
			node = gp;
			continue;
		}
		//2.����ڵ�Ϊ��,�ҵ�ǰ������Һ���
		if(node==p->right){
			leftRotate(root,p);
			temp = p;
			p = node;
			node = temp;
        }
		//3.����ڵ�Ϊ��,�ҵ�ǰ���������
		else {
		p->color = BLACK;
		gp->color = RED;
		rightRotate(root, gp);
		}

     }
	else{//�ø��ڵ�Ϊ�游�ڵ���Һ���
		u = gp->leftchild;
		//1.����ڵ�ҲΪ��
		if (u&&u->color == RED) {
			u->color = BLACK;
			p->color = BLACK;
			gp->color = RED;
			node = gp;
			continue;
		}
		//2.����ڵ�Ϊ��,�ҵ�ǰ������Һ���
		if (node == p->right) {
			p->color = BLACK;
			gp->color = RED;
			leftRotate(root, gp);

		}
		//3.����ڵ�Ϊ��,�ҵ�ǰ���������
		else {
			rightRotate(root, p);
			temp = p;
			p = node;
			node = temp;
		}
   }	
	}
	root->color = BLACK;
}

template <class T>
void RBTTree<T>::remove(T v) {
	RBTTree<T>* node = search(root, v);
	if (node)
		remove(root,node);
}

template <class T>
void RBTTree<T>::remove(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTColor color;//node/��̽ڵ��ԭ����ɫ
	RBTNode<T>* pr;//node/��̽ڵ�ĸ��ڵ�
	RBTNode<T>* cr;///node/��̽ڵ��(��)����

	//1.���Һ��Ӷ�����
	if (node->leftchild && node->rightchild) {
		RBTNode<T>* replace = node;
		//�õ���̽ڵ�replace(�����������ֵ)
		replace = node->rightchild;
		while (replace->leftchild)
			replace = replace->leftchild;

		//��̽ڵ�replace����node
		if (node->parent){
			if (node->parent->leftchild == node)
				node->parent->leftchild = replace;
			else
				node->parent->rightchild = replace;
		}
		else
			replace = root;
		color = replace->color;//��̽ڵ��ԭ����ɫ
		pr = replace->parent;//��̽ڵ�ĸ��ڵ�
		cr = replace->rightchild;//[�̽ڵ�϶����������ӣ��������Һ���]
		if (node == pr) //��̽ڵ��Ǳ�ɾ���ڵ�ĺ���
			pr = replace;
		else{ // ��̽ڵ㲻�뱻ɾ���ڵ������,		
			if (cr)
				pr = cr->parent;
			pr->leftchild = cr;
			replace->rightchild = node->rightchild;
			node->rightchild->parent = replace;
		}

		//��̽ڵ�replace����node����Ϣ
		replace->parent = node->parent;
		replace->leftchild = node->leftchild;//[�̽ڵ�϶����������ӣ��������Һ���]
		replace->color = node->color;
		node->leftchild->parent = replace;

		if (color == BLACK)
			removeFixUp(root, cr, pr);

		delete node;
	}

	//2.����Һ��Ӵ���
	if (node->leftchild)
		cr = node->leftchild;
	else (node->rightchild)
		cr = node->rightchild;
	pr = node->parent;
	color = node->color;
	if (cr)
		cr->parent = pr;
	if (pr) {//node�����Ǹ��ڵ�
		if (node == pr->leftchild)
			pr->leftchild = cr;
		else
			pr->rightchild = cr;
	}
	else
		root = cr;

	if(color==BLACK)
		removeFixUp(root, cr, pr);

	delete node;
}

template <class T>
void RBTTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>* parent) {
	RBTNode<T>* other;
	while ((!node || node->color == BLACK) && node != root) {
		if (parent->leftchild == node) {
			other = node->rightchild;
			if (other->color == RED) {//1.x���ֵ�w�Ǻ�ɫ��  
				other->color = BLACK;
				parent->color = RED;
				leftRotate(root,parent);
				other = parent->rightchild;
			}
			if ((!other->leftchild || other->leftchild->color == BLACK) && (!other->rightchild || other->rightchild->color == BLACK)) {
				// 2.x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else {
				if (!other->rightchild || other->rightchild->color == BLACK)// 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ
				{
					other->leftchild ->color= BLACK;
					other->color = RED;
					rightRotate(root,other);
					other = parent->rightchild;
				}
			// 4.x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				other->color = parent->color;
				parent->color = BLACK;
				other->rightchild->color = BLACK;
				leftRotate(root,parent);
				node = root;
				break;
			}
		}
		else {
			other = parent->leftchild;
			if (other->color== RED) {//1: x���ֵ�w�Ǻ�ɫ��  
				other->color = BLACK;
				parent->color = RED;
				rightRotate(root,parent);
				other = parent->leftchild;
			}
			if ((!other->leftchild || other->leftchild->color == BLACK) && (!other->rightchild || other->rightchild->color == BLACK)) {
				// 2.x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else {
				if (!other->leftchild || other->leftchild->color == BLACK)// 3: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ������Ϊ��ɫ
				{
					other->rightchild->color = BLACK;
					other->color = RED;
					rightRotate(root, other);
					other = parent->leftchild;
				}
				// 4.x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ�ģ��Һ���������ɫ��
				other->color = parent->color;
				parent->color = BLACK;
				other->leftchild->color = BLACK;
				rightRotate(root, parent);
				node = root;
				break;						
			}
		}
	}
	if(node)
		node->color = BLACK;
}

template <class T>
void RBTTree<T>::destroy() {
	destroy(root);	
}

template <class T>
void RBTTree<T>::destroy(RBTNode<T>* tree) {
	if (tree == NULL)
		return;
	if (tree->leftchild)
		destroy(tree->leftchild);
	if (tree->rightchild)
		destroy(tree->rightchild);
	destroy(tree);
	tree = NULL;
}

template <class T>
void RBTTree<T>::print(){
	if (root)
		print(root,root->key,0);
}
template <class T>
void RBTTree<T>::print(RBTNode<T>* tree,T v,int direction) {
	if (tree) {
		if(direction==0)
		   cout << tree->key << "is root."<<endl;
		else
			cout << tree->key<<(tree->color==RED?"RED":"BLACK") << " is " << v << "'s " <<  (direction == 1 ? "right child" : "left child") << endl;
		     print(tree->left, tree->key, -1);
		     print(tree->right, tree->key, 1);	
	}

}