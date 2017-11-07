
//http://blog.csdn.net/lu597203933/article/details/43459035 
//������(Interval Tree)����һϵ�е����䣬����˵ʱ�����䡣��Ҫ��ѯ�����е��������䣬��������䷢���ص�������Щ��
//1��ѡ��������Ϊ���������ݽṹ����������Ľϵ�ֵ(low)��Ϊ��ֵ
//2����������������ֵ��Ϊ����ӵ���(m[x] = max{ high[int[x]],m[left[x]], m[right[x]] }).
//3���Ƿ��ܲ���ɾ���Ȳ�����Ӱ�죿�ܣ�������O(1)ʱ���ھ��ܵ��������������롣
//4���µĲ�������ѯ����������������ص���һ�����䡣

#ifndef  INTERVALTREE//IntervalTree����
#define INTERVALTREE

#include <iostream>
#include <string>
using namespace std;

struct dataNode{
	int low;
	int high;
};
class BSTNode{
public:
	BSTNode* left, *right;
	BSTNode* parent;
	int val;
	dataNode d;
	string color;
	int m;
};
class IntervalTree{
public:
	BSTNode* root;


	IntervalTree(const dataNode &d) {
		root = new BSTNode();
		root->d = d;
		root->color = "balck";
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->m = d.high;
		root->val = d.low;
	}
	BSTNode* insertBST(BSTNode* p, const dataNode &d);
	void insertIntervalTree(BSTNode* root1, const dataNode &d);
	void inorderOSRBTree(BSTNode* p);
	BSTNode* intervalSearch(BSTNode* p, const dataNode &d);
	void destroyBST(BSTNode* p);
};

BSTNode* IntervalTree::insertBST(BSTNode* p, const dataNode &d) {
	BSTNode* y = NULL;
	BSTNode* in = new BSTNode();
	in->left = NULL;
	in->right = NULL;
	in->parent= NULL;
	in->val = d.low;
	in->m = d.high;
	in->d = d;
	while (p) {
		y = p;
		if (p->m < in->m)
			p->m = in->m;  //add
		if (p->val > in->val)
			p = p->left;
		else
			p = p->right;
	}
	if (y) {
		in->parent = y;
		if (y->val > in->val)
			y->left = in;
		else
			y->right = in;
	}
	else
		p = in;
	return in;
}

void IntervalTree::insertIntervalTree(BSTNode* root1, const dataNode &d) {
	BSTNode* in = insertBST(root1,d);
	in->color = "red";
	while (in->parent &&in->parent ->color =="red") {
		if (in->parent == in->parent->parent->left) 
		{
			BSTNode* y = in->parent->parent->right;
			if (y &&y->color == "red") {//1
				y->color = "black";
				y->parent->color  = "red";
				in->parent ->color = "black";
				in = in->parent->parent;
			}
			else {
				if (in == in->parent->right) {//1  parent����)
					BSTNode* pa = in->parent;
					in->m = pa->m;
					in->parent = pa->parent;
					pa->parent->left = in;
					pa->parent = in;
					if (pa->left)
						pa->m = pa->left->m > pa->m ? pa->left->m : pa->m;
					if (in->left) {
						in->left->parent = pa;
						pa->m = in->left->m > pa->m ? pa->left->m : pa->m;				
					}
					pa->right = in->left;
					in->left = pa;
					in = pa;

				}
				else{//1  in->parent->parent ���� 
					BSTNode* pa = in->parent;
					BSTNode* gpa = in->parent->parent ;
					pa->m = gpa->m;
					if (gpa->parent )
					{
						if (gpa == gpa->parent->left)
							gpa->parent->left=pa;
						else
							 gpa->parent->right= pa;

					}
					pa->parent = gpa->parent;
					if (gpa->right)
						gpa->m = gpa->right->m > gpa->m ? gpa->right->m : gpa->m;
					if (pa->right) {
						gpa->m = pa->right->m > gpa->m ? pa->right->m : gpa->m;
						pa->right->parent = gpa;
					}
					gpa->left = pa->right;
					pa->right = gpa;
					gpa->parent= pa;
					pa->color = "black";
					gpa->color = "red";
			     }
			}
		
		
		}
		else {
			BSTNode* y = in->parent->parent ->left;
			if (y&&y->color == "red"){
				y->color = "black";
				y->parent->color  = "red";
				in->parent->color  = "black";
				in = in->parent->parent;
		    }
			else {
				if (in == in->parent->left) {
					BSTNode* pa = in->parent;
					in->m = pa->m;
					in->parent = pa->parent;
					pa->parent->right = in;
					pa->parent = in;
					if (pa->right)
						pa->m = pa->m > pa->right->m ? pa->m : pa->right->m;
					if (in->right) {
						in->right->parent = pa;
						pa->m = pa->m > in->right->m ? pa->m : in->right->m;
					}
					pa->left = in->right;
					in->right = pa;
					in=pa;		
				}
				else {
					BSTNode* pa = in->parent;
					BSTNode* gpa = in->parent->parent ;
					pa->m = gpa->m;
					if (gpa->parent) {
						if (gpa == gpa->parent->left)
							 gpa->parent->left=pa;
						else
							gpa->parent->right=pa;
					}
					pa->parent = gpa->parent;
					if (gpa->left)
						gpa->m = gpa->left->m > gpa->m ? gpa->left->m : gpa->m;
					if (pa->left) {
						pa->left->parent = gpa;
						gpa->m = pa->left->m > gpa->m ? pa->left->m : gpa->m;
					}
					gpa->right = pa->left;
					pa->left = gpa;
					gpa->parent = pa;
					pa->color = "black";
					gpa->color = "red";
				}
			
			
			}
		
		}
	
	}
	root1->color = "balck";
}

void IntervalTree::inorderOSRBTree(BSTNode* p) {
	if (p) {
		if (p->left)
			inorderOSRBTree(p->left);
		cout << p->val << p->color << p->m << " ";
		if (p->right)
			inorderOSRBTree(p->right);
	}
	else
		return;
}

BSTNode* IntervalTree::intervalSearch(BSTNode* p, const dataNode &d) {
	while (p&&(d.low>p->d.high||d.high<p->d.low)) {
		if (p->left&&d.low < p->m)
			p = p->left;
		else
			p = p->right;
	}
	return p;
}


void IntervalTree::destroyBST(BSTNode* p) {
	if (p) {
		if (p->left)
			destroyBST(p->left);
		else
			destroyBST(p->right);
		delete p;
	}
	return;

}

#endif