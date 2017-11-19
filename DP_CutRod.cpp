//钢条长度int n,价格数组int *p
//http://blog.csdn.net/nxiangbo/article/details/51111391

#include <iostream>

using namespace std;


int memoizedCutRod(int n, int *p);
int memoizedCutRodAux(int n, int *p, int *r);//带备忘的自顶向下法
void bottomUpCutRod(int n, int *p);//自底向上的方法
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
	int *r = new int[n+1]; //保存已计算过的子问题的解的数组
	for (int i = 0;i < n + 1;i++) {
		r[i] = -1;
	}
	return memoizedCutRodAux(n,p,r);
}

int memoizedCutRodAux(int n, int *p, int *r) {
	int i, q = -1;
	
	if (r[n] > 0)
		return r[n]; //如果已经计算过该子问题的解，直接返回
	if (n == 0)
		return 0;
	else {
		//r(n)=max(p[i]+r(n-i))
		//p[i]表示切割成长度为i的钢条的收益
		//r(n-i)剩余钢条的最大收益值
		for (i = 1;i <= n;i++)
			q = q > p[i] + memoizedCutRodAux(n - i, p, r) ? q : p[i] + memoizedCutRodAux(n - i, p, r);
	}
	r[n] = q;
	return q;
}

void bottomUpCutRod(int n, int *p) {
	int *r = new int[n+1];//用来保存中间解
	int *solve = new int[n+1]; //用来保存最优解的切割的钢条的长度
	r[0] = 0;
	for (int i = 1;i <= n;i++) { //依次求出规模为i = 1...n的子问题
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
	cout <<"钢条的最大收益为："<< maxValue<<endl;
	cout << "最优方案为：" ;
	while (n>0) {
		cout << solve[n] << " ";
		n = n - solve[n];
	}
	cout << endl;
}



