//http://www.cnblogs.com/xudong-bupt/archive/2013/03/15/2959039.html

#include <iostream>
#include <string>
using namespace std;

char a[500],b[500];
char num[501][501];
char flag[501][501];
void LCS();
void getLCS();


void main() {
	strcpy(a,"ABCBDAB");
	strcpy(b, "BDCABA");
	memset(num,0,sizeof(num));
	memset(flag, 0, sizeof(flag));
	LCS();
	getLCS();
	system("pause");
}


void LCS() {
	int i, j;
	for ( i = 1;i <= strlen(a);i++) {
		for ( j = 1;j <= strlen(b);j++) {
			if (a[i - 1] == b[j - 1]) {
				num[i][j] = num[i - 1][j - 1] + 1;
				flag[i][j] = 1;
			}
			else if (num[i][j-1]> num[i - 1][j]) {
				num[i][j] = num[i][j - 1];
				flag[i][j] = 2;
			}
			else  {
				num[i][j] = num[i - 1][j];
				flag[i][j] = 3;
			}

		}
	}

}


void getLCS() {
	char res[500];
	int k = 0;
	int i = strlen(a);
	int j= strlen(b);
	while (i>0&&j>0) {
		if (flag[i][j] == 1) {
			res[k] = a[i - 1];
			k++;
			i--;
			j--;
		}
		else if (flag[i][j] == 2)
			j--;
		else
			i--;
	
	}
	for (i = k - 1;i >= 0;i--)
		cout << res[i];
}