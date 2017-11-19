//http://blog.csdn.net/baidu_28312631/article/details/47418773
//用D( r, j) 来表示第r行第 j 个数字(r,j从1开始算)
//用MaxSum(r, j)表示从D(r, j)到底边的各条路径中，最佳路径的数字之和。求 MaxSum(1, 1)
// D(r, j)出发，下一步只能走D(r+1,j)或者D(r+1, j+1)。


#include <iostream.>

using namespace std;

#define Max 101
int D[Max][Max];
int maxSum[Max][Max];
int *maxSumRaw;
int n;

int MaxSum(int i, int j);
int MaxSum1(int i, int j);
int MaxSum2(int k);


//下标从1开始
void main() {
	int i,j;
	cin >> n;//三角形行数
	for (i = 1;i <= n;i++) {
		for ( j = 1;j <= i;j++) {
			cin >> D[i][j];
			maxSum[i][j] = -1;
		}
	}
	cout << "输入的三角形为：" << endl;
	for (i = 1;i <= n;i++) {
		for (j = 1;j <= i;j++) {
			cout << D[i][j]<<" ";
		}
		cout << endl;
	}
	cout << "最大路径之和为：" << endl;
	cout << MaxSum(1,1) << endl;//fail????????
	cout << MaxSum1(1, 1) << endl;
	cout << MaxSum2(1) << endl;
	system("pause");
}

//备忘
int MaxSum(int i, int j) {
	if (maxSum[i][j] != -1)
		return maxSum[i][j];
	if(i==n)
	    maxSum[i][j]= D[i][j];
	else {
		int temp=maxSum[i + 1][j + 1] > maxSum[i + 1][j] ? maxSum[i + 1][j + 1] : maxSum[i + 1][j];
		maxSum[i][j]= temp+D[i][j];
	}
	return maxSum[i][j];
}

//把递归转换为递推，从最底层开始，向上
int MaxSum1(int i,int j) {
	int p,q;
	for(p=1;p<=n;p++)
		maxSum[n][p]= D[n][p];
	for(p=n-1;p>=1;p--)
		for (q = 1;q <= p;q++) {
			int temp = maxSum[p+1][q]>maxSum[p + 1][q+1]? maxSum[p + 1][q]: maxSum[p + 1][q+1];
			maxSum[p][q] = temp+D[p][q];
		}	
	return maxSum[i][j];
}

//D的第n行直接替代maxSum
int MaxSum2(int k) {
	maxSumRaw = D[n];//指向第n行
	for (int i = n - 1;i >= 1;--i) {
		for (int j = 1;j <= i;++j) {
			int temp = maxSumRaw[j] > maxSumRaw[j+1] ? maxSumRaw[j] : maxSumRaw[j+1];
			maxSumRaw[j] = temp + D[i][j];
		}
	}
	return maxSumRaw[k];
}
