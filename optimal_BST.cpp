//http://blog.csdn.net/xiajun07061225/article/details/8088784
//����e[i,j]Ϊ�����ؼ���ki,...,kj�����Ŷ�����������������ۣ�����Ҫ�������e[1,n]��
//��j = i - 1ʱ����ʱ������ֻ���������������������Ϊe[i,i - 1] = qi-1.
//��j >= iʱ����Ҫ��ki, ..., kj��ѡ��һ����kr��Ȼ��ֱ���������������������

//�±��1��ʼ

#include <iostream>
using namespace std;

void OptimalBST(double *p, double *q, int n);
void printRoot();
void printOptimalBST(int i, int j, int r);

const int MaxVal = 9999;
const int n = 5;
//���������ڵ��������ĸ���  
double p[n + 1] = { -1,0.15,0.1,0.05,0.1,0.2 };
double q[n + 1] = { 0.05,0.1,0.05,0.05,0.05,0.1 };
int root[n + 1][n + 1];//��¼���ڵ�  
double w[n + 2][n + 2];//���������ܺ�  
double e[n + 2][n + 2];//������������ 

void main(){
	OptimalBST(p,q,n);
	printRoot();
	cout << "Optimal_BST:" << endl;
	printOptimalBST(1,n,-1);
	system("pause");
}

void OptimalBST(double *p, double *q,int n) {
	//��ʼ��ֻ���������������  
	for (int i = 1;i<= n + 1;++i) {
		w[i][i-1] = q[i-1];
		e[i][i - 1] = q[i-1];
	}
	for (int l = 1;l <= n;++l) {//�Ե�����Ѱ����������
		for (int i = 1;i <= n - l + 1;++i) {
			int j = i + l - 1;
			e[i][j] = MaxVal;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int k = i;k <= j;++k) {//�����Ÿ�
				double temp = e[i][k - 1] + e[k + 1][j] + w[i][j];
				if (temp < e[i][j]) {
					e[i][j] = temp;
					root[i][j] = k;
				}
			}
		}
	}
}

//������Ŷ�����������������ĸ� 
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

//��ӡ���Ŷ���������Ľṹ  
//��ӡ��[i,j]���������Ǹ�r����������������  
void printOptimalBST(int i,int j,int r) {
	int rootChild = root[i][j];//�������ڵ� 
	if (rootChild == root[1][n]) {
		//����������ĸ� 
		cout << "k" << rootChild << " is root." << endl;
		printOptimalBST(i, rootChild - 1,rootChild);
		printOptimalBST(rootChild + 1,j, rootChild);
		return;
	}
	if (j < i - 1) {
		return;
	}
	else if(j == i - 1) {//���������  
		if (j < r)
			cout << "d" << j << " is " << "k" << r << "'s left child." << endl;
		else
			cout << "d" << j << " is " << "k" << r << "'s right child." << endl;
		return;
	}
	else{//�����ڲ���� 
		if (rootChild < r)
			cout << "k" << rootChild << " is " << "k" << r << "'s left child." << endl;
		else
			cout << "k" << rootChild << " is " << "k" << r << "'s right child." << endl;
	}
		
	printOptimalBST(i, rootChild - 1, rootChild);
	printOptimalBST(rootChild + 1, j, rootChild);
}