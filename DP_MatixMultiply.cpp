//http://blog.sina.com.cn/s/blog_5d1f04810100x4qe.html
//����A[i:j]������������˴���Ϊm[i][j]��
//�����ż��������Ak��Ak+1֮��Ͽ�����m[i][j]=m[i][k]+m[k+1][j]+pipk+1pj+1������p��ʾ�����ά��
//k��ʱ��δȷ������Ҫ��i��j-1������Ѱ��һ����С��m[i][j]�����ǰ������С��k����s[i][j]��

#include <iostream>

#define N 6
using namespace std;

void MatixChain(int p[N + 1], int m[N][N], int s[N][N]);
void Traceback(int i, int j, int s[N][N]);

void main() {
	int p[N + 1] = { 30, 35, 15, 5, 10, 20, 25 };
	//p[0]:��0�����������,p[1]:��0���������������1�����������
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

//MatrixChain����m[i][j]������������˴���,����¼�Ͽ�λ��s[i][j]
void MatixChain(int p[N+1],int m[N][N], int s[N][N]) {//int *p,int **m,int **s
	//����������ˣ��������˴���Ϊ0,m[i][i]=0
	for (int i = 0;i < N;i++) {
		m[i][i] = 0;
	}

	for (int l =1;l < N;l++) {//������(��-��)
		for (int i = 0;i < N-l;i++) {//����˵�
			int j = i +l; //���Ҷ˵�
			m[i][j] = INT_MAX;
			for (int k = i;k < j;k++) {//i,j�б���Ѱ��k��λ��
				int temp = m[i][k] + m[k + 1][j] + p[i] * p[k+1] * p[j+1];
				if (temp < m[i][j]) {
					m[i][j]=temp;
					s[i][j] = k;
				}
			}
			
		}

	}

}

void Traceback(int i,int j, int s[N][N]) {//Traceback��ӡA[i:j]�ļ����ŷ�ʽ
	if (i == j)
		return;
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);//�Ͽ���Ϊs[i][j]
	cout << "Matix "<< i << " and Matix " << s[i][j] + 1 << " multiply." << endl;
}