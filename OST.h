
//http://blog.csdn.net/lu597203933/article/details/43459035
//动态顺序统计
//在算法系列笔记2中我们在线性时间内完成了静态表的顺序统计，而这里我们在红黑树上进行扩展
//在O(lgn)时间内完成该操作，主要包括返回第i 排名的元素os_select(i)和给定一个元素x，返回其排名(os_rank(x)).

// 插入过程不理解？？？

#include <iostream>
#include <string>
//cout函数重载的是string类库中的string类型，而不是CString或string.h中的。

using namespace std;

class BSTNode {
public:
	BSTNode *left, *right, *parent;
	int val;
	string color;
	int size;//new added
};

class OSRBTree {
public:
	BSTNode *root;

	OSRBTree(const int &rootval) {
		root = new BSTNode();
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->val = rootval;
		root->color = "balck";
		root->size = 1;
	}
	BSTNode* insertBST(BSTNode *p,const int &value);
	void insertOSRBTree(BSTNode *root1,const int &value);
	void inorderOSRBTree(BSTNode *p);
	BSTNode* os_select(BSTNode *p,const int &ith);
	int os_rank(BSTNode *p, const int &value);

};

// 二叉查找树的插入  
BSTNode* OSRBTree::insertBST(BSTNode *p, const int &value) {
	BSTNode *in = new BSTNode();
	in->left = NULL;
	in->right = NULL;
	in->parent = NULL;
	in->val = value;
	in->size = 1;
	BSTNode *y = NULL;
	while (p) {
		y = p;
		p->size += 1;
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
	p = in;
	return in;
}

//// 插入红黑树  
void OSRBTree::insertOSRBTree(BSTNode *root1, const int &value)
{
	BSTNode* in = insertBST(root1, value);
	in->color = "red";
	//调整红黑特性
	while (in->parent&& in->parent->color == "red") {
	
		if (in->parent == in->parent->parent->left) {
			BSTNode* y = in->parent->parent->right;
			if (y&&y->color == "red") {////case 1 父节点存在且为红,该父节点为祖父节点的左孩子,叔叔节点也为红
				y->color = "black";
				y->parent->color = "red";
				in->parent->color = "black";
				in = in->parent->parent;
			}
			else {
				if (in == in->parent->right) {//case 1 父节点存在且为红,该父节点为祖父节点的左孩子,叔叔节点为黑,且当前结点是右孩子[左旋parent,更新parent]
					BSTNode* pa = in->parent;
					in->size = pa->size;//  修改该结点所包含子树结点个数 .得到in->size 
					in->parent = pa->parent;
					pa->parent->left = in;
					pa->parent = in;
					if (pa->left)
						pa->size = pa->left->size + 1;
					else
						pa->size = 1;//得到 pa->size

					if (in->left) {
						in->left->parent = pa;
						pa->size += in->left->size;  //更新pa
					}
					pa->right = in->left;
					in->left = pa;

					in = pa;
				}
				else {
					//case 1 父节点存在且为红,该父节点为祖父节点的左孩子,叔叔节点为黑,且当前结点是左孩子[右旋gparent]
					BSTNode* pa = in->parent;
					BSTNode* gpa = in->parent->parent;
					pa->size = gpa->size;
					if (gpa->parent) {
						if (gpa == gpa->parent->left)
							gpa->parent->left = pa;
						else
							gpa->parent->right = pa;
					}
					pa->parent = gpa->parent;
					if (gpa->right)
						gpa->size = gpa->right->size + 1;
					else
						gpa->size = 1;
					if (pa->right) {
						gpa->size += pa->right->size;
						pa->right->parent = gpa;
					}
					gpa->left = pa->right;
					pa->right = gpa;
					gpa->parent = pa;
					pa->color = "black";
					gpa->color = "red";
				}

			}
		}
		else {
			BSTNode* y = in->parent->parent->left;
			if (y&&y->color == "red") {//case 2 父节点存在且为红,该父节点为祖父节点的右孩子,叔叔节点也为红
				y->color = "black";
				y->parent->color = "red";
				in->parent->color = "black";
				in = in->parent->parent;
			}
			else {
				if (in == in->parent->left)//case 2 父节点存在且为红,该父节点为祖父节点的右孩子,叔叔节点为黑, 且当前结点是右孩子[in->parent右旋]
				{
					BSTNode* pa = in->parent;
					in->size = pa->size;
					in->parent = pa->parent;
					pa->parent->right = in;
					pa->parent = in;
					if (pa->right)
						pa->size = pa->right->size + 1;
					else
						pa->size = 1;
					if (in->right) {
						in->right->parent = pa;
						pa->size += in->right->size;
					}
					pa->left = in->right;
					in->right = pa;
					in = pa;
				}
				else {//case 2 父节点存在且为红,该父节点为祖父节点的右孩子,叔叔节点为黑,且当前结点是左孩子[左旋gparent]
					BSTNode* pa = in->parent;
					BSTNode* gpa = in->parent->parent;
					pa->size = gpa->size;
					if (gpa->parent) {
						if (gpa == gpa->parent->left)
							gpa->parent->left = pa;
						else
							gpa->parent->right = pa;
					}
					pa->parent = gpa->parent;
					if (gpa->left)
						gpa->size = gpa->left->size + 1;
					else
						gpa->size = 1;
					if (pa->left) {
						pa->left->parent = gpa;
						gpa->size += pa->left->size;
					}
					gpa->right = pa->left;
					pa->left = gpa;
					gpa->parent = pa;
					pa->color = "black";
					gpa->color = "red";
				}
			}

		}
		root1->color = "black";
	}
}

void OSRBTree::inorderOSRBTree(BSTNode *p) {
	if (p) {
		if (p->left)
			inorderOSRBTree(p->left);
		cout << p->val << p->color << p->size << " ";
		if (p->right)
			inorderOSRBTree(p->right);
	}
	else
		return;
}

BSTNode* OSRBTree::os_select(BSTNode *p, const int &ith) {
	if (p) {
		int k = 1;
		if (p->left)
			k = p->left->size  + 1;
		if (ith == k)
			return p;
		if (ith < k)
			return os_select(p->left ,ith);
		else
			return os_select(p->right, ith-k);
	}
	else
		return NULL;
}

int OSRBTree::os_rank(BSTNode *p, const int &value) {
	if (p) {
		int k = 1;
		if (p->left)
			k = p->left->size + 1;
		if (p->val == value)
			return k;
		if (p->val > value)
			return os_rank(p->left , value);
		else
			return  os_rank(p->right, value)+k;
	}
	else
	return 0;
}