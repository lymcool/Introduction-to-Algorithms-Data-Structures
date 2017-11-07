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
			cout << "��ϣ�������йؼ���Ϊ" << e[i].key << "�����ݣ��޷��ٲ�������";
			visit(e[i]);
			cout << endl;

		}
		if (j == UNSUCCESS)//���벻�ɹ����ؽ���ϣ��
			j = h.InsertHash(e[i]);
	}
	cout << "����ϣ��ַ��˳�������ϣ��" << endl;
	h.traverseHash(visit);


 //ɾ�����ݲ��� 
	HD temp;
	cout<< "�������ɾ�����ݵĹؼ��֣� 13" << endl;
	k = 13;
	m = h.deleteHash(k,temp);
	if (m) {
		cout << "�ɹ�ɾ������";
		visit(temp);
		cout << endl;
	}
	else
		cout << "�����ڹؼ��֣��޷�ɾ����" << endl;
	cout << "����ϣ��ַ��˳�������ϣ��" << endl;
	h.traverseHash(visit);
	
	//��ѯ���ݲ��� 
	cout << "��������������ݵĹؼ��֣�4" << endl;
	k = 4;
	n = 0;
	j = h.searchHash(k,p,n);
	if (j == SUCCESS) {
		visit(h.getElem(p));
			cout << endl;
	}
	else
		cout << "δ�ҵ�" << endl;

	//�������ݲ��� 
	cout << "�������ݣ���������������ݵĹؼ��֣�16" << endl;
	temp.key = 16;
	cout << "��������������ݵ�order��15" << endl;
	temp.order = 15;
	j = h.InsertHash(temp);
	if (j == DUPLICATE) {
		cout << "��ϣ�������йؼ���Ϊ" << temp.key << "�����ݣ��޷��ٲ�������";
		visit(temp);
		cout << endl;

	}
	if (j == UNSUCCESS)
		j = h.InsertHash(temp);
	cout << "����ϣ��ַ��˳�������ϣ��" << endl;
	h.traverseHash(visit);

	system("pause");
}