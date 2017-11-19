//��������int n,�۸�����int *p
//http://blog.csdn.net/nxiangbo/article/details/51111391

#include <iostream>

using namespace std;


int memoizedCutRod(int n, int *p);
int memoizedCutRodAux(int n, int *p, int *r);//���������Զ����·�
void bottomUpCutRod(int n, int *p);//�Ե����ϵķ���
void bottomUpCutRodTwo(int n, int *p);
void print(int maxValue, int *solve, int n);

void main() {
	int n = 9;
	int p[11] = { 0,1,5,8,9,10,17,17,20,24,30 };
	int result = memoizedCutRod(n,p);
	cout << result<<endl;
	bottomUpCutRod(n,p);
	bottomUpCutRodTwo(n,p);
	system("pause");
}


int memoizedCutRod(int n,int *p) {
	int *r = new int[n+1]; //�����Ѽ������������Ľ������
	for (int i = 0;i < n + 1;i++) {
		r[i] = -1;
	}
	return memoizedCutRodAux(n,p,r);
}

int memoizedCutRodAux(int n, int *p, int *r) {
	int i, q = -1;
	
	if (r[n] > 0)
		return r[n]; //����Ѿ��������������Ľ⣬ֱ�ӷ���
	if (n == 0)
		return 0;
	else {
		//r(n)=max(p[i]+r(n-i))
		//p[i]��ʾ�и�ɳ���Ϊi�ĸ���������
		//r(n-i)ʣ��������������ֵ
		for (i = 1;i <= n;i++)
			q = q > p[i] + memoizedCutRodAux(n - i, p, r) ? q : p[i] + memoizedCutRodAux(n - i, p, r);
	}
	r[n] = q;
	return q;
}

void bottomUpCutRod(int n, int *p) {
	int *r = new int[n+1];//���������м��
	int *solve = new int[n+1]; //�����������Ž���и�ĸ����ĳ���
	r[0] = 0;
	for (int i = 1;i <= n;i++) { //���������ģΪi = 1...n��������
		int q = -1;
		for (int j = 1;j <= i;j++) {
			q = q > p[j] + r[i - j] ? q : p[j] + r[i - j];//
			solve[i] = j;
		}
		r[i] = q;
	}
	print(r[n],solve,n);
}

void bottomUpCutRodTwo(int n, int *p)
{
	int *r = new int[n + 1];
	r[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		int q = p[i];
		for (int j = 1; j <= i / 2; j++) {
			q = q>r[j] + r[i - j] ? q : r[j] + r[i - j];
		}
		r[i] = q;
	}
	cout << r[n];
}

void print(int maxValue,int *solve,int n) {
	cout <<"�������������Ϊ��"<< maxValue<<endl;
	cout << "���ŷ���Ϊ��" ;
	while (n>0) {
		cout << solve[n] << " ";
		n = n - solve[n];
	}
	cout << endl;
}



