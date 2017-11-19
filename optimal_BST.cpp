//http://blog.csdn.net/xiajun07061225/article/details/8088784
//定义e[i,j]为包含关键字ki,...,kj的最优二叉查找树的期望代价，最终要计算的是e[1,n]。
//当j = i - 1时，此时子树中只有虚拟键，期望搜索代价为e[i,i - 1] = qi-1.
//当j >= i时，需要从ki, ..., kj中选择一个根kr，然后分别构造其左子树和右子树。

//下标从1开始

#include <iostream>
using namespace std;

void OptimalBST(double *p, double *q, int n);
void printRoot();
void printOptimalBST(int i, int j, int r);

const int MaxVal = 9999;
const int n = 5;
//搜索到根节点和虚拟键的概率  
double p[n + 1] = { -1,0.15,0.1,0.05,0.1,0.2 };
double q[n + 1] = { 0.05,0.1,0.05,0.05,0.05,0.1 };
int root[n + 1][n + 1];//记录根节点  
double w[n + 2][n + 2];//子树概率总和  
double e[n + 2][n + 2];//子树期望代价 

void main(){
	OptimalBST(p,q,n);
	printRoot();
	cout << "Optimal_BST:" << endl;
	printOptimalBST(1,n,-1);
	system("pause");
}

void OptimalBST(double *p, double *q,int n) {
	//初始化只包括虚拟键的子树  
	for (int i = 1;i<= n + 1;++i) {
		w[i][i-1] = q[i-1];
		e[i][i - 1] = q[i-1];
	}
	for (int l = 1;l <= n;++l) {//自底向上寻找最优子树
		for (int i = 1;i <= n - l + 1;++i) {
			int j = i + l - 1;
			e[i][j] = MaxVal;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int k = i;k <= j;++k) {//找最优根
				double temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
				if (temp < e[i][j]) {
					e[i][j] = temp;
					root[i][j] = k;
				}
			}
		}
	}
}

//输出最优二叉查找树所有子树的根 
void printRoot() {
	cout << "root:" << endl;
	for (int i = 1;i <= n;++i) {
		for (int j = 1;j <= n;++j) {
			cout << root[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//打印最优二叉查找树的结构  
//打印出[i,j]子树，它是根r的左子树和右子树  
void printOptimalBST(int i,int j,int r) {
	int rootChild = root[i][j];//子树根节点 
	if (rootChild == root[1][n]) {
		//输出整棵树的根 
		cout << "k" << rootChild << " is root." << endl;
		printOptimalBST(i, rootChild - 1,rootChild);
		printOptimalBST(rootChild + 1,j, rootChild);
		return;
	}
	if (j < i - 1) {
		return;
	}
	else if(j == i - 1) {//遇到虚拟键  
		if (j < r)
			cout << "d" << j << " is " << "k" << r << "'s left child." << endl;
		else
			cout << "d" << j << " is " << "k" << r << "'s right child." << endl;
		return;
	}
	else{//遇到内部结点 
		if (rootChild < r)
			cout << "k" << rootChild << " is " << "k" << r << "'s left child." << endl;
		else
			cout << "k" << rootChild << " is " << "k" << r << "'s right child." << endl;
	}
		
	printOptimalBST(i, rootChild - 1, rootChild);
	printOptimalBST(rootChild + 1, j, rootChild);
}