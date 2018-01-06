//http://blog.csdn.net/to_baidu/article/details/50302071
//哈夫曼编码，构造最优前缀码（形成完全二叉树）的贪心算法

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
	//频率最小的两个不断合并
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
	return vec[0];//返回构造好的根节点
}

void  PrintHuffman(Node* v,vector<int> vctchar) {
	//用回溯法来打印编码
	//即遇到左子树向左走，vector添加记录0；遇到右子树向右走，vector添加记录1；
	//走到叶子节点并打印出叶节点的编码后回溯，同时往上退一层，则vector弹出一个值。如此不断回溯下去。
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
	cout << "请输入要编码的字符,并以空格隔开（个数任意）：" << endl;
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
	cout << "请输入要编码字符的频率：" << endl;
	for (int i = 0;i < vec.size();i++)
		cin >> vec[i]->frequency;

	Node *root = BuildHuffmanTree(vec);
	cout << endl << "对应的Huffman编码如下：" << endl;
	vector<int> vctchar;
	PrintHuffman(root,vctchar);

	system("pause");

}



