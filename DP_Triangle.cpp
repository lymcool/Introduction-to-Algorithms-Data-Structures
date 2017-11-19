//http://blog.csdn.net/baidu_28312631/article/details/47418773
//��D( r, j) ����ʾ��r�е� j ������(r,j��1��ʼ��)
//��MaxSum(r, j)��ʾ��D(r, j)���ױߵĸ���·���У����·��������֮�͡��� MaxSum(1, 1)
// D(r, j)��������һ��ֻ����D(r+1,j)����D(r+1, j+1)��


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


//�±��1��ʼ
void main() {
	int i,j;
	cin >> n;//����������
	for (i = 1;i <= n;i++) {
		for ( j = 1;j <= i;j++) {
			cin >> D[i][j];
			maxSum[i][j] = -1;
		}
	}
	cout << "�����������Ϊ��" << endl;
	for (i = 1;i <= n;i++) {
		for (j = 1;j <= i;j++) {
			cout << D[i][j]<<" ";
		}
		cout << endl;
	}
	cout << "���·��֮��Ϊ��" << endl;
	cout << MaxSum(1,1) << endl;//fail????????
	cout << MaxSum1(1, 1) << endl;
	cout << MaxSum2(1) << endl;
	system("pause");
}

//����
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

//�ѵݹ�ת��Ϊ���ƣ�����ײ㿪ʼ������
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

//D�ĵ�n��ֱ�����maxSum
int MaxSum2(int k) {
	maxSumRaw = D[n];//ָ���n��
	for (int i = n - 1;i >= 1;--i) {
		for (int j = 1;j <= i;++j) {
			int temp = maxSumRaw[j] > maxSumRaw[j+1] ? maxSumRaw[j] : maxSumRaw[j+1];
			maxSumRaw[j] = temp + D[i][j];
		}
	}
	return maxSumRaw[k];
}
