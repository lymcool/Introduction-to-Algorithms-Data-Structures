//http://blog.sina.com.cn/s/blog_5d1f04810100x4qe.html
//计算A[i:j]所需的最少数乘次数为m[i][j]。
//设最优计算次序在Ak和Ak+1之间断开，则m[i][j]=m[i][k]+m[k+1][j]+pipk+1pj+1，其中p表示数组的维数
//k此时并未确定，需要从i到j-1遍历以寻找一个最小的m[i][j]。我们把这个最小的k放在s[i][j]。

#include <iostream>

#define N 6
using namespace std;

void MatixChain(int p[N + 1], int m[N][N], int s[N][N]);
void Traceback(int i, int j, int s[N][N]);

void main() {
	int p[N + 1] = { 30, 35, 15, 5, 10, 20, 25 };
	//p[0]:第0个矩阵的行数,p[1]:第0个矩阵的列数，第1个矩阵的行数
	int m[N][N];
	//int **m;
	//m=new int*[n];
	//for(int i=0;i<n;i++)
	//m[i]=new int[n];
	int s[N][N];
	MatixChain(p,m,s);
	Traceback(0,N-1,s);
	//for (int i = 0;i<n;i++)
	//{
	//	delete[]m[i];
	//	m[i] = NULL;
	//}
	//delete[]m;
	//m = NULL;
	system("pause");
}

//MatrixChain计算m[i][j]所需的最少数乘次数,并记录断开位置s[i][j]
void MatixChain(int p[N+1],int m[N][N], int s[N][N]) {//int *p,int **m,int **s
	//单个矩阵相乘，所需数乘次数为0,m[i][i]=0
	for (int i = 0;i < N;i++) {
		m[i][i] = 0;
	}

	for (int l =1;l < N;l++) {//链长度(右-左)
		for (int i = 0;i < N-l;i++) {//链左端点
			int j = i +l; //链右端点
			m[i][j] = INT_MAX;
			for (int k = i;k < j;k++) {//i,j中遍历寻找k的位置
				int temp = m[i][k] + m[k + 1][j] + p[i] * p[k+1] * p[j+1];
				if (temp < m[i][j]) {
					m[i][j]=temp;
					s[i][j] = k;
				}
			}
			
		}

	}

}

void Traceback(int i,int j, int s[N][N]) {//Traceback打印A[i:j]的加括号方式
	if (i == j)
		return;
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);//断开处为s[i][j]
	cout << "Matix "<< i << " and Matix " << s[i][j] + 1 << " multiply." << endl;
}