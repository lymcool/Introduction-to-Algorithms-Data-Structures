//http://blog.csdn.net/to_baidu/article/details/50302071
//���������룬��������ǰ׺�루�γ���ȫ����������̰���㷨

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	char value;
	int frequency;
	Node* left;
	Node* right;
};

bool CompareNode(Node* p1, Node* p2) {
	return p1->frequency < p2->frequency;
}


Node* BuildHuffmanTree(vector<Node*> vec) {
	//Ƶ����С���������Ϻϲ�
	while (vec.size()>1) {
		sort(vec.begin(), vec.end(), CompareNode);
		Node* first = vec[0];
		Node* second = vec[1];
		Node* merge = new Node;
		merge->frequency = first->frequency + second->frequency;
		merge->left = first;
		merge->right = second;
        vec.erase(vec.begin(), vec.begin() + 2);
		vec.push_back(merge);
	}
	return vec[0];//���ع���õĸ��ڵ�
}

void  PrintHuffman(Node* v,vector<int> vctchar) {
	//�û��ݷ�����ӡ����
	//�����������������ߣ�vector��Ӽ�¼0�����������������ߣ�vector��Ӽ�¼1��
	//�ߵ�Ҷ�ӽڵ㲢��ӡ��Ҷ�ڵ�ı������ݣ�ͬʱ������һ�㣬��vector����һ��ֵ����˲��ϻ�����ȥ��
	if (v->left == NULL && v->right == NULL) {
		cout << v->value << ": ";
		for (int i = 0;i < vctchar.size();i++)
			cout << vctchar[i];
		cout << endl;
		return;
	}
	else {
		vctchar.push_back(0);
		PrintHuffman(v->left, vctchar);
		vctchar.pop_back();
		vctchar.push_back(1);
		PrintHuffman(v->right, vctchar);
		vctchar.pop_back();
	}
}


void main() {
	cout << "������Ҫ������ַ�,���Կո�������������⣩��" << endl;
	vector<Node*> vec;
	char ch;
	while ((ch = getchar()) != '\n') {
		if (ch == ' ')
			continue;
		Node* temp = new Node;
		temp->value = ch;
		temp->left = NULL;
		temp->right = NULL;
		vec.push_back(temp);
	}
	cout << "������Ҫ�����ַ���Ƶ�ʣ�" << endl;
	for (int i = 0;i < vec.size();i++)
		cin >> vec[i]->frequency;

	Node *root = BuildHuffmanTree(vec);
	cout << endl << "��Ӧ��Huffman�������£�" << endl;
	vector<int> vctchar;
	PrintHuffman(root,vctchar);

	system("pause");

}



