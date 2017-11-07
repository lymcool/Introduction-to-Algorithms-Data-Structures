//https://github.com/xuyicpp/Classical_Algorithms/blob/master/Introduction_to_Algorithms


#include <iostream>
#include <string>
#include <assert.h>
# include <cmath>

using namespace std;

#define EQ(a,b) ((a)==(b))
typedef int keytype;

struct HD{
	keytype key;
	int order;
};

void visit(int i, HD* c)
 {
		cout << '[' << i << "]: " << '(' << c->key << ", " << c->order << ')' << endl;
	 }

void visit(HD c){
	cout << '(' << c.key << ", " << c.order << ')';
}


#include "hashTable.h"
void main() {
	hashTable<HD> h;
	int i, j, n, p=0;
	bool m;

	HD e[10]= { { 17, 1 },{ 60, 2 },{ 29, 3 },{ 38, 4 },{ 1 ,5 },{ 2 ,6 },
		{3 ,7},{ 4 ,8 },{ 60, 9 },{ 13, 10 } };

	keytype k;
	n = 10;
	for (i = 0;i < n;i++) {
		j = h.InsertHash(e[i]);
		if (j == DUPLICATE) {
			cout << "哈希表中已有关键字为" << e[i].key << "的数据，无法再插入数据";
			visit(e[i]);
			cout << endl;

		}
		if (j == UNSUCCESS)//插入不成功，重建哈希表
			j = h.InsertHash(e[i]);
	}
	cout << "按哈希地址的顺序遍历哈希表：" << endl;
	h.traverseHash(visit);


 //删除数据测试 
	HD temp;
	cout<< "请输入待删除数据的关键字： 13" << endl;
	k = 13;
	m = h.deleteHash(k,temp);
	if (m) {
		cout << "成功删除数据";
		visit(temp);
		cout << endl;
	}
	else
		cout << "不存在关键字，无法删除！" << endl;
	cout << "按哈希地址的顺序遍历哈希表：" << endl;
	h.traverseHash(visit);
	
	//查询数据测试 
	cout << "请输入待查找数据的关键字：4" << endl;
	k = 4;
	n = 0;
	j = h.searchHash(k,p,n);
	if (j == SUCCESS) {
		visit(h.getElem(p));
			cout << endl;
	}
	else
		cout << "未找到" << endl;

	//插入数据测试 
	cout << "插入数据，请输入待插入数据的关键字：16" << endl;
	temp.key = 16;
	cout << "请输入待插入数据的order：15" << endl;
	temp.order = 15;
	j = h.InsertHash(temp);
	if (j == DUPLICATE) {
		cout << "哈希表中已有关键字为" << temp.key << "的数据，无法再插入数据";
		visit(temp);
		cout << endl;

	}
	if (j == UNSUCCESS)
		j = h.InsertHash(temp);
	cout << "按哈希地址的顺序遍历哈希表：" << endl;
	h.traverseHash(visit);

	system("pause");
}